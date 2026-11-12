import os
from pathlib import Path
import csv,json,re,collections
out=Path(__file__).resolve().parent.parent/'outputs'
labels=list(csv.DictReader((out/'function-labels.tsv').open(encoding='utf-8'),delimiter='\t'));count=len(labels)
fields=[(0,20,'uint32[5]','axis_steps','absolute step counts'),(0x14,4,'uint32','step_event_count','dominant event count'),(0x18,20,'int32[5]','start_steps','prior planner position'),(0x2c,4,'int32','accelerate_until','profile boundary'),(0x30,4,'int32','decelerate_after','profile boundary'),(0x34,4,'int32','acceleration_rate_fixed','scaled ISR acceleration term'),(0x38,1,'uint8','direction_bits','five axis direction bits'),(0x39,1,'uint8','extruder_index','selected extrusion channel'),(0x3a,1,'uint8','request_flags_unresolved','constructor fifth argument'),(0x3b,1,'uint8','advance_enabled','extrusion advance branch'),(0x3c,2,'int16','advance_initial','advance increment term'),(0x3e,2,'int16','advance_final','advance decrement term'),(0x40,4,'int32','advance_rate_adjustment','secondary factor contribution'),(0x44,4,'int16[2]','advance_state','working advance terms'),(0x48,4,'float32','nominal_speed','accelerated path speed'),(0x4c,4,'float32','entry_speed','lookahead entry limit'),(0x50,4,'float32','max_entry_speed','junction limit'),(0x54,4,'float32','move_length','path length'),(0x58,4,'float32','acceleration','physical-space acceleration'),(0x5c,1,'uint8','recalculate','profile needs recalculation'),(0x5d,1,'uint8','nominal_length','sufficient-distance flag'),(0x60,4,'uint32','nominal_rate','nominal step event rate'),(0x64,4,'uint32','nominal_rate_squared','squared event rate'),(0x68,4,'uint32','initial_rate','clamped starting event rate'),(0x6c,4,'uint32','final_rate','clamped final event rate'),(0x70,4,'uint32','acceleration_steps','event-space acceleration'),(0x74,1,'uint8','accelerated','acceleration mode flag'),(0x75,1,'uint8','lookahead_ready','lookahead working flag'),(0x76,1,'uint8','busy','active block protected against profile rewrite'),(0x77,1,'uint8','dominant_axis','event-count source axis'),(0x78,1,'uint8','endstop_flags_candidate','partially inferred semantics'),(0x7c,4,'uint32','command_marker','copied command metadata')]
with (out/'planner-block-layout.csv').open('w',newline='',encoding='utf-8')as f:w=csv.writer(f);w.writerow(['offset','bytes','type','field','evidence_scope']);w.writerows((f'0x{o:02X}',n,t,k,d)for o,n,t,k,d in fields)
text='''# Motion planner and numeric-runtime reconstruction

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
'''
(out/'Motion-Planner-and-Runtime-Findings.md').write_text(text,encoding='utf-8')
diff=json.loads((out.parent/'work/gui-analysis-diff.json').read_text());merge=list(csv.DictReader((out/'deep-analysis-function-merge.tsv').open(),delimiter='\t'));review=dict(gui_function_count=diff['gui_functions'],previous_function_count=diff['old_functions'],additional_entries=len(diff['additional']),missing_previous_entries=len(diff['missing_from_gui']),imported_entries=sum(r['status'].startswith('imported')for r in merge),flash_sha256=json.loads((out.parent/'work/gui-review-verification.json').read_text())['flash_sha256'],gui_review_archive='work/GUI-DeepRun.gzf',scope='New boundaries and source-byte integrity checked. Automatic roles remain unreviewed unless separately labeled. Existing annotated RAM/types retained; one shared-tail boundary split was reviewed in disassembly.')
(out/'deep-analysis-review.json').write_text(json.dumps(review,indent=2))
(out/'Deep-Analysis-Review.md').write_text(f'''# Review of the completed desktop analysis

Your completed Ghidra program reports **{diff['gui_functions']:,} functions**, compared with **{diff['old_functions']:,}** before. It retains all previous function entry points and adds **{len(diff['additional'])}**. Its 1 MiB flash hash matches the original backup.

A separate snapshot was saved at `work/GUI-DeepRun.gzf` and imported into an isolated review project. The additions are mostly low-level boot/application device support, plus display and GUI routines. **{review['imported_entries']} additional entries** were incorporated into the annotated analysis while retaining the newer RAM reconstruction, types and runtime-flow fixes. One overlap required a reviewed split: 0x0803CA30 loads four signed rectangle fields and tail-branches to the implementation at 0x0803C9D8. Both entry points now have appropriate bodies.

The combined program has **2,317 recovered functions and {count} curated semantic labels**. Recovery counts do not measure complete understanding: newly recovered automatic functions still need semantic review. The user's desktop project remains separate; the package GZF is the combined annotated result. No firmware bytes or printer settings were changed.

See `deep-analysis-function-merge.tsv` for every imported entry and `Motion-Planner-and-Runtime-Findings.md` for the parallel deeper motion/runtime work.
''',encoding='utf-8')
p=out/'Deconstruction-Report.md';s=p.read_text(encoding='utf-8');s=re.sub(r'The analysis recovered \*\*[\d,]+ functions\*\*', 'The analysis recovered **2,317 functions**',s,count=1);s=re.sub(r'assigned \*\*\d+ evidence-based semantic labels\*\*',f'assigned **{count} evidence-based semantic labels**',s,count=1);s=s.replace('**447 functions have curated semantic labels; 1,773 do not.**',f'**{count} functions have curated semantic labels; {2317-count:,} do not.**');s+='\n\n## 15. Motion/runtime reconstruction and completed desktop analysis\n\nThe completed desktop run added 97 function entry points, all now incorporated after one reviewed shared-tail split. The current combined program has **2,317 recovered functions and 477 curated labels**. See **Deep-Analysis-Review.md** for integrity/boundary checks and **Motion-Planner-and-Runtime-Findings.md** for typed 128-byte motion blocks, restored flag-return dataflow, existing extrusion advance, acceleration/ring checks and their limits. Earlier section counts and descriptions refer to earlier passes. The four previous bad-instruction warnings are resolved by modeled exception call-return flow; the F32 comparison leaf C limitation remains explicitly documented.\n';p.write_text(s,encoding='utf-8')
p=out/'README.md';s=p.read_text(encoding='utf-8').replace('447 manually assigned',f'{count} manually assigned').replace('all 2,220 recovered functions','all 2,317 recovered functions').replace('newer IDEX, print-state and UI annotations','newer IDEX, print-state, UI, motion/runtime annotations and desktop-analysis additions');s=s.replace('| package-manifest.json |','| Motion-Planner-and-Runtime-Findings.md | Planner fields, acceleration, advance compensation and numeric-model limitations |\n| planner-block-layout.csv | Recovered 128-byte motion-block schema |\n| comparison-flags-verification.json and double-math-verification.json | Original numeric-helper checks |\n| math-exception-verification.json | 12 exceptional arithmetic/return cases |\n| trapezoid-verification.json and kinematics-queue-verification.json | Profile reference checks and all 256 ring states |\n| planner-init-verification.json and motion-block-verification.json | Initialization and isolated block-construction cases |\n| Deep-Analysis-Review.md and deep-analysis-review.json | Completed user-run comparison and integration evidence |\n| deep-analysis-function-merge.tsv | 97 imported entries, including reviewed shared-tail split |\n| planner-archive-verification.json | Reimported planner types, flag signatures and flow overrides |\n| package-manifest.json |');p.write_text(s,encoding='utf-8')
print('Motion findings and desktop-run review written')
