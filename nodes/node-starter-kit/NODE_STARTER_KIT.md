# Eden Node Starter Kit (v0.1)

**Document ID:** `ENSK-001`  
**Status:** Working Specification  
**Provenance:** Adapted from `SYN-AKA-003` — Synthsara Mad Lab Node Starter Kit  
**Objective:** Minimum viable operational, documentation, safety, and replication skeleton for bootstrapping an autonomous physical Eden Node.

---

## Provenance Note

The parent `SYN-AKA-003` artifact defines a **software-project node bootstrap** built around the rule **Ship Small, Ship Safe**. It requires every new project node to begin with clear documentation, licensing, contribution rules, secret hygiene, and an Akasha record.

Operation Eden preserves that repository discipline and **extends the meaning of node into physical geography**: land, telemetry, restoration, food systems, local governance, and Commons participation.

This document is therefore an expansion of the source architecture, not a claim that the historical Mad Lab artifact already specified physical communities.

---

## 1. The Minimum Viable Node (MVN)

An Eden Node does not require hundreds of acres or millions in capital to begin.

An MVN exists when a committed local cohort links:

1. **One lawful land-access arrangement**
2. **One observation system**
3. **One ecological or food-producing intervention**
4. **One local governance charter**
5. **One open Commons record**

```text
MINIMUM VIABLE NODE
┌──────────────────────────────────────────────────────────────┐
│ LAND ACCESS      ──► Lease, trust, ownership, or agreement  │
│ NERVOUS SYSTEM   ──► EETU-01 telemetry & baseline log       │
│ SOIL ACTION      ──► Food plot / restoration zone           │
│ GOVERNANCE       ──► Local charter + subsidiarity process   │
│ COMMONS UPLINK   ──► Git repository + Akasha entries        │
└──────────────────────────────────────────────────────────────┘
```

A Node begins as a testable local system, not as a claim of utopia.

---

## 2. Repository Bootstrap: Ship Small, Ship Safe

Before a Node publishes operational data or code, its repository should contain:

```text
README.md
LICENSE / LICENSES.md
CONTRIBUTING.md
.gitignore
AKASHA.md
CHARTER.md
FAILURE_LOG.md
```

### Required functions

- `README.md` explains what the Node is, what problem it addresses, how to understand its current status, and how to participate.
- `LICENSE` or `LICENSES.md` defines reuse terms and preserves upstream obligations.
- `CONTRIBUTING.md` defines safe participation, issue reporting, contribution workflow, and review expectations.
- `.gitignore` prevents credentials, private keys, local secrets, `.env` files, private datasets, and other sensitive material from entering version control.
- `AKASHA.md` is the Node's own Knowledge Commons provenance entry.
- `CHARTER.md` defines local governance and decision processes.
- `FAILURE_LOG.md` preserves defects, mistakes, abandoned approaches, ecological surprises, and lessons.

**Never commit private keys, credentials, sensitive personal data, or unnecessary private records.**

---

## 3. Bootstrapping Sequence (90 Days)

### Phase A — Alignment & Covenant (Days 1–15)

1. **Adopt the Standards**  
   Formally adopt the [Declaration of Eden](../../DECLARATION_OF_EDEN.md) and [UDS Eden Profile](../../standards/UDS_EDEN_PROFILE.md) for Node operations.

2. **Form the Local Circle**  
   Identify a core cohort able to cover ecological knowledge, technical systems, food/restoration work, administration, and conflict facilitation. Small teams may combine roles.

3. **Document Land Access**  
   Record the lawful basis for using the site, duration of access, restrictions, and stewardship responsibilities. Do not publish sensitive personal information unnecessarily.

4. **Draft Local Charter**  
   Define proposal flow, stewardship scope, decision rules, consent boundaries, financial transparency, dispute mediation, appeal, and amendment procedures.

### Phase B — Baseline & Observation (Days 16–45)

