# EETU-01 M1 Bench Test Protocol

**Parent Specification:** OETS-001-REV-0.1.2  
**Milestone:** M1 — Breadboard Proof of Concept  
**Target Duration:** 14 days  
**Status:** Ready for execution

## Objective

Demonstrate that the EETU-01 alpha architecture can reliably wake, sample, timestamp, hash, write, return to deep sleep, and recover from controlled faults while preserving a continuous local record.

M1 does **not** validate field enclosure performance, solar autonomy, long-range radio, soil-moisture calibration, or production key protection. Those belong to later milestones.

## Bench Hardware

- ESP32-S3-DevKitC-1, N16R8 target
- DS3231 RTC breakout
- Sensirion SHT40
- Bosch BMP280
- DS18B20 waterproof temperature probe
- MicroSD module + high-endurance MicroSD card
- High-side switched peripheral rail
- Stable 3.3 V bench supply
- Nordic PPK2 or equivalent current profiler
- Optional oscilloscope + characterized shunt for transient validation

## M1 Proposed Pin Map

| Function | GPIO |
|---|---:|
| I²C SDA | 4 |
| I²C SCL | 5 |
| Peripheral rail control | 2 |
| MicroSD CS | 10 |
| MicroSD MOSI | 11 |
| MicroSD CLK | 12 |
| MicroSD MISO | 13 |

These are breadboard defaults and remain subject to change before PCB freeze.

## Required Firmware State Machine

```text
BOOT / WAKE
   ↓
INITIALIZE RTC + HEALTH STATE
   ↓
ENABLE PERIPHERAL RAIL
   ↓
SENSOR SETTLE
   ↓
READ SENSORS
   ↓
BUILD CANONICAL RECORD
   ↓
SHA-256 HASH + CHAIN LINK
   ↓
APPEND NDJSON RECORD TO MICROSD
   ↓
FLUSH / VERIFY WRITE STATUS
   ↓
DISABLE PERIPHERAL RAIL
   ↓
ENTER DEEP SLEEP
```

## Required Record Fields

Each observation must contain, at minimum:

- protocol version
- node ID
- device ID
- timestamp
- monotonic sequence number
- available sensor readings
- firmware version
- reset reason
- storage-health indicator
- sensor-health bitmap
- previous record hash
- record hash

## Test A — Basic Acquisition

Pass conditions:

- SHT40 readable without I²C error.
- BMP280 readable without I²C error.
- DS18B20 readable on 1-Wire bus.
- RTC timestamp is valid after cold boot and wake cycle.
- One complete NDJSON record is written to MicroSD.
- Hash validator independently reproduces `record_hash`.

## Test B — Sleep / Wake Reliability

Run repeated wake cycles at the intended sample cadence.

Pass conditions:

- no unexplained resets
- no unrecovered bus lockups
- sequence numbers remain monotonic
- RTC time remains monotonic
- peripheral rail is disabled during sleep

## Test C — 72-Hour Endurance Run

Minimum duration: **432 observations at ten-minute cadence**.

Pass conditions:

- 432 expected records present
- zero unexplained sequence gaps
- zero hash-chain discontinuities
- zero unrecovered I²C failures
- zero unrecovered MicroSD failures
- any recoverable errors recorded explicitly in system diagnostics

## Test D — Controlled Power-Dip Recovery

Introduce controlled power interruption / brownout conditions appropriate to bench equipment.

Verify:

- device reboots cleanly
- reset reason is recorded where detectable
- previously committed records remain parseable
- no silent modification of previous hash-chain records
- the first post-recovery record identifies the correct predecessor or explicitly establishes a documented recovery boundary

## Test E — Deep-Sleep Current

Measure whole-system current after all transient activity has settled.

Acceptance:

- required: **≤100 µA at 3.3 V**
- stretch goal: **≤25 µA at 3.3 V**

Record:

- measurement instrument
- firmware commit
- board revision / dev-kit revision
- peripheral modules connected
- averaging interval
- minimum / mean / maximum current
- supply voltage
- ambient temperature

## Test F — Acquisition Energy

Measure the complete wake → sample → hash → write → rail-off → sleep transition.

Calculate:

`E_cycle = ∫ V(t) × I(t) dt`

Report the result in:

- millijoules per active cycle
- Joules per Observation (`J/obs`)

Initial engineering target for the sample/write cycle without radio: **<25 mJ**, pending empirical results.

Do not hide failure if the target is missed. Record the trace and optimize from evidence.

## Test G — RTC Characterization

Compare RTC time against a known reference before and after an uninterrupted characterization interval.

Record:

- start delta
- end delta
- elapsed time
- calculated drift in ppm
- ambient temperature range

Acceptance is based on the selected RTC part's specified operating envelope, not an assumed universal drift value.

## Artifacts to Commit

M1 is not complete until the repository contains:

- firmware commit hash used for test
- raw 72-hour NDJSON log
- hash-chain validation report
- current trace / exported measurement data
- `J/obs` calculation
- RTC characterization log
- fault-injection notes
- observed defects
- photographs or wiring diagram of breadboard configuration
- `M1_BENCH_REPORT.md`

## Exit Gate

M1 passes when the architecture demonstrates reliable acquisition, local persistence, cryptographic chain continuity, sleep/wake operation, and measurable energy behavior sufficient to proceed into M2 optimization.

**The bench decides.**
