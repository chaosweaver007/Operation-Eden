# OPERATION EDEN TECHNICAL SPECIFICATION 001
## REVISION 0.1.2 — BENCH FREEZE · M1 BUILD AUTHORIZED

**Document ID:** OETS-001-REV-0.1.2  
**System Name:** Eden Environmental Telemetry Unit (EETU-01)  
**Layer:** Layer 2 (Digital Infrastructure) / Layer 3 (Local Projects)  
**Status:** **SPECIFICATION LOCKED · PROCEED TO M1 BENCH BUILD**  
**Build Gate:** Physical Validation via Breadboard POC & Energy Profiling  
**Target Horizon:** M1 Bench Validation (14 Days) → M2 Power Profiling (7 Days)

## 1. Purpose & Architectural Mandate

The Eden Environmental Telemetry Unit (EETU-01) serves as the sensory nervous system for Operation Eden. Its objective is to provide an open-source, resilient, local-first monitoring system capable of establishing ecological baselines, measuring ongoing regenerative interventions, and verifying environmental change over time.

### Core Design Rules

- **Local-First & Offline-Native:** The node functions without mandatory internet connectivity. Data is retained locally in human-readable, append-oriented formats.
- **Modular Interoperability:** Sensor interfaces use standard buses including I²C, SPI, UART, 1-Wire, and RS-485/Modbus.
- **Low Power:** Energy design targets solar-supported autonomous field operation, with empirical validation before field release.
- **Data Sovereignty by Default:** Raw telemetry remains under local node control. External synchronization is opt-in and selective.
- **Cryptographic Verifiability:** Records are hash-chained locally and periodic manifests are signed.
- **Repairability:** Sensors and subsystems should remain replaceable using broadly available components and ordinary field tools wherever practical.

## 2. Final Pre-Bench Errata Resolution

| Item | Adopted Standard | Engineering Consequence |
|---|---|---|
| MPPT Mechanics | Programmable MPPT via input-voltage regulation (`VMPP` setpoint) | Avoids conflating BQ24650 input-voltage regulation with perturb-and-observe MPPT algorithms |
| Chain Hashing | Hardware-accelerated SHA-256 via ESP32-S3 SHA engine | Reduces hashing overhead while preserving local integrity chain |
| Manifest Signing | Software Ed25519 for Alpha | Keeps protocol portable; hardware-bound key protection evaluated before production freeze |
| Key Protection | Device private key MUST NOT reside as unprotected plaintext in persistent storage | Establishes minimum alpha security requirement |
| Power Metric | Joules per Observation (`J/obs`) | Replaces single-current claims with portable empirical energy measurement |
| Diagnostics | Dedicated system-health telemetry block | Enables fleet diagnosis and baseline normalization |

## 3. Power Subsystem Specification

```text
[ 5W–12V Open-Circuit Solar Array ]
                  │
                  ▼
┌─────────────────────────────────────────────────────────────┐
│ TI BQ24650 Synchronous Buck Battery Charger                 │
│ • Input Regulation: programmed to panel VMPP setpoint       │
│ • 1S LiFePO4 charge profile configured for selected pack   │
│ • Pack thermistor charge-permission window                  │
└──────────────────────────────┬──────────────────────────────┘
                               │
                               ▼
                  [ 1S LiFePO4 Cell / Pack ]
             (3.2V nominal · PCM / over-discharge cut)
                               │
                               ▼
┌─────────────────────────────────────────────────────────────┐
│ Ultra-Low Quiescent Current Power Rail                      │
│ • TPS62840-class low-Iq regulator where appropriate         │
│ • High-side load switching to external sensor/storage rails │
└──────────────────────────────┬──────────────────────────────┘
                               │
         ┌─────────────────────┴─────────────────────┐
         ▼                                           ▼
[ UNGATED DOMAIN ]                          [ GATED DOMAIN ]
• ESP32-S3 deep-sleep domain               • SHT40 / BMP280 / VEML7700
• DS3231 timekeeper                        • DS18B20 array
• Wake lines                               • isolated RS-485 domain
                                            • MicroSD VCC rail
```

**Battery temperature values are design targets and MUST be validated against the selected cell/pack manufacturer's permitted charge-temperature specification before field release.**

## 4. Hardware Architecture

### Core Compute

- ESP32-S3-WROOM-1 (N16R8 target module)
- Native USB for programming and service
- Hardware SHA acceleration
- Wi-Fi / BLE available but not required for core operation

