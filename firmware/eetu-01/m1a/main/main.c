#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <math.h>
#include <sys/stat.h>

#include "esp_system.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_vfs_fat.h"
#include "driver/i2c_master.h"
#include "driver/spi_master.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "mbedtls/sha256.h"

static const char *TAG = "EETU-M1A";

#define I2C_PORT               -1
#define I2C_SDA_GPIO           4
#define I2C_SCL_GPIO           5
#define I2C_FREQ_HZ            100000

#define SPI_MISO_GPIO          13
#define SPI_MOSI_GPIO          11
#define SPI_CLK_GPIO           12
#define SPI_CS_GPIO            10

#define SD_MOUNT_POINT         "/sdcard"
#define LOG_FILE_PATH          "/sdcard/telemetry.ndjson"
#define WAKE_INTERVAL_US       (600ULL * 1000ULL * 1000ULL)

#define SHT40_ADDR             0x44
#define DS3231_ADDR            0x68

typedef struct {
    uint32_t seq;
    char prev_hash[65];
} chain_state_t;

// --- CRC-8 SENSIRION POLYNOMIAL (0x31, INIT 0xFF) ---
static uint8_t sensirion_crc8(const uint8_t *data, size_t len) {
    uint8_t crc = 0xFF;
    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (int bit = 0; bit < 8; bit++) {
            crc = (crc & 0x80) ? (uint8_t)((crc << 1) ^ 0x31) : (uint8_t)(crc << 1);
        }
    }
    return crc;
}

static uint8_t bcd_to_dec(uint8_t val) {
    return ((val / 16 * 10) + (val % 16));
}

// --- HARDWARE-ACCELERATED MBEDTLS SHA-256 WITH CHECKED RETURN ---
static esp_err_t compute_sha256_hex(const char *input, char *out_hex) {
    uint8_t digest[32];
    int rc = mbedtls_sha256((const unsigned char *)input, strlen(input), digest, 0);
    if (rc != 0) {
        ESP_LOGE(TAG, "mbedtls_sha256 failed: %d", rc);
        return ESP_FAIL;
    }
    for (int i = 0; i < 32; i++) {
        snprintf(out_hex + (i * 2), 3, "%02x", digest[i]);
    }
    out_hex[64] = '\0';
    return ESP_OK;
}

// --- SENSOR DRIVERS (ESP-IDF 5.x I2C MASTER API) ---
static esp_err_t sample_sht40(i2c_master_dev_handle_t dev, int32_t *temp_centi_c, int32_t *rh_centi_pct) {
    uint8_t cmd = 0xFD; // High-precision command
    uint8_t rx[6];
    
    esp_err_t ret = i2c_master_transmit(dev, &cmd, 1, 50);
    if (ret != ESP_OK) return ret;
    vTaskDelay(pdMS_TO_TICKS(15));

    ret = i2c_master_receive(dev, rx, 6, 50);
    if (ret != ESP_OK) return ret;

    if (sensirion_crc8(&rx[0], 2) != rx[2] || sensirion_crc8(&rx[3], 2) != rx[5]) {
        ESP_LOGE(TAG, "SHT40 CRC validation failed");
        return ESP_ERR_INVALID_CRC;
    }

    uint16_t t_ticks = (rx[0] << 8) | rx[1];
    uint16_t rh_ticks = (rx[3] << 8) | rx[4];

    float temp_c = -45.0f + 175.0f * (float)t_ticks / 65535.0f;
    float rh_pct = -6.0f + 125.0f * (float)rh_ticks / 65535.0f;
    if (rh_pct > 100.0f) rh_pct = 100.0f;
    if (rh_pct < 0.0f) rh_pct = 0.0f;

    // Cross-runtime canonical integer quantization
    *temp_centi_c = (int32_t)lroundf(temp_c * 100.0f);
    *rh_centi_pct = (int32_t)lroundf(rh_pct * 100.0f);

    return ESP_OK;
}

