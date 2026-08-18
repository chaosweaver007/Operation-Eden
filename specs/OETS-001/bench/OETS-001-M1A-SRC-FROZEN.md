# OPERATION EDEN · TECHNICAL SPECIFICATION 001
## M1A WITNESS CORE · FROZEN BENCH IMPLEMENTATION

**Document ID:** `OETS-001-M1A-SRC-FROZEN`  
**Subsystem:** Eden Environmental Telemetry Unit (EETU-01) — Witness Engine  
**Status:** **FROZEN BENCH IMPLEMENTATION (READY TO FLASH)**  
**Verification:** Cryptographic Crash Recovery · Cross-Runtime Quantization · OSF Guarded Time

---

## 1. Architectural Summary of Bench Freezes

```text
                    ┌─────────────────────────────────────────┐
                    │            RTC TRUST AUDIT              │
                    │   DS3231: 24h UTC Mode + OSF == 0       │
                    └────────────────────┬────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────┐
                    │          SHT40 CRC-8 AUDIT              │
                    │   Sensirion Polynomial (0x31, Init 0xFF)│
                    └────────────────────┬────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────┐
                    │     CROSS-RUNTIME QUANTIZATION          │
                    │   Integer Centi-Units (lroundf * 100)   │
                    └────────────────────┬────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────┐
                    │     CRYPTOGRAPHIC CRASH RECOVERY        │
                    │   Full Ledger Walk + Auto-Truncate      │
                    └────────────────────┬────────────────────┘
                                         │
                                         ▼
                    ┌─────────────────────────────────────────┐
                    │        CANONICAL SHA-256 HASH           │
                    │   Checked Mbed TLS Return Code          │
                    └─────────────────────────────────────────┘
```

The M1A Witness Core is the minimum physical proof loop for Operation Eden:

`wake → validate time → sense → validate CRC → quantize → recover ledger → hash → persist → sleep`

The MicroSD ledger is the canonical persistence root. Recovery does not trust the presence of a newline alone: records advance chain state only after sequence, predecessor, and SHA-256 verification. Any incomplete or cryptographically invalid tail is truncated to the last verified record boundary.

---

## 2. Canonical Executable Artifacts

The frozen source implementation is held in exactly one executable location per artifact:

- `firmware/eetu-01/m1a/main/main.c` — M1A Witness Core firmware
- `firmware/eetu-01/m1a/sdkconfig.defaults` — ESP-IDF build/runtime defaults
- `tools/validator/validate_chain.py` — host-side canonical ledger validator

This specification defines the behavior and freeze boundary. The files above are the executable source of truth and must not be silently forked into alternate canonical copies.

---

## 3. Canonical Preimage Protocol

All cryptographic chain calculations use deterministic integer centi-units rather than cross-runtime floating-point text formatting.

Canonical preimage order:

```text
eden-telemetry-v1|device=eetu-alpha-001|ts=<ISO8601>|seq=<uint32>|air_temp_centi_c=<int32>|relative_humidity_centi_pct=<int32>|firmware=<version>|reset_reason=<reason>|prev=<GENESIS-or-SHA256>
```

Example:

```text
eden-telemetry-v1|device=eetu-alpha-001|ts=2026-08-18T03:45:00.000Z|seq=4|air_temp_centi_c=2245|relative_humidity_centi_pct=5180|firmware=0.1.2-alpha|reset_reason=power_on|prev=9f83c605d847427ae41e4649b934ca495991b7852b855e3b0c44298fc1c149af
```

SHA-256 is computed through Mbed TLS with ESP32-S3 hardware acceleration enabled by configuration. A record is accepted into the chain only when its preimage recomputes to the stored `record_hash`.

---

## 4. Time Trust Gate

The DS3231 is not accepted merely because it returns a syntactically valid time.

A measurement cycle requires:

- 24-hour mode;
- Oscillator Stop Flag (`OSF`) clear;
- valid BCD-derived second, minute, hour, date, and month ranges;
- UTC provisioning as the operational convention.

If the timekeeper fails this gate, the measurement cycle aborts rather than producing falsely trusted ecological evidence.

---

## 5. Sensor Integrity Gate

The SHT40 high-precision measurement response is validated using Sensirion CRC-8:

