import os
from pathlib import Path
import re,csv,json
root=Path(__file__).resolve().parent.parent;out=root/'outputs'
b=Path(os.environ.get('CREATORPRO2_DUMP',str(root/'input/creator-pro-backup.bin'))).read_bytes()
langs=['Simplified Chinese','English','Traditional Chinese','Japanese','German','Korean','French','Polish','Spanish','Portuguese']
rows=[]
for i,lang in enumerate(langs):
    base=0x98308+i*0x2012;block=b[base:base+0x2012]
    for m in re.finditer(rb'[^\x00]+',block):
        try:s=m[0].decode('utf-8')
        except UnicodeDecodeError:continue
        if not s or any(not(c.isprintable() or c in '\r\n\t') for c in s):continue
        rows.append([i,lang,f'0x{base+0x08000000:08X}',f'0x{m.start():04X}',f'0x{base+m.start()+0x08000000:08X}',s])
with (out/'ui-language-catalog.csv').open('w',encoding='utf-8-sig',newline='')as f:
    w=csv.writer(f);w.writerow(['resource_block','language_inferred_from_text','block_address','offset','address','utf8_text']);w.writerows(rows)
funs=json.loads((out/'function-map.json').read_text());labels=[f for f in funs if f['confidence']!='unreviewed']
groups=[('Bootloader',0x08000000,0x08010000),('Application startup, commands and configuration',0x08010000,0x08016000),('Application interrupts, heaters and drivers',0x08016000,0x0801bc00),('UI and print workflow',0x0801bc00,0x08028800),('Transport and motion',0x08028800,0x0802c500),('MCU/USB peripheral support',0x0802c500,0x08032944),('Filesystem',0x08032944,0x08035d3c),('GUI, display and other support',0x08035d3c,0x08049500),('Runtime and numeric support',0x08049500,0x0804c000)]
inventory=[]
for name,lo,hi in groups:
    fs=[f for f in funs if lo<=int(f['address'],16)<hi]
    inventory.append(dict(region=name,start=hex(lo),end_exclusive=hex(hi),recovered_functions=len(fs),curated_labels=sum(f['confidence']!='unreviewed' for f in fs)))
inv=dict(scope='Inventory, not a percentage of complete reverse engineering. Function discovery and indirect-call recovery are incomplete.',source_flash_bytes=len(b),exported_recovered_functions=len(funs),curated_function_labels=len(labels),unreviewed_function_labels=len(funs)-len(labels),utf8_language_resource_strings=len(rows),language_blocks=10,regions=inventory)
(out/'coverage-inventory.json').write_text(json.dumps(inv,indent=2))
pending=sorted([f for f in funs if f['confidence']=='unreviewed'],key=lambda f:f['size'],reverse=True)
with (out/'remaining-functions.csv').open('w',newline='',encoding='utf-8')as f:
    w=csv.writer(f);w.writerow(['address','automatic_name','ghidra_body_bytes_not_unique_coverage','direct_callers','direct_callees']);w.writerows([x['address'],x['name'],x['size'],len(x['callers']),len(x['calls'])]for x in pending)
print(json.dumps(inv,indent=2))
by={f['address']:f for f in funs}
pages=[]
for f in funs:
    m=re.search(r'\*DAT_[0-9a-f]+ /\* pool value 0x20000374 \*/ = (?:0x([0-9a-f]+)|DAT_[0-9a-f]+ /\* pool value 0x([0-9A-F]+) \*/);',f['code'])
    if not m:continue
    callback=f'{int(m[1] or m[2],16)&~1:08x}'
    regs=re.findall(r'(?:FUN_0803c27c|GUI_CreateDialogBox_Recovered)\(DAT_[0-9a-f]+ /\* pool value 0x([0-9A-F]+) \*/,([^,]+),DAT_[0-9a-f]+ /\* pool value 0x([0-9A-F]+) \*/',f['code'])
    pages.append([f['address'],f['name'],callback,by.get(callback,{}).get('name','not recovered'),';'.join(x[0] for x in regs),';'.join(x[1].strip()for x in regs),';'.join(f'{int(x[2],16)&~1:08x}'for x in regs)])
with (out/'ui-page-callbacks.csv').open('w',newline='',encoding='utf-8')as f:
    w=csv.writer(f);w.writerow(['setter_function','setter_name','periodic_callback_thumb_bit_cleared','callback_name','widget_table_address','widget_count_literal','dialog_callback_thumb_bit_cleared']);w.writerows(pages)
print('Recovered UI callback assignments:',len(pages))
