# Akasha Entry Schema (Knowledge Commons Standard)

**Document ID:** `AKES-001`  
**Status:** Active Eden Specification  
**Layer:** Layer 2 (Digital Infrastructure & Commons)  
**Format:** Frontmatter-Annotated Markdown (`.md`)

---

## Provenance

This specification is adapted from **`SYN-AKA-001` — Akasha Entry Format** in the Synthsara corpus.

The parent artifact defines seven canonical semantic fields:

- `WHAT`
- `WHY`
- `SOURCE`
- `DATE`
- `OWNER`
- `STATUS`
- `LINKS`

It also establishes three core documentation rules:

1. documentation enables verification, attribution, and learning without becoming surveillance;
2. record comes before interpretation;
3. credit must remain non-extractive and provenance must remain visible.

Operation Eden preserves those semantics while extending them with machine-readable metadata, evidence state, datasets, cryptographic integrity references, and Node identifiers.

---

## 1. Purpose

The **Akasha Entry Schema** provides structured, findable, attributable documentation across the Eden Knowledge Commons.

Every experiment, design, failure report, governance decision, field protocol, curriculum artifact, and validated replication intended for Commons persistence should use this schema.

The purpose is not to record everything.

> **If it matters, we record it. If it does not need to persist, we let it go.**

Private thoughts, sensitive personal information, data that could harm people, and unnecessary behavioral records do not belong in the public Akasha.

---

## 2. Canonical Frontmatter Specification

```yaml
---
akasha_version: "eden-1.0.0"
entry_id: "AKE-ECOL-2026-001"

# Parent Akasha semantics
what: "Riparian Strip Bio-Silt Trapping via Native Willow Staking"
why: "Test a low-cost method for reducing bank erosion and suspended sediment at a restoration site."
source:
  summary: "Operation Eden ecological seed experiment"
  derived_from:
    - "SYN-AKA-001"
  related_specs:
    - "OETS-001-REV-0.1.2"
  source_links: []

date:
  created: "2026-08-17"
  updated: "2026-08-17"

owner:
  name: "Local Watershed Guild"
  node_id: "eden-us-ga-001"
  contact: null
  contact_sig: null

status: "ACTIVE"
# Parent lifecycle values:
# DRAFT | REVIEW | ACTIVE | ARCHIVED | DEPRECATED | DISPUTED

links:
  prerequisites: []
  related: []
  builds_on: []
  extended_by: []

# Eden extensions
domain: "ecology"
# ecology | agriculture | technology | governance | infrastructure | health | education | culture | economy

evidence_status: "field-testing"
# untested | bench-testing | field-testing | validated | failed | superseded

license: "CC-BY-SA-4.0"
tags:
  - "watershed"
  - "soil-retention"
  - "riparian"
  - "low-tech"

related_datasets:
  - "commons/datasets/2026-q3-riparian-turbidity.csv"

integrity:
  method: "optional"
  manifest: null
  signature: null
---
```

Cryptographic integrity is supported where useful, especially for telemetry, manifests, and multi-node replication records, but is **not mandatory for every Akasha entry**.

---

## 3. Standard Body Structure

```markdown
# [Title Matching `what`]

## 1. Executive Summary & Problem Statement
A concise description of the physical, technical, social, or educational problem addressed and why the entry matters.

## 2. Materials, Tools & Context
- **Environmental / Operating Context:**
- **Bill of Materials / Inputs:**
- **Required Tools:**
- **Dependencies:**
- **Known Constraints:**

## 3. Step-by-Step Implementation Protocol
1. Establish baseline or initial state.
2. Execute intervention / build procedure.
3. Record maintenance or observation cadence.
4. Preserve deviations from the original plan.

## 4. Empirical Results & Evidence
- **Baseline Data:**
- **Measured Outcomes:**
- **Raw Artifact Links:**
- **Telemetry / Logs:**
- **Uncertainty / Confounders:**

## 5. Failure Analysis & Lessons Learned
- **What Failed:**
- **What Changed:**
- **Why It Changed:**
- **What Remains Unknown:**
- **Guidance for Replicating Nodes:**
```

---

## 4. Status Semantics

### Lifecycle Status

| Status | Meaning |
|---|---|
| `DRAFT` | Work in progress; not ready for operational reliance |
| `REVIEW` | Ready for feedback; not finalized |
| `ACTIVE` | Current, approved, and in use |
| `ARCHIVED` | No longer current; preserved for historical reference |
| `DEPRECATED` | Replaced by a newer entry or protocol |
| `DISPUTED` | Accuracy, provenance, interpretation, or ownership is contested |

### Evidence Status

| Evidence State | Meaning |
|---|---|
| `untested` | Proposal or design without empirical testing |
| `bench-testing` | Controlled technical test underway |
| `field-testing` | Real-world test underway |
| `validated` | Defined acceptance criteria met within documented scope |
| `failed` | Acceptance criteria not met; retained for learning |
| `superseded` | Evidence or method replaced by a later implementation |

Lifecycle state and evidence state are intentionally separate. An `ACTIVE` document may still describe a `field-testing` protocol.

---

## 5. Receipts Without Surveillance

Akasha documentation SHOULD enable:

- verification;
- attribution;
- replication;
- learning;
- correction;
- historical provenance.

Akasha documentation MUST NOT become a mechanism for:

- tracking private behavior without necessity and consent;
- punitive dossiers;
- social-credit scoring;
- unnecessary personal-data retention;
- gatekeeping access to general knowledge.

---

## 6. Ledger Over Pattern

The factual record comes first.

Interpretation may be added, debated, revised, or disputed, but interpretation must never overwrite the underlying record.

When an entry contains both observation and inference, label them separately.

---

## 7. Non-Extractive Crediting

When adapting another person's or community's work:

- name the source;
- link the source when possible;
- identify modifications;
- preserve upstream license obligations;
- do not silently claim inherited work as original;
- seek permission where the license or context requires it.

---

## 8. Minimum Viable Entry

When a full entry is not yet practical, preserve at minimum:

```text
WHAT:   [Title]
WHY:    [One sentence]
SOURCE: [Origin]
DATE:   [YYYY-MM-DD]
OWNER:  [Responsible person or group]
STATUS: [DRAFT/REVIEW/ACTIVE/...]
LINKS:  [Related artifacts if known]
```

The structured Eden schema may be completed later without erasing the original minimal record.

**Pattern must never overwrite record.**
