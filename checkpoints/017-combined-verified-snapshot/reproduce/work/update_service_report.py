import os
from pathlib import Path
import csv,json
out=Path(__file__).resolve().parent.parent/'outputs'
text='''# Service commands, print-time counters and command routing

This pass found a service counter-reset path and clarified command behavior. It did not reveal a new printing mode or enable any feature. All execution was offline; time, storage, filesystem and action interfaces were intercepted.

## Service counter reset

**0x0801402C**, now `GCode_M615_ResetPrintTimeCounters`, zeros two persistent print-time fields and their RAM copies:

| Field | Persistent offset | RAM | Width |
|---|---|---|---|
| Accumulated print hours | 0x69 | 0x200001EE | uint16 |
| Accumulated minute remainder | 0x6B | 0x200001F0 | uint8 |

Both load with default zero in **0x08013D3E**. Print-session timer arithmetic establishes hours and minutes: 3,600,000,000 microseconds per hour and 60,000,000 per minute. This is a print-time accounting path, not evidence of an activation, subscription or performance restriction.

Two callers reach the reset routine:

- The immediate dispatcher's **M615** route when the global control-channel byte at 0x20000241 is zero.
- Startup helper **0x08015826**, called once from `App_Main`, checks the filesystem mount-status byte at 0x20000259. When zero, it attempts a read-only open of the UTF-16 path `1:/j6&^%$#@-'s#&%%z@3#{}.txt`. A successful open triggers the reset. The path starts at **0x08015B64**. It does not inspect file contents in this function. The inspected helper does not delete the marker, so a marker left present could trigger another reset at the next eligible startup. This last statement follows from the code, not a repeated physical boot test.

The marker-file path is documented as reverse-engineering evidence. No marker file was created and no service command was sent. Resetting these fields would erase recorded usage; it does not add printer capability.

## Timing and boundaries

**0x0801407C** services an hour timer, increments the cumulative uint16 hours and the byte session-hour count, saves hours and restarts the timer. **0x080140BE** returns session hours/minutes for print-status display. **0x0801410A** adds the partial session minute remainder, carries once at 60, saves fields, stops the timer and clears the session-hour counter. That is not a general arbitrary-minute normalization routine; normal session remainder constraints matter.

**0x08016248** freezes elapsed time on pause and adjusts the start timestamp on resume. A tested 10-minute active period, 20-minute pause and 5-minute active period accumulated 15 minutes. An hour interval spanning unsigned timestamp wrap also passed. The cumulative hour field wraps from 65535 to zero in the tested increment path. This is observed 16-bit arithmetic, not a recommendation to alter the counter.

Fourteen checks cover loading, resetting, successful/missing/gated marker opens, one-hour boundaries, minute carry, uint16 hour rollover, pause/resume exclusion and timestamp wrap. External persistence calls were recorded in memory.

## Immediate command sweep

`immediate-route-verification.json` records **2,010 cases**: M0 through M1000 for control-channel byte values zero and one, plus four nonstandard/non-M inputs under each value. The tested print state was initialized and inactive. Parser conversion and all action/report handlers were intercepted; the original dispatcher and character search ran.

With control-channel byte one, recognized immediate M numbers are:

**23, 24, 25, 26, 27, 28, 29, 105, 112, 114, 115, 119, 502, 504, 600, 601, 602, 650, 651.**

The other 982 integers in that sweep return unhandled. With the byte zero, M601 and M615 call action handlers; all tested inputs return consumed, including unrecognized M numbers and G1. This describes the dispatcher result; the claim-control handler was stubbed, so the sweep does not demonstrate ownership transitions or end-to-end transport behavior. Control-channel state is not an authentication claim.

## G162 clarification

Six additional original-instruction checks examined **0x080116A4**, with its planner intercepted and no F field. A Z field's **presence** selects the configured unsigned Z extent at 0x2000016C; its numeric spelling is not parsed in this handler. Tested `Z-900` and `Z999` both selected the seeded extent 150. Without Z, absolute-mask state uses current Z and nonzero relative-mask state uses zero. Other target-array components retain their incoming staged values, and current coordinates are copied or added afterward according to that mask.

The tests deliberately seeded different current/staged arrays to expose data dependencies. They do not establish that arbitrary stale values arise in a normal job. Treat G162 as an internal workflow command until its caller/job preconditions are fully understood.

## Ghidra continuation

Navigate to `Service_ResetPrintTimeIfMarkerPresent`, `GCode_M615_ResetPrintTimeCounters`, `PrintTime_ServiceHourTimer` and `Timer_SetPaused`. Use cross-references from timer 0x20001064 and configuration fields 0x200001EE/F0 to follow print-start, pause and completion accounting. The updated archive has **447 curated labels among 2,220 recovered functions**; remaining library/UI/transport behavior and hardware timing are not fully characterized.
'''
(out/'Service-and-Command-Findings.md').write_text(text,encoding='utf-8')
p=out/'configuration-map.csv'
with p.open(newline='',encoding='utf-8-sig')as f:r=csv.DictReader(f);fields=r.fieldnames;rows=list(r)
for row in rows:
    if row['storage_offset_hex']=='0x69':row.update(observed_role='Accumulated print hours',evidence_limit='Original-instruction timer increment/reset tests; uint16 wraps at 65536')
    if row['storage_offset_hex']=='0x6B':row.update(observed_role='Accumulated print minute remainder',evidence_limit='Original-instruction minute-carry and reset tests; partial-session remainder assumptions apply')
