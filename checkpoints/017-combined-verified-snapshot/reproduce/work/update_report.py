import os
from pathlib import Path
import csv,json
root=Path(__file__).resolve().parent.parent;out=root/'outputs'
p=out/'Deconstruction-Report.md';s=p.read_text(encoding='utf-8')
s=s.replace('148 evidence-based semantic labels','340 evidence-based semantic labels')
s=s.replace('Roughly two thousand functions still carry automatic names.','1,880 of the 2,220 recovered functions do not yet have a curated semantic label. Some additional startup/vector names exist but are not counted as manually characterized.')
s=s.replace('The heater structure is stored in Ghidra, but not all auto-inferred function parameters use that structure type.','The principal heater and PID parameters now have explicit recovered pointer types. Compiler helper calling conventions still cause artifacts such as `extraout_r3`; the raw instructions take precedence.')
s=s.replace('Application wrappers are provisionally labeled at 0x0803429C, 0x08034400, 0x080345DA and 0x080348B2.','Semantic comparison with the original Elm-Chan FatFs R0.09b source identified the application filesystem APIs and internal helper algorithms; exact release/build attribution remains unproven. The open/read/write/close APIs are now named at 0x0803429C, 0x08034400, 0x080345DA and 0x080348B2.')
s=s.replace('Exact drive-to-physical-medium mapping should be confirmed in the disk-I/O dispatch code rather than inferred from path numbers alone.','Disk dispatch at 0x08032944/0x080329BA/0x08032AB6 confirms drive 0 uses serial flash and drive 1 uses the SD path. Drive 0 initialization checks JEDEC ID 0xEF4018. This is an observed ID expectation, not a read of the actual installed part.')
s=s.replace('resolve sensor-table search behavior above the first 20 extruder entries.','audit all bypass/recovery callers. The table boundary above entry 19 has now been confirmed by instruction emulation (see pass 2 below).')
section='''## 9. Deeper validation and reconstruction — pass 2

### What the counts mean

There is no defensible “100% deconstructed” percentage from automatic disassembly. All 1,048,576 supplied flash bytes are preserved, and all 2,220 currently recovered functions are exported, but undiscovered functions, shared tails, indirect calls and resource interpretation remain possible. **340 functions have curated semantic labels; 1,880 do not.** Label counts measure navigation and characterized roles, not branch-level proof. `coverage-inventory.json` gives regional counts, and `remaining-functions.csv` lists outstanding functions by recovered body size. The 62 recovered functions in the selected filesystem region all have semantic labels; this does not prove every branch of that region.

### Original-instruction checks

The numeric and thermal verification files record offline Unicorn execution of the original ARM instructions. No code was sent to a printer. Numeric tests use mapped flash and reconstructed startup RAM. Thermal tests substitute deterministic sensor values, time/expiry, readiness and output-driver interfaces; they test the control routine, not actual ADC/SPI timing, electrical output or hardware safety.

- Five finite arithmetic cases establish add/divide/multiply/subtract/reverse-subtract wrapper roles.
- Two simple PID examples and a deterministic **128-sample** sequence agree with a separately reconstructed float32 algorithm. This covers positive/negative errors, integral clamping to ±256, ring history wrap and truncation before doubling. It does not establish NaN, infinity, overflow or every possible input.
- With gains 1, 0.5, 0.25, target 100 and initial state zero: measured 90 gives **34**, then measured 92 gives **38**. The weighted sum is converted to integer before multiplication by two. `Recovered-PID-Reference.c` is a readable finite-input model, not replacement firmware.
- Target 999 clamps to **120 for heater ID 2** and **240 for ID 4**; a negative target clamps to zero. Fault-disabled/control-bypass fields inhibit a nonzero target.
- Five isolated fault conditions trip on the **51st tested update call**: sensor status 3 → code 2; sensor status 4 → code 0x20; temperature 261 → code 4; insufficient rise with the timer expired → code 8; sustained deficit with timeout and readiness true → code 0x10. Each tested path sets disabled=1, clears the target, calls output(heater,0), and records code | (heater_id << 8).
- Busy statuses 1/2 do not increment the sensor-fault counter across 60 tested updates. A cold target produces 255 requested output; zero target produces zero. Counters can interact when multiple checks fail simultaneously, so 51 calls is not a universal wall-clock shutdown latency.

### Confirmed table boundary

`Sensor_TableInterpolate` at 0x080175B8 uses search bounds 0..19. Although the contiguous extruder table contains 29 pairs, this routine does not search its final nine entries. Original-instruction execution for table 1 returns 240 at raw 1247 and the caller-supplied cap 400 at raw 1248 and 2152. This is real behavior of the tested interpolation call, not just decompiler output. The SPI pipeline adds cold-junction compensation later, so these standalone results are not a complete physical-temperature calibration. Bed examples: raw 1721 → 126; raw 4086 → signed -29 (stored as 0xFFFFFFE3 in r0).

### Sensor identity inference

The SPI command words 0x0C62, 0x3C62 and 0x0072, paired differential channels and signed internal-temperature conversion at 0.03125 °C/LSB strongly match **TI ADS1118**. Config decoding yields differential AIN0–AIN1 / AIN2–AIN3, ±256 mV range and 64 SPS; 0x0072 selects its temperature sensor. This is a high-confidence inference from firmware behavior and the [TI ADS1118 datasheet](https://www.ti.com/lit/ds/symlink/ads1118.pdf), not physical chip-marking verification. The exact thermocouple type and board routing remain unverified.

### Libraries and compiler conventions

The filesystem algorithms, constants, object offsets and ordering were compared with the [original Elm-Chan FatFs R0.09b source archive](https://elm-chan.org/fsw/ff/arc/ff9b.zip). Named routines include FAT12/16/32 cluster operations, long filenames, path traversal, mount/open/read/write/sync/seek, directory enumeration, free-space, delete/mkdir/rename/format and UTF conversion. These are semantic matches, not a binary-identical source rebuild. STM32 peripheral helpers were named from register operations; confidence is lower for larger routines whose full original source has not been matched.

Float32 wrappers now have explicit r0/r1 storage and float types. Comparisons return **processor flags**, which ordinary C signatures do not express. An inline comparison experiment destabilized decompilation and was reverted; the final export contains no failed decompilations, but retains the four known bad-instruction warnings. `Runtime_F64_ExceptionDispatch` at 0x0804B1F8 reads a descriptor at aligned LR and restores the caller's stack; the embedded word around 0x0804AB3C is not evidence of corrupted flash. Its unusual return/dispatch convention still needs a custom analysis model. Ghidra “Unknown calling convention” annotations on explicitly assigned register storage are analysis limitations, not firmware faults.

### Display resources and indirect callbacks

`ui-language-catalog.csv` contains **1,803 readable UTF-8 runs** from ten fixed-size 0x2012-byte resource blocks: Simplified Chinese, English, Traditional Chinese, Japanese, German, Korean, French, Polish, Spanish and Portuguese. The block index is a resource index; selected-language behavior depends on external font availability and includes fallbacks. Candidate runs are decoded text, not proof of 1,803 distinct UI fields; duplicate/short strings remain.

`ui-page-callbacks.csv` recovers **19 assignments** to the periodic page callback at 0x20000374 and nearby dialog table/event callback registrations where statically visible. Thumb bits are cleared in callback addresses. This supplements the direct call graph; it is not a full dynamic page-transition graph. Page names and every widget event still need interpretation.

### What prevents full recovery

The original variable names, comments, source organization and build environment are stripped. External serial-flash assets, EEPROM calibration, backup SRAM, MCU UID/option bytes and live execution state are outside this dump. More static work can characterize the remaining 1,880 functions, especially UI/library internals and IDEX transforms, but it cannot supply absent captured data or establish real hardware timing. A source-equivalent, rebuildable firmware or complete behavioral proof has **not** been achieved.

The updated GZF was reimported into an independent project: **2,220 functions, 372 nonautomatic names**, and the same 1 MiB flash SHA-256. The distinction between 372 nonautomatic names and 340 curated labels is intentional: startup/vector names are also present. Use the curated-label table for the conservative count.

'''
if '## 9. Deeper validation'not in s:s=s.replace('## Primary documentation used for hardware interpretation',section+'## Primary documentation used for hardware interpretation')
p.write_text(s,encoding='utf-8')
p=out/'README.md';s=p.read_text().replace('148 manually assigned','340 manually assigned')
s=s.replace('as **CreatorPro2-Analyzed**.','as **CreatorPro2-Analyzed** (first pass); the deeper pass is imported separately as **CreatorPro2-DeepAnalysis**.')
s=s.replace('| analysis-summary.json | Summary counts |','''| analysis-summary.json | Summary counts |
| numeric-emulation-verification.json | Arithmetic, table boundaries and 128-sample PID comparison |
| thermal-emulation-verification.json | Offline heater limits and fault-path checks, with environment stubs |
| Recovered-PID-Reference.c | Readable finite-input controller model; not replacement firmware |
| coverage-inventory.json | Regional inventory without an invented completion percentage |
| remaining-functions.csv | Outstanding functions ordered by recovered body size |
| ui-language-catalog.csv | 1,803 UTF-8 runs from ten localized resource blocks |
| ui-page-callbacks.csv | 19 periodic page-callback assignments and dialog registrations |''')
p.write_text(s,encoding='utf-8')
cmd=list(csv.DictReader((out/'command-map.csv').open(encoding='utf-8-sig')))
updates={'M0/M1':'Optional P seconds; wait state 6 and prompt flag','M6':'Wait state 4; P timeout in seconds, default 900','M7':'Wait state 5; P timeout in seconds, default 1800','M132':'Zeros extrusion coordinates and resynchronizes motion positions','M147':'Parse F/L and enqueue frequency/duration pair','M148':'Select stored sound pattern or repeated two-tone pattern','M610':'Persist machine name at configuration base+0x40 (34 bytes)','M611':'Persist selector 1/2 at configuration base+0x0E and update dimensions','M906':'Parse R/L motor-current values; calls channel 0/5 driver, exact hardware unverified'}
for r in cmd:
    if r['command'] in updates:r['observed_behavior']=updates[r['command']];r['status']='confirmed handler behavior; hardware meaning where noted remains inferred'
with (out/'command-map.csv').open('w',newline='',encoding='utf-8')as f:
    w=csv.DictWriter(f,fieldnames=cmd[0].keys());w.writeheader();w.writerows(cmd)
print('Updated report and companion indexes')
