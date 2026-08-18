# Eden Node Starter Kit (v0.1)
**Document ID:** `ENSK-001`  
**Status:** Working Specification  
**Provenance:** Derived from `SYN-AKA-003` (Node Starter Kit Architecture)  
**Objective:** Minimum viable operational and safety skeleton for bootstrapping an autonomous physical Eden Node.

---

## 1. The Minimum Viable Node (MVN)

An Eden Node does not require hundreds of acres or millions in capital to begin. An MVN is established the moment a committed cohort links **One Land Parcel**, **One Telemetry Unit**, **One Food/Restoration Plot**, and **One Open Commons Log**.

```text
MINIMUM VIABLE NODE
┌──────────────────────────────────────────────────────────────┐
│ LAND ACCESS      ──► Sovereign lease, trust, or agreement   │
│ NERVOUS SYSTEM   ──► EETU-01 telemetry & baseline log       │
│ SOIL ACTION      ──► 1 bio-intensive plot / watershed zone  │
│ GOVERNANCE       ──► Local charter + Subsidiarity Council   │
│ COMMONS UPLINK   ──► Git repo publishing to Eden Commons    │
└──────────────────────────────────────────────────────────────┘
```

---

## 2. Bootstrapping Sequence (90-Day Onboarding)

### Phase A: Alignment & Covenant (Days 1–15)
1. **Adopt the Standards:** Formally ratify the [Declaration of Eden](../../DECLARATION_OF_EDEN.md) and [UDS Eden Profile](../../standards/UDS_EDEN_PROFILE.md).
2. **Form the Local Circle:** Identify a minimum core cohort of 3–7 stewards across ecology, technical systems, food production, and conflict facilitation.
3. **Draft Local Charter:** Complete the `LOCAL_CHARTER_TEMPLATE.md` defining local decision consent models and dispute mediation.

### Phase B: Baseline & Observation (Days 16–45)
1. **Deploy Observation Hardware:** Assemble and install at least one `EETU-01` unit at the site core.
2. **Execute Ecological Baseline:** Follow `OETS-001` Section 6 to log 14 days of uninterrupted soil, microclimate, and water baseline data before disturbing the soil.
3. **Map the Hydrology & Sunlight:** Create the initial open-source site GIS map (elevation, water flow, solar exposure).

### Phase C: First Interventions (Days 46–75)
1. **Ecological Seed Action:** Execute one high-priority restoration pilot (e.g., swale construction, native guild planting, contaminated soil bioremediation).
2. **Agricultural Seed Action:** Establish the first food-producing bio-intensive bed or perennial food forest guild.
3. **Log All Incurred Costs:** Maintain an itemized ledger of every penny spent, hour volunteered, and material sourced.

### Phase D: Commons Integration (Days 76–90)
1. **Publish Node File:** Register the node in `nodes/registry/` with geographic context, stewardship contact signature, and active projects.
2. **Publish First Akasha Entry:** Document the baseline, intervention, costs, and early data using the `AKASHA_ENTRY_SCHEMA.md`.
3. **Open Failure Register:** Log every initial mistake, dead plant, and sensor bug in the node's public failure log.

---

## 3. Node Starter Kit Directory Structure

When a new Node repo or sub-directory is created, it should instantiate the following scaffolding:

```text
eden-node-[country]-[region]-[number]/
├── CHARTER.md               # Local governance, meeting cadence, consent protocol
├── SITE_MAP.md              # Boundary polygons, zoning, watershed maps
├── LEDGER.md                # Transparent financial and resource flows
├── telemetry/               # Local logs, daily Merkle roots, EETU config
├── interventions/           # Active farming and ecological experiment logs
├── commons-sync/            # Published Akasha entries and replication kits
└── FAILURE_LOG.md           # Continuous public register of defects and lessons
```

---

## 4. The Golden Rule of Node Sovereignty

> **No central board, algorithm, or federation body may dictate the internal daily life, spiritual culture, or local land-use decisions of an individual Node, provided the Node operates within the non-extractive, transparent, and life-serving boundaries of the Universal Diamond Standard.**
