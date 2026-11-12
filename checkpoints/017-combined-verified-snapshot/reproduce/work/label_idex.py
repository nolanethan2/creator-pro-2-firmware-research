import os
from pathlib import Path
import csv
root=Path(__file__).resolve().parent.parent;path=root/'outputs/function-labels.tsv'
rows={r['address']:r for r in csv.DictReader(path.open(),delimiter='\t')}
items=[
('0801068c','Command_FindLastField','Searches last matching field character with strrchr; M118 uses first/last T to detect a two-tool job'),
('080380ea','Lib_StrRChr','Scans to NUL while retaining last matching character pointer'),
('080114b8','GCode_M111_SetSynchronizedCarriages','T sets 0x20000013 and enables both X carriages; offline original-instruction step test confirms T1 opposite counter deltas and T2 same deltas'),
('080135fc','Config_IsSingleExtruder','Returns MachineConfig[0x1C] != 2; branches select one/two temperature reports and startup disables second heater in single mode'),
('080138c0','Config_ApplyExtruderCountHomeOffsets','Chooses profile-table home offsets based on one/two-extruder predicate'),
('08013940','Config_SetExtruderCount','Input 1 stores one-extruder selector; all other tested inputs store 2 at EEPROM +0x0E; updates RAM count and home offsets'),
('08011198','GCode_M611_SetExtruderCount','S argument calls persistent count selector; this is not an advanced feature unlock'),
('08013ab4','Config_SelectCaseVariantProfile','0x11 Silver / 0x12 Black from UI option text and callback; selected initial motion tables identical in this firmware'),
('08013cd6','Config_ResetUserSettingsDefaults','Restores language, variant profile, temperature presets and machine-name defaults; selects profile by storage backend'),
('08025fe4','UI_CaseVariantDialog_Initialize','Adds Silver then Black options; profile 0x12 selects Black'),
('08026222','UI_CaseVariantDialog_Callback','Confirm maps option 1 to profile 0x12 Black and other option to 0x11 Silver'),
('08011266','GCode_M118_ConfigureJobIDEX','First/last T sets two-tool flag; D1/D2 arm IDEX setup, bounds and calibration flags. D omitted retains prior mode. Original-instruction tests with numeric conversion stub; not a standalone physical mode-switch recipe')]
for a,n,e in items:rows[a]=dict(address=a,name=n,confidence='high',evidence=e)
with path.open('w',encoding='utf-8',newline='')as f:
    w=csv.DictWriter(f,fieldnames=['address','name','confidence','evidence'],delimiter='\t');w.writeheader();w.writerows(rows[a]for a in sorted(rows))
print('Curated labels:',len(rows))
