import os
from pathlib import Path
import csv,json
root=Path(__file__).resolve().parent.parent;out=root/'outputs'
p=out/'Deconstruction-Report.md';s=p.read_text(encoding='utf-8')
s=s.replace('340 evidence-based semantic labels','348 evidence-based semantic labels').replace('1,880 of the 2,220','1,872 of the 2,220').replace('**340 functions have curated semantic labels; 1,880 do not.**','**348 functions have curated semantic labels; 1,872 do not.**').replace('remaining 1,880 functions','remaining 1,872 functions')
s=s.replace('372 nonautomatic names','380 nonautomatic names').replace('and 340 curated labels','and 348 curated labels')
section='''## 10. Profile and IDEX selector follow-up

See **IDEX-and-Profile-Findings.md** and **idex-selector-verification.json** for the detailed trace and test limits.

- The 0x11/0x12 profile selector is shown in the UI as **Silver/Black**, respectively. Both initialized motion-table rows match; no performance unlock was found.
- M611 S1 selects persistent single-extruder configuration; S2 selects dual. This affects home offsets, UI/reporting and second-heater startup behavior, so it is not an advanced-mode unlock.
- M118 processes first/last T and a requested D mode as job-header metadata; D1/D2 arm a larger IDEX compensation/setup workflow. Omitting D can retain the previous requested mode.
- M111 T1 enables both carriages with opposite logical X counter changes; M111 T2 enables both with matching changes in the tested original-instruction step path. These correspond to mirror and duplicate behavior. No hardware outputs were driven.
- The coordinate parser has separate +/-66 compensation transforms, and the queue service uses calibration-pad markers and stored internal command sequences. Requested mode, compensation-pass mode and active synchronized mode are distinct RAM fields.
- These are existing Creator Pro 2 capabilities documented by FlashForge. The installed FlashPrint 5 also contains ditto-print settings. A full slicer-generated job is the practical route; raw command fragments here are analysis references, not complete initialization instructions.

No printer setting, firmware byte or connected device was changed. Eight additional functions received curated labels, bringing the total to 348; the recovered-function count remains 2,220.

'''
if '## 10. Profile and IDEX'not in s:s=s.replace('## Primary documentation used for hardware interpretation',section+'## Primary documentation used for hardware interpretation')
p.write_text(s,encoding='utf-8')
p=out/'README.md';s=p.read_text(encoding='utf-8').replace('340 manually assigned','348 manually assigned')
s=s.replace('| configuration-map.csv | Partial 15-offset storage schema with evidence limits |','''| configuration-map.csv | Partial 15-offset storage schema with evidence limits |
| IDEX-and-Profile-Findings.md | Tested selector behavior and practical interpretation |
| idex-selector-verification.json | Offline profile, header, coordinate and carriage-step cases |''')
s=s.replace('Your earlier `creator pro backup.bin` analysis entry is retained separately.','Your earlier `creator pro backup.bin` analysis entry is retained separately. The GZF in this package includes the newer IDEX/profile annotations; GUI copies imported earlier may not contain those latest labels.')
p.write_text(s,encoding='utf-8')
def update_csv(name,updates,key):
    p=out/name;rows=list(csv.DictReader(p.open(encoding='utf-8')))
    for r in rows:
        if r[key]in updates:r.update(updates[r[key]])
    with p.open('w',newline='',encoding='utf-8')as f:
        w=csv.DictWriter(f,fieldnames=rows[0].keys());w.writeheader();w.writerows(rows)
update_csv('configuration-map.csv',{'0x0E':dict(observed_role='Extruder-count selector: 1 single / 2 dual',evidence_limit='Changes home offsets and startup/UI/report behavior; not an IDEX unlock'),'0x26':dict(observed_role='Case variant: 0x11 Silver / 0x12 Black',evidence_limit='Selected initial motion tables identical in this dump; profile byte still changes')},'storage_offset_hex')
update_csv('command-map.csv',{'M111':dict(observed_behavior='T1 both carriages mirror X count changes; T2 duplicate; requires complete job initialization',status='instruction-emulated with numeric/GPIO stubs'),'M118':dict(observed_behavior='Job extents and first/last T metadata; D1/D2 arm IDEX setup; omitted D retains mode',status='instruction-emulated with numeric-conversion stub'),'M611':dict(observed_behavior='S1 persistent single-extruder selector; S2 dual, updates home offsets',status='confirmed handler and intercepted-storage emulation')},'command')
print('Updated profile and IDEX report references')