1. **Deploy Observation Hardware**  
   Assemble and install at least one suitable environmental telemetry unit. `EETU-01` is the reference architecture, not a mandatory vendor-specific product.

2. **Execute Ecological Baseline**  
   Follow the current OETS baseline methodology or an equivalent documented method before intervention where feasible.

3. **Map the Site**  
   Record relevant boundaries, slope, hydrology, sunlight, access routes, existing vegetation, soil zones, utilities, and hazards.

4. **Create the First Akasha Record**  
   Record what the site is, why it was selected, source/provenance, responsible stewards, status, and related artifacts using `AKASHA_ENTRY_SCHEMA.md`.

### Phase C — First Interventions (Days 46–75)

1. **Ecological Seed Action**  
   Execute one bounded restoration pilot appropriate to the site.

2. **Agricultural Seed Action**  
   Where appropriate, establish one measurable food-producing or soil-building pilot.

3. **Track Inputs**  
   Record material costs, purchased services, donated materials, volunteer hours where contributors consent to aggregation, energy use where useful, and major maintenance requirements.

4. **Preserve Control / Reference Conditions**  
   Where practical, retain comparable untreated or reference areas so claims of improvement have context.

### Phase D — Commons Integration (Days 76–90)

1. **Publish Node Manifest**  
   Register the Node in `nodes/registry/` with non-sensitive geographic context, current stewardship contact method, status, active projects, and repository link.

2. **Publish First Full Akasha Entry**  
   Document baseline, intervention, costs, evidence, uncertainty, and early results.

3. **Open Failure Register**  
   Log initial mistakes, dead plants, sensor faults, process breakdowns, and corrective actions without turning the record into a punitive dossier.

4. **Review Conformance**  
   Run the Node against `UDS_EDEN_PROFILE.md` and document unresolved gaps.

---

## 4. Node Directory Structure

```text
eden-node-[country]-[region]-[number]/
├── README.md
├── LICENSES.md
├── CONTRIBUTING.md
├── .gitignore
├── AKASHA.md
├── CHARTER.md
├── SITE_MAP.md
├── LEDGER.md
├── FAILURE_LOG.md
│
├── telemetry/
│   ├── README.md
│   ├── configs/
│   ├── manifests/
│   └── public-data/
│
├── interventions/
│   ├── ecological/
│   └── agricultural/
│
├── commons-sync/
│   ├── entries/
│   └── replication-kits/
│
└── governance/
    ├── proposals/
    ├── decisions/
    └── appeals/
```

Sensitive raw data should remain local when publication would violate consent, privacy, safety, or legitimate site-security needs. The Commons should receive only the shareable layer.

---

## 5. Minimum Node Records

Every active Node should maintain:

- current charter;
- current steward/contact record;
- land-access basis;
- ecological baseline or reason one cannot yet be established;
- active intervention register;
- transparent resource ledger appropriate to the project;
- telemetry/data policy;
- failure log;
- Akasha provenance entry;
- UDS Eden conformance review;
- replication notes.

---

## 6. Node Sovereignty Rule

> **No central board, algorithm, interface, or federation body may dictate the ordinary internal life, spiritual culture, or local operating choices of an Eden Node merely because it participates in the federation.**

Local autonomy is bounded by the conditions attached to use of the Operation Eden designation: transparency, non-extraction, sovereignty, fairness, accountability, security, privacy, service to life, ecology, due process, and the documented Eden extensions in `UDS_EDEN_PROFILE.md`.

Federation may determine whether a project remains **recognized as an Operation Eden Node**; federation does not thereby acquire ownership of the local community.

---

## 7. Replication Exit Condition

A Node is considered replication-ready when another independent group can understand:

- what was attempted;
- what resources it required;
- what rules governed it;
- what evidence was collected;
- what succeeded;
- what failed;
- what remains uncertain;
- what should be changed next time.

A Node that cannot teach another Node has not yet completed the replication loop.

**Ship small. Ship safe. Record what matters. Let evidence improve the pattern.**
