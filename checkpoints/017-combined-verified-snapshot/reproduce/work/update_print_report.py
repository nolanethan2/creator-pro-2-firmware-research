import os
from pathlib import Path
p=Path(__file__).resolve().parent.parent/'outputs/Deconstruction-Report.md'
s=p.read_text(encoding='utf-8').replace('five bounded TBB switches','six bounded TBB switches').replace('Five bounded TBB switches','Six bounded TBB switches')
section='''## 11. Pause/resume control-flow repair

The bounded seven-entry branch at 0x080121B2 now has explicit targets in Ghidra. This exposes resume states 0x81 through 0x87, including the intentionally unhandled state 0x82. Offline checks passed 13 transitions and seven wait conditions using original state-dispatch instructions and simulated subsystem responses. See **Print-Pause-Resume-Findings.md** and **print-state-verification.json** for the sequence and test limits. This is control-flow recovery, not a hardware motion/heating validation.

'''
if '## 11. Pause/resume'not in s:s=s.replace('## Primary documentation used for hardware interpretation',section+'## Primary documentation used for hardware interpretation')
p.write_text(s,encoding='utf-8')