with p.open('w',newline='',encoding='utf-8-sig')as f:w=csv.DictWriter(f,fields);w.writeheader();w.writerows(rows)
p=out/'command-map.csv'
with p.open(newline='',encoding='utf-8-sig')as f:r=csv.DictReader(f);fields=r.fieldnames;rows=list(r)
for row in rows:
    if row['route']=='immediate channel0'and row['command']=='M615':row.update(observed_behavior='Reset cumulative print-time hours/minutes in RAM and storage offsets 0x69/0x6B',status='original-instruction handler tests with persistent-write stubs; routing sweep')
    if row['command']=='G161/G162':row.update(observed_behavior='G161 consumed; G162 uses Z presence to select configured extent, otherwise current/zero Z by relative mask; other staged axes retained',status='original-instruction routing and six handler cases; planner intercepted, F omitted')
with p.open('w',newline='',encoding='utf-8')as f:w=csv.DictWriter(f,fields);w.writeheader();w.writerows(rows)
p=out/'Deconstruction-Report.md';s=p.read_text(encoding='utf-8').replace('431 evidence-based','447 evidence-based').replace('**431 functions have curated semantic labels; 1,789 do not.**','**447 functions have curated semantic labels; 1,773 do not.**');s+='\n\n## 14. Service paths and usage accounting\n\nThe service pass identifies M615 and the startup marker-file helper as print-time counter resets, resolves storage offsets 0x69/0x6B as cumulative hours/minute remainder, and verifies timer pause/wrap behavior. Fourteen usage/service cases, 2,010 immediate-routing cases and six G162 cases passed under the documented emulator stubs. See **Service-and-Command-Findings.md** for the exact path, addresses, routing lists and evidence limits. Sixteen additional functions bring curated labels to **447**; all **2,220** recovered functions remain exported. This does not constitute complete reverse engineering or an established feature unlock.\n';p.write_text(s,encoding='utf-8')
p=out/'README.md';s=p.read_text(encoding='utf-8').replace('431 manually assigned','447 manually assigned');s=s.replace('| package-manifest.json |','| Service-and-Command-Findings.md | Service marker, M615 counter reset, timing and routing evidence |\n| usage-service-verification.json | 14 offline usage, timer and service-file checks |\n| immediate-route-verification.json | 2,010 original-dispatch routing cases with action stubs |\n| g162-verification.json | Six internal G162 handler checks with planner stub |\n| package-manifest.json |');p.write_text(s,encoding='utf-8')
print('Service and command findings written')
