# Operation Eden Licensing Model

Operation Eden uses different open licenses for different artifact classes so that hardware, software, and documentation can each use a license suited to their domain.

## Hardware

**CERN Open Hardware Licence Version 2 — Strongly Reciprocal (CERN-OHL-S v2)**

Intended scope:

- schematics
- PCB layouts
- Gerbers and fabrication outputs
- mechanical CAD
- hardware bills of materials
- hardware-specific design source

Hardware directories should carry an appropriate SPDX identifier or license notice where practical.

## Firmware & Software

**Apache License 2.0**

Intended scope:

- embedded firmware
- local dashboards
- validation tools
- command-line utilities
- protocol implementations
- reusable software libraries

Source files should use `SPDX-License-Identifier: Apache-2.0` where appropriate.

## Documentation

**Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)**

Intended scope:

- Declaration of Eden
- strategic plans
- technical specifications
- assembly guides
- calibration manuals
- fieldbooks
- curricula
- diagrams and documentation created specifically for the project unless otherwise marked

Attribution should identify Operation Eden and the relevant document authors/contributors where known.

## Data

Telemetry and ecological datasets are **not automatically public simply because the software is open source**.

Operation Eden follows a local-sovereignty-first model:

- Raw node telemetry remains under the control of the local Node or data steward.
- Synchronization to a regional cluster or Knowledge Commons is opt-in.
- Sensitive location, ecological, personal, or community data may require redaction, aggregation, delayed release, or non-release.
- Dataset-specific licenses should be declared when a dataset is intentionally published.

## Third-Party Components

Third-party hardware, firmware, libraries, datasets, fonts, images, and documentation retain their original licenses. Their inclusion in an Operation Eden repository does not relicense them.

## Canonical License Texts

Before a tagged public release, each artifact class should include the complete canonical license text required by its governing license and any required notices for third-party dependencies.