static esp_err_t sample_ds3231_checked(i2c_master_dev_handle_t dev, char *iso_buf, size_t max_len) {
    uint8_t status_reg = 0x0F;
    uint8_t status_val = 0;
    
    // Check Oscillator Stop Flag (OSF - Bit 7 of 0x0F)
    esp_err_t ret = i2c_master_transmit_receive(dev, &status_reg, 1, &status_val, 1, 50);
    if (ret != ESP_OK) return ret;

    if (status_val & 0x80) {
        ESP_LOGE(TAG, "DS3231 OSF flag active! Clock integrity compromised.");
        return ESP_ERR_INVALID_STATE;
    }

    // Read Timekeeping Registers (0x00 - 0x06)
    uint8_t time_reg = 0x00;
    uint8_t rx[7];
    ret = i2c_master_transmit_receive(dev, &time_reg, 1, rx, 7, 50);
    if (ret != ESP_OK) return ret;

    // Validate 24-hour format (bit 6 of hours register must be 0)
    if (rx[2] & 0x40) {
        ESP_LOGE(TAG, "DS3231 configured in 12-hour mode. 24-hour UTC required.");
        return ESP_ERR_INVALID_STATE;
    }

    uint8_t sec  = bcd_to_dec(rx[0] & 0x7F);
    uint8_t min  = bcd_to_dec(rx[1]);
    uint8_t hour = bcd_to_dec(rx[2] & 0x3F);
    uint8_t date = bcd_to_dec(rx[4]);
    uint8_t mon  = bcd_to_dec(rx[5] & 0x1F);
    uint16_t yr  = 2000 + bcd_to_dec(rx[6]);

    if (sec > 59 || min > 59 || hour > 23 || date == 0 || date > 31 || mon == 0 || mon > 12) {
        ESP_LOGE(TAG, "DS3231 register BCD range error");
        return ESP_ERR_INVALID_STATE;
    }

    snprintf(iso_buf, max_len, "%04d-%02d-%02dT%02d:%02d:%02d.000Z", yr, mon, date, hour, min, sec);
    return ESP_OK;
}

// --- CANONICAL PREIMAGE GENERATION ---
static void build_canonical_preimage(char *buf, size_t max_len, const char *ts, uint32_t seq,
                                     int32_t temp_centi, int32_t rh_centi,
                                     const char *fw, const char *reason, const char *prev_hash) {
    snprintf(buf, max_len,
        "eden-telemetry-v1|device=eetu-alpha-001|ts=%s|seq=%" PRIu32 "|air_temp_centi_c=%" PRId32 "|relative_humidity_centi_pct=%" PRId32 "|firmware=%s|reset_reason=%s|prev=%s",
        ts, seq, temp_centi, rh_centi, fw, reason, prev_hash);
}

