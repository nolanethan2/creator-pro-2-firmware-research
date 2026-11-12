import os
from pathlib import Path
import json,csv,re
root=Path(__file__).resolve().parent.parent;out=root/'outputs'
funcs={f['address']:f for f in json.loads((out/'function-map.json').read_text())};catalog=json.loads((out/'ui-screen-catalog.json').read_text(encoding='utf-8'))
rows={r['address']:r for r in csv.DictReader((out/'function-labels.tsv').open(),delimiter='\t')}
roles={'0801c28a':'Home','0801c5b4':'About','0801d326':'FileBrowser','0801e4c6':'PrintStatus','0801ee8c':'Tools','080205b4':'Preheat','08020db2':'FilamentHeating','080213aa':'FilamentLoadUnload','08021666':'Homing','08021e48':'ManualJog','08022988':'Language','08022d72':'BedLeveling','080235dc':'TemperatureStatus','08023b78':'PreheatDuringPrint','08023f7e':'Settings','08024608':'SingleButtonMessage','08025646':'PrintAdjustments','0802636c':'PulleyType','080275b0':'CalibrationAdjustment','08028034':'CalibrationWizard','080282ea':'ContinueZCalibration','08028a7e':'ExpertCalibrationIntro'}
typed=set()
def label(a,n,e,c='high'):
    assert a in funcs,a
    rows[a]=dict(address=a,name=n,confidence=c,evidence=e)
for s in catalog['screens']:
    creator=s['creator'];role=roles.get(creator)
    if not role:continue
    cb=s['callback'];typed.add(cb)
    label(creator,'UI_'+role+'_Open','Static widget table '+s['table']+' and callback '+cb+'; role established from displayed strings, event routes and control-path review')
    label(cb,'UI_'+role+'_Callback','Message dispatch (init/paint/parent notification), widget IDs and routes match '+role+' screen')
    m=re.search(r'== 0x1d\) \{\s*FUN_([0-9a-f]+)\(',funcs[cb]['code'])
    if m:
        typed.add(m[1]);label(m[1],'UI_'+role+'_Initialize','Invoked for initialization message 0x1D; installs text/appearance for '+role+' screen')
for a,n,e in [
('08028432','UI_ExpertCalibration_Initialize','Manual fine calibration title and X-/X+/Y-/Y+ buttons'),
('08028688','UI_ExpertCalibration_Callback','Original-instruction callback tests confirm 0.05 X/Y staging, OK persistence at EEPROM 0/4 and Cancel clearing'),
('0802893c','UI_ExpertCalibrationIntro_Callback','Next creates expert calibration widget table 0x080AD8D8; back returns to Settings'),
('08028a14','UI_ExpertCalibrationIntro_Periodic','On pending flag, installs expert calibration explanation and Next text'),
('080244a4','UI_Settings_OpenExpertCalibration','Settings Expert Mode button route to intro screen; no secret enable bit'),
('08013c7a','Config_SaveXCalibrationOffset','Reads float at 0x20001028 and writes EEPROM offset 0 through byte-addressed float writer'),
('08013c96','Config_SaveYCalibrationOffset','Reads float at 0x2000102C and writes EEPROM offset 4'),
('0801c2cc','UI_Home_OpenPrintSource','Home print action opens storage/source screen'),
('0801c2e2','UI_Home_OpenPreheat','Home preheat action selects normal or in-print screen based on 0x20000444'),
('0801c304','UI_Home_OpenTools','Home tools action opens Tools screen'),
('0801bf76','UI_CloseStatusDialog','Closes status dialog handle 0x2000038C and clears it'),
('0801bdc4','UI_ShowHeaterFault','Maps heater fault code to localized sensor/temperature/rise/drop error messages'),
('0803c27c','GUI_CreateDialogBox_Recovered','Indirect widget constructor loop, 28-byte records, initialization message; consistent with emWin dialog API'),
('08042518','GUI_GetDialogItem_Recovered','Looks up child widget by parent handle and integer ID throughout callbacks'),
('080425ae','GUI_GetWidgetId_Recovered','Returns widget identifier used in notification dispatch'),
('0803a1f8','GUI_ButtonCreateIndirect_Recovered','28-byte widget descriptor extraction and text-setting path; button usage in recovered tables'),
('080417ea','GUI_TextCreateIndirect_Recovered','28-byte widget descriptor extraction; text widget usage in recovered tables'),
('0803ada6','GUI_FrameWindowCreateIndirect_Recovered','First record in all recovered dialog tables; extracts frame geometry and callback'),
('0803a392','GUI_ButtonSetText_Recovered','Text setter used with button IDs and localized labels'),
('08041930','GUI_TextSetText_Recovered','Text setter used for static text fields and formatted status strings')]:label(a,n,e,'medium'if a.startswith('0803')or a.startswith('0804')else'high')
typed.update(['08028432','08028688','08028326','0802893c'])
# Correct the earlier case-color interpretation: the surrounding screen says Pulley Type.
for a in ['08013ab4','08025fe4','08026222']:
    if a in rows:rows[a]['name']=rows[a]['name'].replace('CaseVariant','PulleyType');rows[a]['evidence']=rows[a]['evidence'].replace('case','pulley hardware')+'; enclosing UI title is Pulley Type, not case color'
with (out/'function-labels.tsv').open('w',encoding='utf-8',newline='')as f:
    w=csv.DictWriter(f,fieldnames=['address','name','confidence','evidence'],delimiter='\t');w.writeheader();w.writerows(rows[a]for a in sorted(rows))
(root/'work/ui-message-functions.txt').write_text('\n'.join(sorted(typed)))
print('Curated labels:',len(rows),'typed message functions:',len(typed))