- polynomial: `0x31`;
- initialization: `0xFF`;
- temperature word and humidity word independently checked.

CRC failure returns `ESP_ERR_INVALID_CRC` and prevents the sample from entering the ledger.

---

## 6. Cross-Runtime Quantization

Environmental values are quantized before entering the cryptographic boundary:

```text
air_temp_centi_c = lroundf(temp_c * 100)
relative_humidity_centi_pct = lroundf(rh_pct * 100)
```

NDJSON retains both:

1. human-readable decimal metrics; and
2. `raw_canonical` integer values used by the cryptographic preimage.

The validator reconstructs hashes from `raw_canonical`, not floating-point representations.

---

## 7. Cryptographic Crash Recovery

On every boot, `recover_and_sanitize_chain()` performs a sequential ledger audit:

1. initialize expected state as `seq = 1`, `prev = GENESIS`;
2. read only newline-complete candidate records;
3. parse canonical fields;
4. require exact sequence continuity;
5. require exact predecessor linkage;
6. reconstruct the canonical integer preimage;
7. recompute SHA-256;
8. advance state only if the stored hash matches;
9. remember the byte offset after the last valid record;
10. truncate the file to that offset.

If zero records validate, the ledger is sanitized back to byte zero and the next accepted record becomes Genesis.

---

## 8. Build Gate Configuration

`firmware/eetu-01/m1a/sdkconfig.defaults` freezes:

```text
# Hardware Crypto & Mbed TLS Acceleration
CONFIG_MBEDTLS_HARDWARE_SHA=y
CONFIG_MBEDTLS_SHA256_C=y

# FATFS / VFS Crash Resilience Optimization
CONFIG_FATFS_IMMEDIATE_FSYNC=y
CONFIG_FATFS_MAX_LFN=32

# FreeRTOS & Deep Sleep Timer Clock
CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ_160=y
CONFIG_ESP32S3_RTC_CLK_SRC_EXT_CRYS=n
```

---

## 9. Matched Host Validator

`tools/validator/validate_chain.py` independently verifies:

- sequence monotonicity;
- Genesis/null predecessor rule;
- predecessor linkage;
- canonical integer preimage reconstruction;
- SHA-256 digest equality.

Canonical success declaration:

```text
[✓] SUCCESS: Verified <N> committed records, contiguous sequence, valid hash chain, and canonical record integrity.
```

---

## 10. M1A Bench Acceptance Matrix

| Verification Vector | Pass Criterion | Validation Test |
|---|---|---|
| Normal Cycle Flow | 10 consecutive wake → sense → hash → write → sleep loops | Serial output + uninterrupted sequence |
| CRC-8 Enforcement | SHT40 sample rejected when checksum mismatches | Inject/mock corrupt sensor response and verify `ESP_ERR_INVALID_CRC` |
| Full Preimage Rigidity | Altering any canonical metric/system field invalidates audit | Edit a committed record and require validator failure |
| Cold Power Cut During Sleep | Prior state recovers from SD without corruption | Pull supply in sleep, restore power, require next sequence to reference verified tail |
| Cold Power Cut During Write | Partial/invalid tail is removed, prior valid chain retained | Interrupt write cycle and verify boot sanitization |
| Chain Verification Script | All accepted records independently reproduce | Validator prints canonical success declaration |

---

## 11. Freeze Boundary

```text
=====================================================================
  M1A BENCH PROTOCOL: HARDENED & FROZEN
  COMPATIBILITY:      ESP-IDF 5.x · C99/C11 · Python 3.8+
  CRYPTO CANON:       SHA-256 (Canonical Integer-Quantized Preimage)
  TIME ACCREDITATION: DS3231 24h UTC + Oscillator Stop Flag (OSF)
  PERSISTENCE GATE:   Full-Ledger Sequential Scan + Auto-Truncate
=====================================================================
```

The source freeze authorizes physical bench execution. It does **not** by itself constitute evidence that the firmware has compiled on the target, passed the M1A acceptance matrix, survived destructive power-cut testing, or met M2 energy targets. Those claims become valid only when corresponding build and bench evidence is attached to the repository.

**Next state:** `BUILD → FLASH → CUT POWER → RECOVER → VERIFY`

The code is ready for the bench evidence phase. The first accepted records from the physical unit become the implementation proof layer for OETS-001.
