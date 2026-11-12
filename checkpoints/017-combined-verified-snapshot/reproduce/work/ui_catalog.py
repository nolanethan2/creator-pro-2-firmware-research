import os
from pathlib import Path
import json,re,csv,struct
root=Path(__file__).resolve().parent.parent;out=root/'outputs'
b=Path(os.environ.get('CREATORPRO2_DUMP',str(root/'input/creator-pro-backup.bin'))).read_bytes()
funcs=json.loads((out/'function-map.json').read_text(encoding='utf-8'));by={f['address']:f for f in funcs}
def textat(a):
    if not 0x8000000<=a<0x8100000:return ''
    raw=b[a-0x8000000:a-0x8000000+512].split(b'\0')[0]
    try:return raw.decode('utf-8')
    except UnicodeDecodeError:return ''
rows=[];screens=[];widgets=[]
for f in funcs:
    resources=[]
    for m in re.finditer(r'DAT_[0-9a-f]+ /\* pool value 0x20000384 \*/\s*\+\s*(0x[0-9a-f]+|\d+)',f['code']):
        off=int(m[1],0);t=textat(0x809a31a+off)
        if t:resources.append(dict(offset=hex(off),text=t))
    f['ui_resources']=list({r['offset']:r for r in resources}.values())
    if resources:rows.append([f['address'],f['name'],' | '.join(r['text']for r in f['ui_resources'])])
    simple=re.sub(r'DAT_[0-9a-f]+ /\* pool value 0x([0-9A-F]+) \*/',lambda m:'0x'+m[1],f['code'])
    for m in re.finditer(r'FUN_0803c27c\s*\(\s*(0x[0-9A-Fa-f]+)\s*,\s*(0x[0-9a-f]+|\d+)\s*,\s*(0x[0-9A-Fa-f]+)',simple):
        table,count,cb=int(m[1],16),int(m[2],0),int(m[3],16)&~1
        if not(1<=count<=100 and 0x8000000<=table<=0x8100000-count*28):continue
        screens.append(dict(creator=f['address'],table=hex(table),count=count,callback=f'{cb:08x}'))
        for i in range(count):
            a=table+i*28;create,name=struct.unpack_from('<II',b,a-0x8000000);id,x,y,w,h,flags=struct.unpack_from('<HhhhhH',b,a-0x8000000+8);para,size=struct.unpack_from('<II',b,a-0x8000000+20)
            widgets.append(dict(table=hex(table),index=i,address=hex(a),create_function=f'{create&~1:08x}',name=textat(name),id=hex(id),x=x,y=y,width=w,height=h,flags=hex(flags),parameter=para,extra_bytes=size))
(out/'ui-screen-catalog.json').write_text(json.dumps(dict(screens=screens,widgets=widgets,function_resources=[dict(address=a,name=n,text=t)for a,n,t in rows]),indent=2,ensure_ascii=False),encoding='utf-8')
with (out/'ui-resource-references.csv').open('w',newline='',encoding='utf-8-sig')as f:
    w=csv.writer(f);w.writerow(['function','name','english_resource_text']);w.writerows(rows)
with (out/'ui-widgets.csv').open('w',newline='',encoding='utf-8-sig')as f:
    w=csv.DictWriter(f,fieldnames=list(widgets[0]));w.writeheader();w.writerows(widgets)
print(json.dumps(dict(screens=len(screens),widgets=len(widgets),functions_with_resources=len(rows))))
print(json.dumps([dict(address=a,text=t[:400])for a,n,t in rows if '0801bc00'<=a<'08028800'],indent=2))