### Timekeeping

- DS3231SN-class TCXO real-time clock
- High-stability offline timekeeping with periodic synchronization support

### Base Sensors

- Sensirion SHT40 — ambient air temperature / relative humidity
- Bosch BMP280 — barometric pressure
- Vishay VEML7700 — ambient illuminance (`lux`), not pyranometry
- DS18B20 waterproof probe — soil temperature
- Modular calibrated dielectric soil-moisture probe
- Tipping bucket rain gauge — precipitation pulse input

### Industrial Expansion

- Galvanically isolated RS-485 / Modbus RTU transceiver
- TVS / surge protection appropriate to field cable deployment
- Isolated DC/DC supply for isolated bus domain where required
- Qwiic / STEMMA QT I²C expansion
- UART expansion reserved for SX1262-class LoRa radios

## 5. Crypto & Telemetry Protocol

```text
[ OBSERVATION STREAM ] → [ SHA-256 ] → [ LOCAL HASH CHAIN ]
                                              │
                                              ▼
                         [ PERIODIC MANIFEST / MERKLE ROOT ]
                                              │
                                              ▼
                                  [ Ed25519 SIGNATURE ]
```

### 5.1 Ten-Minute Periodic Sample Record

```json
{
  "protocol": "eden-telemetry-v1",
  "node_id": "eden-us-ga-001",
  "device_id": "eetu-alpha-001",
  "timestamp": "2026-08-17T23:10:00.000Z",
  "seq": 14286,
  "metrics": {
    "air_temp_c": 22.45,
    "relative_humidity_pct": 68.2,
    "barometric_pressure_hpa": 1014.2,
    "ambient_light_lux": 0.0,
    "soil_temp_c": 19.8,
    "soil_moisture_vwc_pct": 31.4,
    "rainfall_period_mm": 0.0
  },
  "system": {
    "firmware_version": "0.1.2-alpha",
    "battery_mv": 3285,
    "solar_mv": 0,
    "board_temp_c": 21.5,
    "reset_reason": "rtc_timer_wakeup",
    "free_storage_bytes": 15874298880,
    "sensor_health_bitmap": "0x003F"
  },
  "prev_record_hash": "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
  "record_hash": "9f83c605d847427ae41e4649b934ca495991b7852b855e3b0c44298fc1c149af"
}
```

### 5.2 Integrity Manifest

At a ten-minute cadence there are 144 observations per 24-hour period. A canonical epoch manifest may aggregate the daily chain and sign its Merkle root rather than signing each individual record.

```json
{
  "manifest_protocol": "eden-epoch-v1",
  "node_id": "eden-us-ga-001",
  "device_id": "eetu-alpha-001",
  "epoch_start_seq": 14200,
  "epoch_end_seq": 14343,
  "start_time": "2026-08-17T00:00:00.000Z",
  "end_time": "2026-08-17T23:50:00.000Z",
  "merkle_root": "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b",
  "ed25519_public_key": "3d4017c3e843895a92b70aa74d1b7ebc9c982ccf2ec4968cc0cd55f12af4660c",
  "signature": "ed25519:<signature-bytes>"
}
```

### Cryptographic Implementation Note

SHA-256 chain hashing may use the ESP32-S3 hardware SHA accelerator. Ed25519 manifest signing is implemented independently in software for the alpha prototype. Production key-protection requirements will be defined before field-release freeze. The device private key MUST NOT be stored as unprotected plaintext in persistent storage.

Production hardware evaluation will compare the ESP32-S3 RSA-based Digital Signature peripheral against an external secure element for hardware-bound device identity/signing requirements.

## 6. Field Calibration & Baseline Methodology

A sensor reading without a calibration and baseline record is an unverified assumption.

### Ecological Baseline Procedure

1. **Multi-Point Transect Selection**  
   Identify distinct ecological and hydrological zones such as riparian buffer, degraded core, and reference/control zone.

2. **Soil Moisture Calibration**  
   Calibrate dielectric probes against site-specific gravimetric measurements appropriate to the selected soil horizons and methodology.

3. **Passive Baseline Window**  
   Run co-located sensors before intervention long enough to characterize ordinary variance. Initial field protocol targets 14 uninterrupted days.

4. **Periodic Recalibration**  
   Perform scheduled inspection, cleaning, reference checks, and maintenance appropriate to each sensor class.

## 7. M1 Breadboard Bench Protocol

### Hardware Test Bench

