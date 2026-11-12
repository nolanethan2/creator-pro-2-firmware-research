# Motion planner and numeric-runtime reconstruction

The deeper pass reconstructs motion-block layout, acceleration profiles, queue traversal and existing extrusion-advance compensation. It also fixes important analysis-model problems. This is read-only reverse engineering; none of the emulator inputs were sent to a printer.

## What changed in Ghidra

Six comparison helpers return their result in processor flags, not an ordinary C return register. They now have explicit four-register return storage (NG/ZR/CY/OV). Callers show named flag tests instead of misleading constant branches. Binary64 helpers now have correct two-register double arguments/results and semantic names. This is an analysis signature, not a firmware patch.

There is still a specific limitation: **Ghidra's C rendering of the three hardware F32 comparison leaf functions drops finite NG/ZR/CY expressions**. Their raw VCMP/VMRS instruction semantics are correct in the listing, and their original instructions passed comparison tests. The leaf C bodies carry explicit warnings. Use the original instructions and `comparison-flags-verification.json`; do not copy those leaf C bodies into a replacement program. The signature improves caller dataflow but does not make every decompiled body authoritative.

The software-double exception helper at **0x0804B1F8** reads an embedded descriptor relative to LR and restores the outer caller's saved return address. Its calls do not continue into that descriptor as executable instructions. Twelve call sites are modeled as call-and-return. Twelve exceptional arithmetic cases (including infinity, NaN, zero division and negative square root) returned to the original caller with the expected result classification. This supports the local control-flow correction. The final export no longer has the previous four bad-instruction warnings at the embedded descriptor. Other decompiler warnings and exceptional-path interpretation remain possible.

## Motion block and planner flow

The ring at **0x20009A9C** contains 16 records of **128 bytes**, ending immediately before axis data at 0x2000A29C. Head is byte 0x200005B1 and tail is byte 0x200005B2. The modulo-16 count makes the maximum distinguishable queued count 15; empty is head == tail. All 256 valid head/tail pairs were checked for count, emptiness, current-block selection/busy marking and discard.

| Address | Recovered function |
|---|---|
| 0x0802A37C | Planner_BuildMotionBlock |
| 0x08029D88 | Planner_CalculateTrapezoid |
| 0x0802A066 / 0x0802A0EC | Reverse block pass / reverse ring pass |
| 0x0802A132 / 0x0802A274 | Forward block pass / forward ring pass |
| 0x0802A2A8 | Recalculate adjacent trapezoids |
| 0x0802A32C | Reverse → forward → trapezoid lookahead sequence |
| 0x0802A33C | Reset queue, prior motion and advance factors |
| 0x08049D00 | Queue count |
| 0x08049D3C | Select current block and mark busy |
| 0x08049D18 | Discard current block |
| 0x08049A34 / 0x08049B90 | Acceleration/deceleration speed helpers |

`planner-block-layout.csv` gives the recovered field offsets. Direction bits are at +0x38, tool at +0x39, nominal rate at +0x60, initial/final rates at +0x68/+0x6C, acceleration at +0x70 and busy at +0x76. Some flag meanings remain explicitly tentative.

## Acceleration model

For the finite, nonoverflowing accelerated cases tested, initial/final rates are derived from nominal rate times entry/exit fractions (fractions above one are capped), rounded by adding 0.5 then truncating, and clamped to **at least 120 step events per second**. Acceleration and deceleration distances follow squared-rate differences divided by twice the event-space acceleration. When they would overlap, the implementation computes a triangular intersection and clamps it to the event-count interval. Active blocks marked busy do not receive the final profile writes.

The isolated routine permits negative acceleration-distance results when artificially supplied nominal rates below its 120 floor. A seeded nominal rate of 100 produced accelerate-until −2; that does not prove normal higher-level motion generation supplies that combination. Caller constraints must be preserved before interpreting this as a printer defect.

The two speed helpers implement sqrt(max(0, v² + 2ad)) and sqrt(max(0, v² − 2ad)), with mixed float32/float64 rounding. **1,024 finite cases** matched an independently rounded reference. **134 profile cases plus seven busy/nonaccelerated/advance cases** passed with only the interrupt wrapper intercepted. Lookahead pass roles are statically reconstructed; this is not exhaustive multi-block dynamic validation.

## Existing extrusion advance and limits

Decoded initialized configuration contains uint32 values **850** and **900** at machine-configuration offsets **+0x44** and **+0x48** (RAM 0x20000154/158). Planner initialization divides these by **100000**, producing approximately **0.0085** and **0.009** at RAM 0x20000590/594. Ten isolated block-construction cases confirm that the mixed X-plus-extrusion case enables the advance branch, while pure XYZ and pure extrusion do not. This is existing compensation code with nonzero defaults. Its factors are not established as interchangeable with Marlin or Klipper tuning parameters, and no supported runtime tuning command has been established here.

Initialization caps the two inspected acceleration fields at **10000**. An initialized slowdown flag selects a low-water queue threshold of **8**. In the seeded four-block case, the block builder reduced requested nominal speed from 20 to 10. Speed limiting has multiple layers: for a deliberately excessive seeded X request of 1000, the inspected per-axis clamp gate produced 150, while the other gate setting still limited the result to 500 through a separate minimum-segment-time path. These artificial builder inputs are not a usable speed-unlock recipe or measured printer limits.

Four initialization cases ran original arithmetic with axis/I/O/reset/timer calls intercepted. Ten block cases ran the original builder and trapezoid but intercepted lower-level setup, motor-request/interrupt wrappers and final multi-block lookahead. These scope limits are included in the JSON results.

## Numeric checks and practical continuation

**6,384 finite comparison cases** established CY/ZR relations and captured all NZCV patterns encountered. Software-double N/V values are not interchangeable with hardware floating-point comparison flags; mixed-sign integer-CMP patterns differ. **5,161 finite arithmetic/conversion cases** matched the reference operations, including half-integer ties-to-even and signed-zero rounding. Twelve exceptional cases additionally exercised descriptor dispatch and result classification. Subnormals, alternate rounding modes, overflow boundaries and every NaN payload are not exhaustively covered.

Start in Ghidra at `Planner_CalculateTrapezoid` to see typed fields, then follow `Planner_BuildMotionBlock` and the three lookahead passes. For unresolved work, prioritize full command-to-stepper execution, homing/calibration and interruption/recovery state interactions. A flash dump cannot by itself establish mechanical calibration, electrical signal timing, or the contents of external persistent storage.
