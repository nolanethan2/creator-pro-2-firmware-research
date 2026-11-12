# Service commands, print-time counters and command routing

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
