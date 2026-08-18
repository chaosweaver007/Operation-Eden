# Operation Eden Knowledge Commons Taxonomy

**Document ID:** `AKTX-001`  
**Status:** Active Eden Adaptation  
**Layer:** Layer 2 (Knowledge Commons)  
**Primary Source:** `SYN-AKA-002` — *Library Taxonomy + Folder Map*

---

## 1. Purpose

A Commons without a shared classification system becomes a pile of files. This taxonomy adapts the Synthsara Akasha tagging model to Operation Eden so experiments, designs, failures, datasets, and governance records remain findable across Nodes.

The source taxonomy requires each entry to identify **what it is**, **where it is in its lifecycle**, and **what it is about**. Eden preserves that rule while aligning status vocabulary with `AKASHA_ENTRY_SCHEMA.md` and the existing repository structure.

---

## 2. Required Classification Dimensions

Every published Akasha entry MUST include:

1. **Type** — what kind of artifact is this?
2. **Status** — where is it in its lifecycle?
3. **Domain** — which Eden system does it primarily belong to?
4. **Topics** — what specific subjects does it address?

---

## 3. Type Tags

Canonical type tags:

- `type:text` — written specification, article, report, protocol, or narrative.
- `type:image` — photograph, diagram, map, or static visual.
- `type:audio` — field recording, interview, music, or other audio artifact.
- `type:video` — recorded demonstration, instruction, meeting, or animation.
- `type:code` — software repository, script, firmware, schema, or code sample.
- `type:hardware` — schematic, PCB, mechanical design, BOM, or field device.
- `type:dataset` — structured measurements or observation records.
- `type:artifact` — reusable tool, template, checklist, or downloadable package.
- `type:discussion` — meeting, deliberation, workshop, or conversation summary.

An entry may carry more than one type when necessary, but one SHOULD be designated primary.

---

## 4. Status Tags

The original Akasha taxonomy used `draft`, `review`, `active`, `archived`, `deprecated`, and `disputed`. The Eden Akasha Entry Schema introduced a more empirical lifecycle.

Operation Eden standardizes on:

- `status:draft` — work in progress.
- `status:in-review` — ready for critique, not yet approved.
- `status:bench-testing` — undergoing controlled technical validation.
- `status:field-testing` — deployed in a real environment, evidence incomplete.
- `status:validated` — acceptance criteria have been met for the declared scope.
- `status:superseded` — replaced by a newer artifact.
- `status:failed` — did not meet declared acceptance criteria; retained as useful evidence.
- `status:disputed` — accuracy, provenance, authorship, ownership, or interpretation is actively contested.
- `status:archived` — retained for history and no longer active.

### Source-to-Eden status mapping

| Source taxonomy | Eden status |
|---|---|
| `draft` | `draft` |
| `review` | `in-review` |
| `active` | `validated` or `field-testing`, depending on evidence |
| `deprecated` | `superseded` |
| `archived` | `archived` |
| `disputed` | `disputed` |

**Important:** `validated` is scope-bounded. It does not mean universally true or permanently correct.

---

## 5. Domain Tags

These align with `AKASHA_ENTRY_SCHEMA.md`:

- `domain:ecology`
- `domain:agriculture`
- `domain:technology`
- `domain:governance`
- `domain:infrastructure`
- `domain:health`
- `domain:culture`

Recommended Eden extensions:

- `domain:education`
- `domain:economy`
- `domain:data`

When an entry spans domains, select one primary domain and use topics for the rest.

---

## 6. Topic Tags

Core cross-cutting topics inherited from the Akasha lineage include:

- `topic:governance`
- `topic:ethics`
- `topic:ai`
- `topic:systems-thinking`
- `topic:community`
- `topic:reciprocity`
- `topic:consent`
- `topic:research`
- `topic:design`

Operation Eden adds field-oriented topics:

- `topic:telemetry`
- `topic:soil`
- `topic:water`
- `topic:biodiversity`
- `topic:food-production`
- `topic:energy`
- `topic:repairability`
- `topic:open-hardware`
- `topic:open-source`
- `topic:data-sovereignty`
- `topic:privacy`
- `topic:restoration`
- `topic:baseline`
- `topic:replication`
- `topic:failure-analysis`
- `topic:education`
- `topic:node-governance`

Tags should be added when they materially improve retrieval, not as decorative metadata.

---

## 7. Example Eden Classification

```yaml
type:
  - "type:text"
  - "type:dataset"
status: "status:field-testing"
domain: "domain:ecology"
topics:
  - "topic:water"
  - "topic:restoration"
  - "topic:telemetry"
  - "topic:baseline"
  - "topic:replication"
```

---

## 8. Repository Placement Rule

The historical Synthsara taxonomy used a top-level numbered folder map for Mad Lab production, Akasha, projects, discussions, and archive. Operation Eden already has a functional domain-oriented repository topology, so the old folder map is preserved as provenance rather than copied literally.

Use the current Eden structure:

```text
Operation-Eden/
├── standards/
├── governance/
├── knowledge-commons/
├── seed-projects/
├── nodes/
├── specs/
├── hardware/
├── firmware/
├── protocol/
├── tools/
├── docs/
├── provenance/
└── impact/
```

Artifact placement SHOULD follow function. Akasha metadata provides cross-cutting retrieval without forcing every idea into one folder hierarchy.

---

## 9. Cartographer's Rule

When creating an artifact:

1. Give it a clear, descriptive name.
2. Put it in the most appropriate functional directory.
3. Add Akasha metadata when it enters the Commons.
4. Use a lifecycle status that reflects evidence, not enthusiasm.
5. Link superseded versions instead of erasing history.
6. Preserve failed work when it teaches the network something.

When searching:

1. Search the functional directory.
2. Search Akasha metadata and tags.
3. Follow provenance links.
4. Check `superseded`, `failed`, `disputed`, and `archived` material when reconstructing history.

---

## 10. Duplicate and Migration Rule

The source registry explicitly identifies duplicate-resolution and migration workflows as unfinished work. Until a dedicated deduplication protocol is ratified:

- do not silently overwrite distinct artifacts with the same title;
- preserve source IDs and version identifiers;
- mark replacements as `superseded` rather than deleting them;
- record migration provenance in `provenance/SOURCE_REGISTRY.md`;
- prefer canonical repository paths over detached duplicates once a migration has been formally accepted.

---

**FINDABLE KNOWLEDGE IS USABLE KNOWLEDGE. PRESERVE THE PATH THAT PRODUCED IT.**
