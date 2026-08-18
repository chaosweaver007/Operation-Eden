# OETS-001 M1A Source Freeze Provenance Receipt

**Receipt ID:** `OE-PROV-OETS-001-M1A-001`  
**Artifact:** `OETS-001-M1A-SRC-FROZEN`  
**Classification:** Implementation / Bench Source Freeze  
**Status:** Frozen Bench Implementation · Physical Validation Pending  
**Parent Specification:** `specs/OETS-001/OETS-001-REV-0.1.2.md`

## What Was Frozen

The M1A Witness Core translates the EETU-01 bench architecture into executable artifacts:

- `firmware/eetu-01/m1a/main/main.c`
- `firmware/eetu-01/m1a/sdkconfig.defaults`
- `tools/validator/validate_chain.py`
- `specs/OETS-001/bench/OETS-001-M1A-SRC-FROZEN.md`

The implementation freezes five hardening requirements:

1. DS3231 24-hour UTC trust gate with Oscillator Stop Flag rejection.
2. SHT40 CRC-8 validation before telemetry acceptance.
3. Integer centi-unit quantization for cross-runtime deterministic hashing.
4. Full sequential cryptographic ledger recovery with invalid-tail truncation.
5. Checked SHA-256 computation through the Mbed TLS path configured for ESP32-S3 hardware acceleration.

## Canonical Persistence Rule

The MicroSD telemetry ledger is the persistence root for M1A chain recovery. A record advances canonical state only after:

`complete line → sequence check → predecessor check → canonical preimage reconstruction → SHA-256 verification`

NVS is not part of the canonical M1A persistence state.

## Evidence Boundary

A repository commit proves that the source was versioned. It does **not** prove that the hardware passed.

The following remain evidence gates:

- target compilation under the selected ESP-IDF 5.x version;
- successful flash and boot on ESP32-S3-DevKitC-1;
- 10 normal witness cycles;
- SHT40 CRC rejection test;
- deliberate record-tamper validator failure;
- cold power cut during deep sleep;
- cold power cut during storage write;
- successful ledger recovery and sanitization;
- independent validator success;
- 72-hour M1 endurance run;
- M2 Joules-per-Observation power profile.

Until those artifacts are attached, the correct status is **Frozen Bench Implementation**, not validated hardware.

## Cross-System Archive

A canonical archival copy of the frozen package is stored in Google Drive as:

**`OETS-001-M1A-SRC-FROZEN — EETU-01 Witness Core`**

Drive file ID: `1NFZhQW-ssx-S5EXyHLJfoHzCxYUDh4oGJR0Bub67Fvs`

Operation Eden Drive folder ID: `1CvyQkJ-A6cSs8pS9RIv7AhgvqUiEAdWs`

## Provenance Chain

```text
OETS-001 REV 0.1.2
        │
        ▼
M1A HARDENING REVIEW
        │
        ▼
OETS-001-M1A-SRC-FROZEN
        │
        ├── firmware
        ├── validator
        ├── build defaults
        └── archival Drive record
        │
        ▼
PHYSICAL BENCH EVIDENCE
        │
        ▼
M1A ACCEPT / REVISE
```

**SOURCE FREEZE IS NOT FIELD PROOF. THE BENCH DECIDES THE NEXT STATUS.**