// --- CRYPTOGRAPHIC CRASH RECOVERY LEDGER ENGINE ---
static void recover_and_sanitize_chain(chain_state_t *state) {
    state->seq = 0;
    strcpy(state->prev_hash, "GENESIS");

    FILE *f = fopen(LOG_FILE_PATH, "r+");
    if (!f) {
        ESP_LOGI(TAG, "No existing log found. Bootstrapping Genesis block.");
        return;
    }

    char line[1024];
    long last_valid_end_pos = 0;
    uint32_t expected_seq = 1;
    char running_prev_hash[65] = "GENESIS";

    while (1) {
        long current_line_start = ftell(f);
        if (!fgets(line, sizeof(line), f)) break;

        size_t len = strlen(line);
        if (len == 0 || line[len - 1] != '\n') break; // Incomplete or interrupted line

        // Parse canonical integer fields and hashes
        char parsed_ts[32] = {0}, parsed_fw[32] = {0}, parsed_reason[32] = {0};
        char parsed_prev[65] = {0}, parsed_record_hash[65] = {0};
        uint32_t parsed_seq = 0;
        int32_t parsed_t_centi = 0, parsed_rh_centi = 0;

        char *ptr_ts = strstr(line, "\"timestamp\":\"");
        char *ptr_seq = strstr(line, "\"seq\":");
        char *ptr_t = strstr(line, "\"air_temp_centi_c\":");
        char *ptr_rh = strstr(line, "\"relative_humidity_centi_pct\":");
        char *ptr_fw = strstr(line, "\"firmware_version\":\"");
        char *ptr_reason = strstr(line, "\"reset_reason\":\"");
        char *ptr_prev = strstr(line, "\"prev_record_hash\":");
        char *ptr_hash = strstr(line, "\"record_hash\":\"");

        if (!ptr_ts || !ptr_seq || !ptr_t || !ptr_rh || !ptr_fw || !ptr_reason || !ptr_prev || !ptr_hash) {
            break;
        }

        sscanf(ptr_ts, "\"timestamp\":\"%31[^\"]\"", parsed_ts);
        sscanf(ptr_seq, "\"seq\":%" SCNu32, &parsed_seq);
        sscanf(ptr_t, "\"air_temp_centi_c\":%" SCNd32, &parsed_t_centi);
        sscanf(ptr_rh, "\"relative_humidity_centi_pct\":%" SCNd32, &parsed_rh_centi);
        sscanf(ptr_fw, "\"firmware_version\":\"%31[^\"]\"", parsed_fw);
        sscanf(ptr_reason, "\"reset_reason\":\"%31[^\"]\"", parsed_reason);
        sscanf(ptr_hash, "\"record_hash\":\"%64[^\"]\"", parsed_record_hash);

        if (strncmp(ptr_prev, "\"prev_record_hash\":null", 23) == 0) {
            strcpy(parsed_prev, "GENESIS");
        } else {
            sscanf(ptr_prev, "\"prev_record_hash\":\"%64[^\"]\"", parsed_prev);
        }

        // Sequence and Link Verification
        if (parsed_seq != expected_seq || strcmp(parsed_prev, running_prev_hash) != 0) {
            ESP_LOGW(TAG, "Chain continuity broken at pos %ld", current_line_start);
            break;
        }

        // Preimage and Hash Verification
        char preimage_check[512];
        char calculated_hash[65];
        build_canonical_preimage(preimage_check, sizeof(preimage_check), parsed_ts, parsed_seq,
                                parsed_t_centi, parsed_rh_centi, parsed_fw, parsed_reason, running_prev_hash);

        if (compute_sha256_hex(preimage_check, calculated_hash) != ESP_OK ||
            strcmp(calculated_hash, parsed_record_hash) != 0) {
            ESP_LOGW(TAG, "Cryptographic invalidity at pos %ld", current_line_start);
            break;
        }

        // State advances only on verified record
        last_valid_end_pos = ftell(f);
        state->seq = parsed_seq;
        strcpy(state->prev_hash, parsed_record_hash);
        strcpy(running_prev_hash, parsed_record_hash);
        expected_seq++;
    }

    fclose(f);

    // Sanitize partial or corrupted tail
    truncate(LOG_FILE_PATH, last_valid_end_pos);
    ESP_LOGI(TAG, "Ledger verified and locked: Valid Records=%" PRIu32 ", Tail Pos=%ld", state->seq, last_valid_end_pos);
}

