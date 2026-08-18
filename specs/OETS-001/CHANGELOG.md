# OETS-001 Revision History

## 0.1.2 — Bench Freeze / M1 Build Authorized

Status: **Current canonical revision**

Key changes from 0.1.1:

- Clarified BQ24650 MPPT mechanism as programmable input-voltage regulation at a selected `VMPP` setpoint.
- Separated ESP32-S3 hardware SHA acceleration from software-based Ed25519 alpha signing.
- Added explicit private-key protection requirement.
- Replaced single active-current acceptance scalar with Joules per Observation (`J/obs`) energy profiling.
- Added requirement to characterize transient peak current.
- Clarified battery-temperature limits as pack-specific design targets requiring validation.
- Added breadboard pin map as an M1 default rather than a PCB-frozen interface.
- Strengthened autonomy calculation requirements.

## 0.1.1 — Pre-POC Frozen Draft

Key changes from 0.1.0:

- Corrected RTC precision language for DS3231-class TCXO timekeeping.
- Replaced CN3791 / Li-ion mismatch with BQ24650-class LiFePO4-capable charging architecture.
- Reclassified VEML7700 as an ambient illuminance sensor rather than a solar irradiance instrument.
- Corrected isolated RS-485 architecture.
- Converted deep-sleep current from prediction to empirical acceptance criterion.
- Replaced per-record Ed25519 signatures with hash-chain + periodic signed manifest architecture.
- Added dedicated system-health diagnostics block.

## 0.1.0 — Alpha Prototype Draft

Initial architecture establishing:

- local-first / offline-native telemetry
- modular sensor interfaces
- solar-supported low-power operation
- local raw-data sovereignty
- ESP32-S3 compute
- environmental sensing package
- MicroSD append-oriented logging
- ecological baseline methodology
- starter-kit replication package
- 90-day milestone structure
