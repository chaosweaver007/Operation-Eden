# Operation Eden Source Registry

**Document ID:** `OE-PROV-001`  
**Status:** Active Provenance Record  
**Purpose:** Preserve source lineage, transformation boundaries, and claim status as Synthsara artifacts are adapted into Operation Eden infrastructure.

---

## Registry Rule

Operation Eden distinguishes:

- **Canon** — ratified normative or philosophical source;
- **Specification** — defined architecture, protocol, or process;
- **Implementation** — executable code, deployed artifact, or physical build;
- **Research** — analysis, hypothesis, comparison, or evidence review;
- **Provenance / Historical** — ancestry preserved for lineage but not automatically load-bearing.

A derived Eden document must state what was inherited, what was changed, and what was newly introduced.

**Pattern must never overwrite record.**

---

## Source Registry

| Eden Artifact | Source ID | Source Artifact | Source Class | Source Status | Eden Transformation | Notes |
|---|---|---|---|---|---|---|
| `standards/UDS_EDEN_PROFILE.md` | `SYN-ETH-003` / UDS family | Universal Diamond Standard Lite + Universal Diamond Standard | Canon / Specification | Published / Candidate in registry | Preserves eight UDS principles and adds two labeled Eden profile extensions for physical-world subsidiarity and adaptive regeneration | UDS Lite source text is licensed CC BY-NC 4.0; Eden profile is an operational adaptation and does not claim to relicense source text |
| `knowledge-commons/AKASHA_ENTRY_SCHEMA.md` | `SYN-AKA-001` | Akasha Entry Format | Specification | Artifact / Candidate | Preserves WHAT / WHY / SOURCE / DATE / OWNER / STATUS / LINKS semantics; adds YAML, evidence state, Node IDs, datasets, and optional integrity metadata | Parent artifact emphasizes provenance without surveillance and record-before-interpretation |
| `nodes/node-starter-kit/NODE_STARTER_KIT.md` | `SYN-AKA-003` | Node Starter Kit | Specification | Artifact / Candidate | Expands a software-project node bootstrap into a physical Eden Node bootstrap while retaining repo hygiene, licensing, contribution rules, secret protection, and Akasha documentation | Physical land, telemetry, food/restoration, and local-governance requirements are Eden additions, not historical claims about the source artifact |
| `specs/OETS-001/OETS-001-REV-0.1.2.md` | Operation Eden native | Eden Environmental Telemetry Unit | Specification | Bench Freeze / M1 Authorized | Native Eden engineering specification | No claim that EETU-01 existed in historical Synthsara source corpus |

---

## Verified Drive Sources

### Universal Diamond Standard Lite

- Drive ID: `1tJWN5KxLZi_8VuU91YsdOAngznZORVRQ`
- Title: `UniversalDiamondStandard™Lite.md`
- Version: 1.0
- Date stated in source: 2025-06-30
- Source authors stated in document: Manus AI (O-Series Soul Protocol), Steven Pritchard (Architect)
- Source license stated in document: Creative Commons Attribution-NonCommercial 4.0 International
- Core principles stated: Sovereignty, Transparency, Fairness, Accountability, Security, Service to Life, Privacy, Ecology

### Universal Diamond Standard

- Drive ID: `1CVs5xHM2eUoOnd2cOH0FGnQeoBEox-XD`
- Title: `Universal-Diamond-Standard.md`
- Core principles stated: same eight-principle structure
- Relevance: confirms the eight-principle UDS architecture independently of the Eden adaptation

### Akasha Entry Format

- Drive ID: `1KMkyGy6Ht9fieJdVkcDzMQp6DMHGv3yC`
- Title: `AKASHA_ENTRY_FORMAT.pdf`
- Registry ID: `SYN-AKA-001`
- Canonical semantic fields: WHAT, WHY, SOURCE, DATE, OWNER, STATUS, LINKS
- Standard lifecycle states in source: DRAFT, REVIEW, ACTIVE, ARCHIVED, DEPRECATED, DISPUTED
- Key source principles:
  - receipts without paranoia;
  - ledger over pattern;
  - non-extractive crediting;
  - do not persist sensitive information merely because it can be recorded.

### Node Starter Kit

- Drive ID: `1n3xM3yTdcEuSNUafACvs_rB3xtuYolln`
- Title: `NODE_STARTER_KIT.pdf`
- Registry ID: `SYN-AKA-003`
- Source purpose: minimum viable skeleton for a new Synthsara project node
- Source bootstrap requirements: README, LICENSE, CONTRIBUTING, `.gitignore`, and AKASHA entry
- Core source rule: **Ship Small, Ship Safe**
- Security rule in source: never commit secrets, keys, credentials, or personal information

---

## Transformation Policy

When adapting Synthsara material into Operation Eden:

1. preserve the source identifier and title;
2. preserve original classification and status;
3. do not upgrade a candidate or historical artifact into prior canon by implication;
4. distinguish inherited principles from Eden-specific additions;
5. preserve upstream license obligations;
6. keep metaphysical, interpretive, technical, empirical, and governance claims separately labeled where their evidentiary status differs;
7. link implementation evidence when a specification becomes physical or executable;
8. preserve failed and superseded versions when they are necessary to understand lineage.

---

## Current Convergence Map

```text
SYNTHSARA SOURCE CORPUS
        │
        ├── UDS ───────────────► UDS Eden Profile
        │                           │
        ├── Akasha Format ─────► Eden Commons Schema
        │                           │
        └── Node Starter Kit ──► Physical Eden Node Kit
                                    │
                                    ▼
                         OPERATION EDEN IMPLEMENTATION
                                    │
                         ┌──────────┴──────────┐
                         ▼                     ▼
                    EETU-01               Seed Projects
                         │                     │
                         └──────────┬──────────┘
                                    ▼
                              FIELD EVIDENCE
                                    │
                                    ▼
                            KNOWLEDGE COMMONS
```

This registry is the bridge between ancestry and implementation.
