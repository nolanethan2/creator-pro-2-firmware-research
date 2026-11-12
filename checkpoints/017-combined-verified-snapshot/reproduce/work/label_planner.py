import os
from pathlib import Path
import csv
out=Path(__file__).resolve().parent.parent/'outputs';p=out/'function-labels.tsv'
with p.open(encoding='utf-8',newline='')as f:r=csv.DictReader(f,delimiter='\t');fields=r.fieldnames;labels={row['address']:row for row in r}
new={
'0804a9f4':('Math_F64_Add','512 normal finite bit-exact arithmetic cases; exceptional classification tests; original soft-double addition'),
'0804ab6c':('Math_F64_Divide','512 normal finite bit-exact arithmetic cases and zero-denominator classification tests'),
'0804b0a4':('Math_F64_Multiply','512 normal finite bit-exact arithmetic cases and zero-times-infinity exception test'),
'0804b3c0':('Math_F64_ReverseSubtract','512 normal finite cases return arg1 minus arg0, bit-exact'),
'0804b570':('Math_F64_Subtract','512 normal finite cases return arg0 minus arg1, bit-exact; infinity case tested'),
'0804b744':('Math_F32_ToF64','512 original-instruction conversion cases'),
'0804a990':('Math_F64_ToF32','512 original-instruction conversion cases, binary32 rounding checked'),
'0804ae94':('Math_F64_ToI32','Bit-level double exponent/mantissa conversion; exercised throughout trapezoid and arithmetic tests'),
'0804b832':('Math_U64_ToF32','Two-register unsigned input and binary32 result; exercised by triangular advance profile computation'),
'08049fcc':('Math_F64_SqrtWithStatus','512 finite nonnegative bit-exact square-root cases; wrapper additionally records status on exceptional output'),
'0804b3d8':('Math_F64_SqrtCore','512 normal finite bit-exact square-root cases; negative/infinite input classifications tested'),
'0804b30c':('Math_F64_RoundNearestEven','553 finite cases including signed half-integer ties and negative zero; NaN/infinity classification tested'),
'0804ae1c':('Math_F64_CompareFlags_0804ae1c','1064 finite pairs: CY arg0>=arg1 and ZR equality; exact integer-CMP NZCV patterns vary by sign'),
'0804b02c':('Math_F64_CompareFlags_0804b02c','1064 finite pairs: CY arg0>=arg1 and ZR equality; explicit four-flag return signature'),
'0804b2a0':('Math_F64_CompareReverseFlags','1064 finite pairs: CY arg1>=arg0 and ZR equality; explicit four-flag return signature'),
'08029d88':('Planner_CalculateTrapezoid','134 independent kinematic profile comparisons plus seven busy/nonaccelerated/advance cases; only interrupt wrapper stubbed'),
'0802a066':('Planner_ReversePassBlock','Reviews current/next entry-speed limits, nominal-length and lookahead-ready flags; reverse traversal caller'),
'0802a132':('Planner_ForwardPassBlock','Limits current block entry speed from previous block acceleration/distance; compares tolerances and marks recalculation'),
'0802a0ec':('Planner_ReversePass','Walks from ring head backward to sampled tail, calling reverse block pass'),
'0802a274':('Planner_ForwardPass','Walks from tail to head, calling forward block pass'),
'0802a2a8':('Planner_RecalculateTrapezoids','Computes adjacent entry/exit speed factors and recalculates profiles, including final block'),
'0802a32c':('Planner_RecalculateLookahead','Runs reverse pass, forward pass and trapezoid rebuilding in sequence'),
'0802a33c':('Planner_ResetQueueAndAdvance','Clears head/tail, prior speed and positions; stores two advance factors and Z/endstop-related flag'),
'0802a37c':('Planner_BuildMotionBlock','128-byte block constructor; axis steps/directions, rate limiting, extrusion advance, trapezoid, ring publication and lookahead; ten isolated block cases'),
'0802b06a':('Planner_NextRingIndex','Adds one and wraps index16 to zero; original-instruction block/ring cases'),
'0802b064':('Motion_SetInterruptCriticalSection','Privilege test and IRQ control wrapper around shared planner updates'),
'08049d00':('Planner_GetQueuedBlockCount','Returns (head-tail)&15; all 256 valid head/tail pairs tested'),
'08049a24':('Motion_StepsFromSquaredRateDifference','Returns (arg1-arg0)/arg2 with zero denominator fallback; trapezoid distance helper'),
'08049a34':('Motion_SpeedAfterAcceleration','sqrt(max(0,v*v+2*a*d)) with operation-specific float/double rounding; 512 bit-exact cases'),
'08049b90':('Motion_MaxEntrySpeedForDeceleration','sqrt(max(0,v*v-2*a*d)) with operation-specific float/double rounding; 512 bit-exact cases')}
for a,(name,evidence)in new.items():labels[a]=dict(address=a,name=name,confidence='high',evidence=evidence)
for a in ['0804b7d8','0804b8a0','0804b982']:
    labels[a]['evidence']='1064 original-instruction finite comparisons each; explicit flag-return signature. WARNING: Ghidra leaf C drops NG/ZR/CY expressions; use VCMP/VMRS disassembly and tested flag truth table, not that leaf C body.'
with p.open('w',encoding='utf-8',newline='')as f:w=csv.DictWriter(f,fields,delimiter='\t');w.writeheader();w.writerows(labels[a]for a in sorted(labels))
print(f'{len(labels)} curated function labels')
