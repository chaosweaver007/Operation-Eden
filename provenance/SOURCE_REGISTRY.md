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
| `knowledge-commons/TAXONOMY.md` | `SYN-AKA-002` | Library Taxonomy + Folder Map | Specification | Artifact / Candidate | Preserves type/status/topic classification and findability rules; aligns lifecycle language with Eden field/bench evidence and uses Eden's existing functional repository topology | Source registry notes migration and duplicate-resolution workflow as unfinished; Eden retains explicit migration rules rather than claiming the source solved them |
| `nodes/node-starter-kit/NODE_STARTER_KIT.md` | `SYN-AKA-003` | Node Starter Kit | Specification | Artifact / Candidate | Expands a software-project node bootstrap into a physical Eden Node bootstrap while retaining repo hygiene, licensing, contribution rules, secret protection, and Akasha documentation | Physical land, telemetry, food/restoration, and local-governance requirements are Eden additions, not historical claims about the source artifact |
| `standards/DATA_SOVEREIGNTY.md` | `SYN-DAT-002` | Synthsara Data Ownership Model | Specification | Historical Draft | Preserves user control, granular permissioning, selective disclosure, and non-extractive data principles | POWERcoin, staking, automatic monetization, and claims that blockchain alone guarantees legal ownership/privacy are not imported |
| `standards/DATA_SOVEREIGNTY.md` | `SYN-DATA-011` | Genesis Privacy Trinity Binding | Specification | Merged / Binding | Imports zero-write private mode, revocable consent, consent receipts, data minimization, and testable privacy promises; adapts them to Eden environmental/community/governance data classes | Strongest repository-native privacy specification in the current registry; authority beyond its repository and complete test coverage remain governance questions |
| `governance/MECHANISM_DESIGN.md` | `SYN-GOV-001` | Synthsara: An Executable Mechanism-Design Specification | Specification | Final Draft | Adapts due process, bounded authority, anti-Goodhart constraints, AI authority limits, threat modeling, and simulation-before-deployment into an Eden governance profile | Source explicitly frames itself as falsifiable and does not claim universal incentive compatibility, perfect privacy, permanent Sybil immunity, or capture-proof governance |
| `specs/OETS-001/OETS-001-REV-0.1.2.md` | Operation Eden native | Eden Environmental Telemetry Unit | Specification | Bench Freeze / M1 Authorized | Native Eden engineering specification | No claim that EETU-01 existed in historical Synthsara source corpus |
| `DECLARATION_OF_EDEN.md` | Operation Eden native | Declaration of Eden | Canon / Foundational | Active Eden Founding Document | Native Eden mission and normative orientation | Does not itself establish empirical proof, technical feasibility, or governance mechanics |
| `STRATEGIC_IMPLEMENTATION_PLAN.md` | Operation Eden native | Operation Eden Strategic Implementation Plan | Specification / Strategy | Active Planning Baseline | Native five-layer execution architecture and replication model | Milestones remain targets until supported by field execution and evidence |

---

## Verified Drive and Repository Sources

### Universal Diamond Standard Lite

- Drive ID: `1tJWN5KxLZi_8VuU91YsdOAngznZORVRQ`
- Title: `UniversalDiamondStandard™Lite.md`
- Registry ID: `SYN-ETH-003`
- Registry classification/status: Canon · Published / Candidate
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
- Registry classification/status: Specification · Artifact / Candidate
- Canonical semantic fields: WHAT, WHY, SOURCE, DATE, OWNER, STATUS, LINKS
- Standard lifecycle states in source: DRAFT, REVIEW, ACTIVE, ARCHIVED, DEPRECATED, DISPUTED
- Key source principles:
  - receipts without paranoia;
  - ledger over pattern;
  - non-extractive crediting;
  - do not persist sensitive information merely because it can be recorded.

### Library Taxonomy + Folder Map

- Drive ID: `1tv5LKCzfh9Lu1VIVUFS3vhOOa4Dq2qHO`
- Registry ID: `SYN-AKA-002`
- Registry classification/status: Specification · Artifact / Candidate
- Source requires classification by type, lifecycle status, and topic.
- Source emphasizes findability, descriptive naming, archive preservation, and routine triage.
- Registry open question: migration and duplicate-resolution workflow still requires implementation.

### Node Starter Kit

