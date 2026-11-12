import os
from pathlib import Path
import csv
out=Path(__file__).resolve().parent.parent/'outputs';p=out/'function-labels.tsv'
with p.open(encoding='utf-8',newline='')as f:r=csv.DictReader(f,delimiter='\t');fields=r.fieldnames;labels={row['address']:row for row in r}
new={
'08013d3e':('Config_LoadPrintTimeCounters','Loads uint16 hours at storage +0x69 and byte minutes at +0x6B; original-instruction startup read test'),
'08013ffc':('Config_SavePrintHours','Writes uint16 storage +0x69 then delay; observed in emulated hour increment/finalization'),
'08014014':('Config_SavePrintMinutes','Writes byte storage +0x6B then delay; observed in emulated finalization'),
'0801402c':('GCode_M615_ResetPrintTimeCounters','Resets stored/RAM hours and minutes; immediate channel-zero M615 and startup marker-file callers; original-instruction tests'),
'0801407c':('PrintTime_ServiceHourTimer','3600000000-us expiration increments cumulative and session hour counters; tested boundary, uint16 rollover and clock wrap'),
'080140be':('PrintTime_GetSessionHoursMinutes','Returns session hours and elapsed microseconds divided by 60000000; timer inactive/recovery branches require context'),
'0801410a':('PrintTime_AccumulateAndStopSession','Accumulates session minute remainder, carries at 60, persists counters, clears timer/session-hour accumulator; original-instruction checks'),
'08014712':('PrintTime_StartSessionTimer','Starts one-hour timer or shorter recovered-session remainder; clears/restores byte session-hour counter'),
'08015826':('Service_ResetPrintTimeIfMarkerPresent','When storage mount-status byte is zero, opens exact UTF16 service-marker path read-only; successful open calls counter reset; tested missing/present/gated'),
'08016248':('Timer_SetPaused','Captures elapsed time on pause and adjusts timestamp on resume; original-instruction pause-exclusion test'),
'08016270':('Timer_IsActive','Returns first timer byte'),
'08016276':('Timer_GetElapsedMicroseconds','Inactive returns zero; paused returns saved elapsed; active uses unsigned timestamp delta; tested paused and resumed'),
'08029b72':('Planner_IsQueueEmpty','Compares planner queue head 0x200005B1 and tail 0x200005B2'),
'080106b6':('Command_ReplyConsumedIfRequired','Conditionally formats/sends common consumed-command response based on source and processing-state flags'),
'080116a4':('GCode_G162_PlanConfiguredZMove','Z field presence selects configured unsigned Z extent; absence uses current Z or zero by relative mask; retains other staged axes; six original-instruction checks without F'),
'08011756':('GCode_M25_RequestPause','Sets UI pause request byte, displays localized pause message, performs UI update and pause-state request')}
for a,(name,evidence)in new.items():labels[a]=dict(address=a,name=name,confidence='high',evidence=evidence)
with p.open('w',encoding='utf-8',newline='')as f:w=csv.DictWriter(f,fields,delimiter='\t');w.writeheader();w.writerows(labels[a]for a in sorted(labels))
print(f'{len(labels)} curated function labels')
