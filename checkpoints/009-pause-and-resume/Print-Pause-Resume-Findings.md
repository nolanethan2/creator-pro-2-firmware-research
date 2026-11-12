# Print pause/resume state recovery

The seven-entry Thumb branch table at **0x080121B2** was manually recovered from its bounds check and original byte offsets. Its index is **state - 0x81**, with values 0..6. This repaired a previously incomplete decompiled view of **0x0801217E**. The original flash bytes were not modified.

The state byte is **0x2000004E**. Pause and resume paths use planner waits, captured temperature targets and saved motion coordinates. The following sequence is now visible in the decompiler and was checked by offline execution of the original dispatch instructions.

| State | Observed operation | Next state |
|---|---|---|
| 0x40 | Invoke six-channel policy/snapshot helper with argument 1 | 0x41 |
| 0x41 | Wait for planner empty | 0x42 |
| 0x42 | Save motion position; invoke pause extrusion action with argument 1 | 0x43 |
| 0x43 | Wait for planner empty | 0x44 |
| 0x44 | Invoke pause-position path, capture fan/output bit and heater targets; optionally shut down heaters | 0x45 |
| 0x45 | Wait for planner empty; finish pause UI | 1, or 0x20 when pending flag at 0x2000002B is set |
| 0x80 | Restore bed/extruder target requests, apply tool-selection conditions; show heating status | 0x81 |
| 0x81 | Wait for bed readiness when saved bed target is positive | 0x83 |
| 0x82 | Default/no-op branch | unchanged |
| 0x83 | Wait for required extruders according to saved target/tool flags | 0x84 |
| 0x84 | Apply policy helper, invoke saved-position restoration path | 0x85 |
| 0x85 | Wait for planner empty | 0x86 |
| 0x86 | Invoke reverse pause-extrusion action with argument 0 | 0x87 |
| 0x87 | Wait for planner empty, call completion hook and close status dialog | 0 |

The normal state-0x45 branch to 1 was tested; the alternative pending-flag branch to 0x20 is identified statically, not included in the current transition tests. The table's missing 0x82 behavior should not be filled in from an assumed consecutive sequence.

## Verification scope

**print-state-verification.json** records **13 transition tests and seven hold cases**. Planner-busy cases preserve states 0x41, 0x43, 0x45, 0x85 and 0x87. Heater-not-ready cases preserve states 0x81 and 0x83 with positive saved targets.

The tests execute the firmware's original state-dispatch ARM instructions in Unicorn. Motion/extrusion functions, UI, GPIO reads, heater setters/readiness and planner status are deterministic stubs. Actual heater target getters run against mapped RAM. This verifies branch sequencing and waiting, not physical motion distances, extrusion direction under every tool configuration, reheat timing or hardware safety.

## Related helpers and unresolved details

- **0x08011BE2:** iterates six channel-policy entries and calls get/set/clear helpers. It must not be renamed as generic motor enable without characterizing those helpers.
- **0x08011C28:** adjusts extruder motion only when target/readiness checks permit; argument 1 and argument 0 are opposite pause/resume actions. Exact physical amounts require configuration interpretation.
- **0x08011D00:** argument 1 prepares a pause move after checking XYZ state; argument 0 restores saved logical coordinates and resynchronizes extrusion positions. Portions remain affected by software-float decompiler artifacts.
- **0x08011C1A:** the inspected code is effectively an empty six-iteration loop; do not infer a hardware restoration operation from its position in the state flow.
- **0x08015B04:** the inspected completion hook returns immediately.
- **0x0801BF76:** closes the status window and clears its handle.

This adds a recovered control path, not a newly unlocked feature. Full interruption/recovery behavior across power loss, malformed jobs and all IDEX states remains unproven.
