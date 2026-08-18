# Operation Eden Data Sovereignty Standard

**Document ID:** `EDEN-DATA-001`  
**Status:** Active Eden Standard  
**Layer:** Layer 1 / Layer 2  
**Scope:** Nodes, telemetry, governance, Commons, participant data, and data-sharing interfaces

---

## 1. Purpose

Operation Eden treats data sovereignty as an operational requirement, not a privacy slogan. The standard inherits two distinct Synthsara lineages:

- `SYN-DAT-002` — **Synthsara Data Ownership Model**, a historical precursor establishing user ownership, granular permissioning, selective disclosure, and the principle that data exchange must be opt-in rather than extractive.
- `SYN-DATA-011` — **Genesis Privacy Trinity Binding**, the later merged/binding implementation reference establishing zero-write private modes, revocable consent, consent receipts, data minimization, and testable privacy promises.

Historical token, staking, marketplace, and POWERcoin assumptions from the older data model are **not imported** into Operation Eden by this document.

---

## 2. Core Law

> **If a system cannot explain what it records, why it records it, who can access it, how long it persists, and how authorization can be revoked, the system has no right to retain it.**

For Operation Eden, local control is the default. Publication, federation, and external synchronization are explicit transitions, not assumed states.

---

## 3. Data Classes

### A. Environmental Telemetry
Examples: temperature, humidity, soil moisture, rainfall, water-quality measurements, equipment health.

- Raw telemetry is retained under the control of the local Node.
- EETU-01 must function without mandatory external synchronization.
- Publication to the Eden Commons is opt-in and selectively scoped.
- Cryptographic signatures prove record provenance and integrity; they do not grant a third party ownership over the underlying data.
- Environmental datasets intended for public release must be reviewed for accidental disclosure of participant identity, precise private-residence location, or other sensitive context.

### B. Participant and Community Data
Examples: names, contact details, identities, private discussions, learning records, health information, behavioral data, or personal profiles.

- Private and guest interactions default to zero persistent writes where technically applicable.
- No hidden profile enrichment.
- No secondary use without separate authorization.
- Consent must be granular, dynamic, revocable, and legible.
- Opt-out must be no harder than opt-in.

### C. Governance and Resource Records
Examples: proposals, decisions, budgets, project ledgers, appeals, steward actions.

- Institutional decisions and resource flows should be transparent to affected participants.
- Transparency does not justify publishing unnecessary private source material.
- Public receipts should record the decision, authority, scope, and evidence class while minimizing personal data.

### D. Knowledge Commons Contributions
Examples: Akasha entries, open designs, research notes, field protocols, failure reports.

- Publication is an explicit act of contribution.
- The contributor must know the license and intended visibility before publication.
- Public Commons material should use the applicable Operation Eden open license.

---

## 4. Consent Receipt Requirement

Every material change to a participant-facing consent state SHOULD generate a human-readable consent receipt. For systems that persist personal data, this becomes a MUST.

A receipt must state:

- what changed;
- what data or capability is affected;
- why the change is recorded;
- who can access the resulting data;
- retention behavior;
- whether federation or public sharing is enabled;
- how to revoke;
- how to export or request deletion where applicable.

---

## 5. Zero-Write Private Mode

Where an Eden digital service offers a private or guest mode, that mode MUST NOT silently create persistent interaction records.

Unless the participant explicitly opts in, private/guest mode must avoid:

- conversation records;
- hidden content hashes tied to the participant;
- extracted behavioral patterns;
- profile enrichment;
- contribution or reputation scoring;
- automatic Commons publication.

Operational diagnostics required for security or system stability must be minimized, documented, and separated from participant-content retention.

---

## 6. Federation Rule

A local Node may participate in the wider Eden federation without surrendering its raw data store.

Federation interfaces SHOULD support:

1. local retention of canonical raw records;
2. selective publication of derived or redacted datasets;
3. cryptographic integrity proofs where useful;
4. explicit synchronization scopes;
5. revocable credentials and access grants;
6. offline operation when the wider network is unavailable.

**Federation is interoperability, not custody transfer.**

---

## 7. Privacy Claims Must Be Testable

Every material privacy promise must map to a test, audit procedure, or observable implementation control.

Minimum test classes include:

- private mode creates no prohibited persistent interaction writes;
- consent-state changes generate receipts;
- revoked permissions stop future access;
- export output is human-readable;
- federation disabled means no external synchronization;
- public telemetry publication excludes disallowed private fields;
- local systems continue operating when external services are unavailable.

---

## 8. Migration Boundary

Operation Eden deliberately preserves the **data-sovereignty principles** of the Synthsara lineage while excluding unratified or superseded economic assumptions.

Imported:

- user/community control;
- granular permissioning;
- selective disclosure;
- revocation;
- consent receipts;
- zero-write private modes;
- data minimization;
- privacy claims backed by tests.

Not imported by this standard:

- POWERcoin;
- token staking;
- transferable governance influence;
- automatic data monetization;
- assumptions that blockchain registration alone establishes legal ownership or privacy.

---

## 9. Conformance Questions

Before an Eden artifact handling data is accepted:

- [ ] What data is collected?
- [ ] Who controls the canonical copy?
- [ ] Is collection necessary for the stated purpose?
- [ ] Is consent explicit where personal/community data is involved?
- [ ] Can authorization be revoked?
- [ ] Can the system operate without cloud access?
- [ ] Are public and private data paths separated?
- [ ] Are retention and deletion behaviors documented?
- [ ] Are privacy promises testable?
- [ ] Does federation preserve local sovereignty?

---

**LOCAL CONTROL FIRST · EXPLICIT SHARING · REVOCABLE CONSENT · TESTABLE PRIVACY**