- Drive ID: `1n3xM3yTdcEuSNUafACvs_rB3xtuYolln`
- Title: `NODE_STARTER_KIT.pdf`
- Registry ID: `SYN-AKA-003`
- Registry classification/status: Specification · Artifact / Candidate
- Source purpose: minimum viable skeleton for a new Synthsara project node
- Source bootstrap requirements: README, LICENSE, CONTRIBUTING, `.gitignore`, and AKASHA entry
- Core source rule: **Ship Small, Ship Safe**
- Security rule in source: never commit secrets, keys, credentials, or personal information

### Synthsara Data Ownership Model

- Drive ID: `1M9-pos3fT1ixwVnV-wwPIGXEAOau0mVs`
- Registry ID: `SYN-DAT-002`
- Registry classification/status: Specification · Historical Draft
- Source themes: individual control, granular permissioning, selective disclosure, privacy-preserving exchange, and self-sovereign identity.
- Registry note: major precursor to current privacy architecture; legal enforceability and economic incentives require review.
- Migration boundary: historical POWERcoin/token and automatic monetization mechanics are not active Eden requirements.

### Genesis Privacy Trinity Binding

- Repository path: `chaosweaver007/Genesis/docs/privacy/Genesis-Privacy-Trinity-Binding.md`
- Registry ID: `SYN-DATA-011`
- Registry classification/status: Specification · Merged / Binding
- Binding requirements include meaningful/granular/revocable consent, zero-write private/guest behavior, Consent Receipts, data minimization, and tests for privacy promises.
- The binding states that private interaction data must not persist without explicit consent and that consent must remain legible and reversible.

### Synthsara Executable Mechanism-Design Specification

- Drive ID: `1dEtgSKe-wzG4P_OqKsLUjV8afD0e3UW2c8UO9TqsSNU`
- Registry ID: `SYN-GOV-001`
- Registry classification/status: Specification · Final Draft
- Source scope: formal dynamic mechanism, WORTH separation, due process, monitoring, constitutional control, threat model, and simulation contract.
- Source research position: a falsifiable institutional/computational hypothesis whose claims must be earned through analysis, adversarial simulation, pilots, and public correction.
- Registry note: current strongest governance formalization; institutional cost and equilibrium analysis remain open.

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
8. preserve failed and superseded versions when they are necessary to understand lineage;
9. prefer later binding/testable specifications over older aspirational versions when they conflict;
10. state explicitly when historical economic or token assumptions are excluded from the Eden migration.

---

## Current Convergence Map

```text
SYNTHSARA SOURCE CORPUS
        │
        ├── UDS ─────────────────────► UDS Eden Profile
        │                                  │
        ├── Data Ownership ───────────┐     │
        │                             ├────► Data Sovereignty Standard
        ├── Privacy Trinity Binding ──┘     │
        │                                  │
        ├── Mechanism Design ─────────────► Eden Governance Profile
        │                                  │
        ├── Akasha Format ────────────────► Eden Commons Schema
        │                                  │
        ├── Akasha Taxonomy ──────────────► Eden Commons Taxonomy
        │                                  │
        └── Node Starter Kit ─────────────► Physical Eden Node Kit
                                           │
                                           ▼
                                OPERATION EDEN IMPLEMENTATION
                                           │
                              ┌────────────┴────────────┐
                              ▼                         ▼
                         EETU-01                  Seed Projects
                              │                         │
                              └────────────┬────────────┘
                                           ▼
                                     FIELD EVIDENCE
                                           │
                                           ▼
                                   KNOWLEDGE COMMONS
```

---

## Provenance Discipline

When importing future Synthsara material into Operation Eden, every migration should answer:

- What exact source artifact is being used?
- What is its registry ID?
- What is its source classification?
- What is its source status?
- Which clauses are inherited?
- Which clauses are rejected, superseded, or deferred?
- What Eden artifact now carries the migrated requirement?
- What test, ratification, implementation, or field evidence is still missing?

### Canon Is Not Evidence

Normative authority, technical implementation, and empirical validation are different layers.

A document may be canonical without proving an empirical claim.  
A specification may be rigorous without being implemented.  
An implementation may run without satisfying its intended specification.  
A successful pilot may remain local and non-generalizable.

Operation Eden therefore preserves the chain:

**SOURCE → CLASSIFICATION → ADAPTATION → IMPLEMENTATION → TEST → EVIDENCE → REVISION**

---

**PRESERVE THE LINEAGE. PRESERVE THE STATUS. NEVER LET ANCESTRY MASQUERADE AS PROOF.**