// --- MAIN EXECUTION CORE ---
void app_main(void) {
    esp_reset_reason_t reason = esp_reset_reason();
    const char *reason_str = (reason == ESP_RST_DEEPSLEEP) ? "rtc_wakeup" : "power_on";

    // 1. Initialize Modern I2C Master Bus
    i2c_master_bus_config_t bus_cfg = {
        .i2c_port = I2C_PORT,
        .sda_io_num = I2C_SDA_GPIO,
        .scl_io_num = I2C_SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus_handle));

    // Discrete device configurations
    i2c_device_config_t sht_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SHT40_ADDR,
        .scl_speed_hz = I2C_FREQ_HZ,
    };
    i2c_master_dev_handle_t sht40_dev;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &sht_cfg, &sht40_dev));

    i2c_device_config_t rtc_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = DS3231_ADDR,
        .scl_speed_hz = I2C_FREQ_HZ,
    };
    i2c_master_dev_handle_t ds3231_dev;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &rtc_cfg, &ds3231_dev));

    // 2. Read Sensors (Enforce OSF and CRC checks)
    char iso_time[32];
    int32_t t_centi = 0, rh_centi = 0;
    ESP_ERROR_CHECK(sample_ds3231_checked(ds3231_dev, iso_time, sizeof(iso_time)));
    ESP_ERROR_CHECK(sample_sht40(sht40_dev, &t_centi, &rh_centi));

    // 3. Mount MicroSD
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t spi_cfg = {
        .mosi_io_num = SPI_MOSI_GPIO,
        .miso_io_num = SPI_MISO_GPIO,
        .sclk_io_num = SPI_CLK_GPIO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    ESP_ERROR_CHECK(spi_bus_initialize(host.slot, &spi_cfg, SDSPI_DEFAULT_DMA));

    sdspi_device_config_t slot_cfg = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_cfg.gpio_cs = SPI_CS_GPIO;
    slot_cfg.host_id = host.slot;

    esp_vfs_fat_sdmmc_mount_config_t mount_cfg = {
        .format_if_mount_failed = false,
        .max_files = 2,
        .allocation_unit_size = 16 * 1024
    };

    sdmmc_card_t *card;
    ESP_ERROR_CHECK(esp_vfs_fat_sdspi_mount(SD_MOUNT_POINT, &host, &slot_cfg, &mount_cfg, &card));

    // 4. Recover & Authenticate Ledger Tail
    chain_state_t chain;
    recover_and_sanitize_chain(&chain);
    uint32_t current_seq = chain.seq + 1;

    // 5. Construct Canonical Preimage & Compute Record Hash
    char preimage[512];
    build_canonical_preimage(preimage, sizeof(preimage), iso_time, current_seq,
                            t_centi, rh_centi, "0.1.2-alpha", reason_str, chain.prev_hash);

    char record_hash[65];
    ESP_ERROR_CHECK(compute_sha256_hex(preimage, record_hash));

    // 6. Assemble Dual-Representation NDJSON Record
    char json_record[1024];
    float t_float = (float)t_centi / 100.0f;
    float rh_float = (float)rh_centi / 100.0f;

    if (strcmp(chain.prev_hash, "GENESIS") == 0) {
        snprintf(json_record, sizeof(json_record),
            "{\"protocol\":\"eden-telemetry-v1\",\"device_id\":\"eetu-alpha-001\",\"timestamp\":\"%s\",\"seq\":%" PRIu32 ",\"metrics\":{\"air_temp_c\":%.2f,\"relative_humidity_pct\":%.2f},\"raw_canonical\":{\"air_temp_centi_c\":%" PRId32 ",\"relative_humidity_centi_pct\":%" PRId32 "},\"system\":{\"firmware_version\":\"0.1.2-alpha\",\"reset_reason\":\"%s\"},\"prev_record_hash\":null,\"record_hash\":\"%s\"}\n",
            iso_time, current_seq, t_float, rh_float, t_centi, rh_centi, reason_str, record_hash);
    } else {
        snprintf(json_record, sizeof(json_record),
            "{\"protocol\":\"eden-telemetry-v1\",\"device_id\":\"eetu-alpha-001\",\"timestamp\":\"%s\",\"seq\":%" PRIu32 ",\"metrics\":{\"air_temp_c\":%.2f,\"relative_humidity_pct\":%.2f},\"raw_canonical\":{\"air_temp_centi_c\":%" PRId32 ",\"relative_humidity_centi_pct\":%" PRId32 "},\"system\":{\"firmware_version\":\"0.1.2-alpha\",\"reset_reason\":\"%s\"},\"prev_record_hash\":\"%s\",\"record_hash\":\"%s\"}\n",
            iso_time, current_seq, t_float, rh_float, t_centi, rh_centi, reason_str, chain.prev_hash, record_hash);
    }

    FILE *f = fopen(LOG_FILE_PATH, "a");
    if (f) {
        fputs(json_record, f);
        fflush(f);
        fsync(fileno(f)); // Request synchronization of buffered FAT/VFS file state to storage
        fclose(f);
    }

    printf("%s", json_record);

    // 7. Tear Down Peripherals & Enter Deep Sleep
    esp_vfs_fat_sdcard_unmount(SD_MOUNT_POINT, card);
    spi_bus_free(host.slot);
    i2c_del_master_bus(bus_handle);

    ESP_LOGI(TAG, "Cycle complete. Entering deep sleep (%llu s)...", WAKE_INTERVAL_US / 1000000ULL);
    esp_deep_sleep(WAKE_INTERVAL_US);
}