- Compute: ESP32-S3-DevKitC-1 (N16R8 target)
- RTC: DS3231 breakout on primary I²C
- Primary sensors: SHT40 + BMP280
- Soil temperature: DS18B20 with switched pull-up domain
- Storage: MicroSD via SPI
- Switching: logic-level high-side load switch / P-channel MOSFET arrangement for peripheral rail isolation
- Instrumentation: Nordic PPK2 or equivalent current profiler; oscilloscope + shunt acceptable when measurement bandwidth and burden voltage are characterized

### Proposed Breadboard Pin Map

- I²C SDA: GPIO 4
- I²C SCL: GPIO 5
- Switched peripheral control: GPIO 2
- MicroSD CS: GPIO 10
- MicroSD MOSI: GPIO 11
- MicroSD CLK: GPIO 12
- MicroSD MISO: GPIO 13

**Pin assignments are M1 bench defaults, not yet PCB-frozen interfaces.**

## 8. M1 / M2 Acceptance Criteria

| Test | Pass / Required Result | Verification |
|---|---|---|
| Deep-Sleep Current | Whole assembly ≤100 µA @ 3.3 V; stretch ≤25 µA | PPK2/current profiler averaged over stable sleep interval |
| Cycle Energy | Measure and report `J/obs`; initial engineering target <25 mJ for sample/write cycle without radio | Numerical integral of voltage × current over wake/sample/write/sleep transition |
| Peak Current | Measure and document all characterized transients | Current profiler / oscilloscope |
| Hash Chain | 100% valid SHA-256 continuity across 432 continuous cycles (72 h) | Offline validation script |
| Bus Stability | Zero unrecovered I²C lockups over 72 h endurance run | Firmware logs + watchdog/error counters |
| Switched Rail | Peripheral rail approaches de-energized state and leakage is characterized; design target <1 µA where measurement permits | DMM / current profiler |
| RTC Stability | Characterize DS3231 drift against a known reference; result must remain within selected part's specified operating envelope | Pre/post reference comparison |
| Power-Dip Recovery | No silent chain corruption after controlled brownout/power-dip tests | Log inspection + hash validator |

### Autonomy Calculation Requirement

The 14-day zero-sun autonomy claim MUST NOT be accepted from nominal component current alone. Final sizing must use measured cycle energy, measured sleep current, usable battery capacity, regulator losses, self-discharge, temperature derating, battery aging assumptions, and safety margin.

## 9. Starter Kit Repository Structure

```text
eetu-01-starter-kit/
├── hardware/
│   ├── schematics/
│   ├── gerbers/
│   ├── mechanical/
│   └── bom/
├── firmware/
│   ├── src/
│   ├── lib/
│   └── tests/
├── protocol/
│   ├── schemas/
│   └── crypto/
├── docs/
│   ├── assembly_guide.md
│   ├── calibration.md
│   ├── baseline_manual.md
│   ├── repair_fieldbook.md
│   └── failure_log.md
└── tools/
    ├── local_dashboard/
    └── validation/
```

## 10. Immediate Implementation Milestones

| Milestone | Target | Description | Deliverable |
|---|---|---|---|
| M1 — Breadboard POC | Days 1–14 | ESP32-S3 bench test with SHT40, BMP280, DS18B20, DS3231, MicroSD, chain logging | Verified firmware build, raw data stream, endurance log |
| M2 — Power Profiling | Days 15–21 | Characterize wake, sample, write, sleep, and transient energy | `J/obs` profile and autonomy model |
| M3 — PCB & Enclosure | Days 22–45 | Open carrier PCB and field enclosure prototypes | Three functioning EETU-01 prototypes |
| M4 — Ecological Seed Site Zero | Days 46–60 | Deploy first unit and begin no-intervention baseline | Signed raw baseline dataset |
| M5 — Starter Kit | Days 61–90 | Publish hardware, firmware, protocol, documentation, and failure logs | Reproducible EETU-01 starter kit |

## 11. Authorization

```text
=====================================================================
  SPECIFICATION STATUS: LOCKED FOR PHYSICAL PROTOTYPING
  DOCUMENT CODE:        OETS-001-REV-0.1.2
  ACTION:               ASSEMBLE BENCH PROTOTYPE (M1)
=====================================================================
```

Documentation now gives way to hardware execution.

The next authoritative milestone is the bench log, energy profile, and integrity validation output.

**The sensory foundation is specified. The hardware blueprint is open. Data remains sovereign.**
