# Operation Eden Governance Mechanism Design Profile

**Document ID:** `EDEN-GOV-001`  
**Status:** Active Design Specification · Requires Simulation and Field Validation  
**Layer:** Layer 2 (Governance Infrastructure)  
**Primary Source:** `SYN-GOV-001` — *Synthsara: An Executable Mechanism-Design Specification*

---

## 1. Purpose

Operation Eden requires governance that can coordinate real people, land, tools, money, ecological interventions, and shared infrastructure without collapsing into either centralized control or unstructured consensus paralysis.

This document adapts the strongest formal Synthsara governance specification into an Eden-specific mechanism profile.

The source explicitly treats its governance architecture as a **falsifiable institutional and computational hypothesis**, not as proof of universal incentive compatibility, permanent Sybil resistance, perfect privacy, or immunity from capture. Operation Eden adopts that same bounded stance.

---

## 2. Constitutional Ordering

Governance mechanisms are subordinate to the following order:

1. `DECLARATION_OF_EDEN.md`
2. `standards/UDS_EDEN_PROFILE.md`
3. `standards/DATA_SOVEREIGNTY.md`
4. Local Node Charter
5. Approved operational procedures and proposals

No proposal may gain legitimacy merely because it receives votes if it violates a higher constitutional layer.

---

## 3. Subsidiarity Rule

> **A decision should be made at the smallest practical scope containing the people, land, resources, and risks materially affected by that decision.**

A local garden schedule does not require federation approval. A shared protocol affecting every Node does not belong to one local steward.

Decision scopes:

- **Project Scope** — individual Seed Project or working group.
- **Node Scope** — one physical Eden Node.
- **Regional/Federated Scope** — interoperability or shared resources across multiple Nodes.
- **Constitutional Scope** — changes to Eden-wide invariants, conformance rules, or protected rights.

---

## 4. Proposal Lifecycle

```text
[ PROPOSE ]
     │
     ▼
[ SCOPE + CONFLICT CHECK ]
     │
     ▼
[ DISCLOSE COST / RISK / AUTHORITY ]
     │
     ▼
[ DELIBERATE ]
     │
     ▼
[ CONSENT / DECISION RULE ]
     │
     ▼
[ EXECUTE WITH BOUNDED AUTHORITY ]
     │
     ▼
[ AUDIT + MEASURE ]
     │
     ├────────────► [ APPEAL / CORRECTION ]
     │
     ▼
[ RETAIN · REVISE · REVOKE ]
```

Every significant proposal should identify:

- decision scope;
- affected parties;
- requested authority;
- required resources;
- expected ecological/social benefit;
- known risks;
- reversibility;
- evidence standard;
- review date;
- appeal path.

---

## 5. Due Process Is Structural

No automated score, steward, council, or AI advisory system may impose a permanent sanction without documented process.

Minimum due-process requirements:

- notice of the issue;
- access to the evidence appropriate to the case;
- opportunity to respond;
- conflict-of-interest screening;
- bounded timelines;
- proportionate interim measures where necessary;
- appeal;
- correction of erroneous records;
- restoration pathway where feasible.

The source mechanism specifically distinguishes compromised participants from permanently malicious identities. Eden therefore treats behavior and incidents as contestable evidence, not immutable moral classification.

---

## 6. Contribution Signals and Anti-Goodhart Boundary

The Synthsara source formalizes WORTH as a **capped, delayed, non-transferable governance signal** separated from transferable compensation and explicitly rejects treating it as a measure of intrinsic human value, emotional depth, healing, or moral superiority.

Operation Eden therefore adopts the following boundary:

- Eden MAY later adopt a contribution signal under a separate ratified specification.
- No contribution metric may equal human worth.
- Money may not directly purchase governance authority.
- Private psychological disclosure may not generate political power.
- Contribution signals must be contestable, contextual, and resistant to simple metric gaming.

**Until a separate Eden contribution protocol is ratified, no WORTH-based voting rule is active in Operation Eden.**

---

## 7. AI Authority Boundary

AI systems may assist with:

- summarization;
- proposal comparison;
- conflict detection;
- simulation;
- evidence organization;
- policy consistency checks;
- translation and accessibility.

AI systems do not become sovereign decision-makers merely because they are useful.

Any AI governance support must remain:

- capability-bounded;
- explainable enough for affected participants to review;
- subject to human appeal;
- unable to silently expand its own authority;
- subordinate to the UDS Eden Profile and local/federated charters.

---

## 8. Threat Model

Eden governance must assume participants and institutions can be mistaken, strategic, compromised, collusive, exhausted, bribed, captured, or sincerely divided.

At minimum, governance testing must model:

- Sybil participation;
- collusion;
- bribery or external subsidy;
- steward capture;
- false reporting;
- validator bias;
- privacy leakage;
- strategic metric gaming;
- emergency-power abuse;
- quorum manipulation;
- low-participation capture;
- compromised credentials;
- off-platform coercion that the protocol cannot fully observe.

No mechanism document may claim to eliminate risks that remain outside its observable system boundary.

---

## 9. Simulation Before Expansion

Governance rules with material authority SHOULD be adversarially simulated before federation-wide deployment.

Comparative evaluation should ask whether the proposed mechanism improves outcomes relative to simpler alternatives, rather than comparing itself only to an idealized baseline.

Candidate metrics include:

- participation rate;
- concentration of decision power;
- false-sanction rate;
- appeal reversal rate;
- time-to-resolution;
- governance capture rate;
- extraction or rent concentration;
- participation cost;
- resilience under identity attacks;
- recovery after compromised actors or infrastructure failures.

A failed preregistered threshold is evidence about the mechanism and must be documented as such.

---

## 10. Emergency Powers

Emergency authority must be:

- explicitly scoped;
- time-limited;
- logged;
- reviewable;
- automatically expired unless renewed under ordinary governance;
- unable to permanently amend constitutional rights through emergency procedure alone.

---

## 11. Governance Acceptance Gate

Before a governance mechanism moves from proposal to active Node use:

- [ ] Decision scope is defined.
- [ ] Constitutional conflicts have been checked.
- [ ] Authority is bounded and revocable.
- [ ] Due process and appeal exist.
- [ ] Privacy/data implications are documented.
- [ ] Economic influence cannot silently purchase political authority.
- [ ] AI authority, if any, is advisory/capability-bounded.
- [ ] Threat model is documented.
- [ ] Failure criteria are explicit.
- [ ] Simulation or pilot evidence is attached where the mechanism is high-impact.

---

## 12. Research Boundary

This document is an **adapted operational profile**, not proof that the mechanism is optimal or stable under every population and threat model.

Operation Eden governance earns legitimacy through:

**clear rules → adversarial testing → limited pilots → public evidence → correction.**
