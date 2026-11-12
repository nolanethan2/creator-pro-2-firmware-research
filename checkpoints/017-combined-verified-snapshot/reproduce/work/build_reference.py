import os
from pathlib import Path
import re, json, csv, struct, hashlib, html
root=Path(__file__).resolve().parent.parent
out=root/'outputs'
b=Path(os.environ.get('CREATORPRO2_DUMP',str(root/'input/creator-pro-backup.bin'))).read_bytes()
ram=(root/'work/app-initialized-ram.bin').read_bytes()
def csvout(name,fields,rows):
    with (out/name).open('w',encoding='utf-8-sig',newline='') as f:
        w=csv.writer(f);w.writerow(fields);w.writerows(rows)
def pin(port,mask):
    if not port or not mask:return ''
    return 'P'+chr(65+(port-0x40020000)//0x400)+str(mask.bit_length()-1)
pins=[]
for i,axis in enumerate(['X primary','Y','Z','Extruder 0','Extruder 1']):
    v=struct.unpack_from('<10I',ram,0x5bc+i*40)
    pins.append([i,axis,pin(*v[:2]),pin(*v[2:4]),pin(*v[4:6]),pin(*v[6:8]),pin(*v[8:10])])
csvout('motor-pin-table.csv',['axis_index','axis_role_inferred','step','direction','enable_candidate','aux_input_pair_unresolved','endstop_input'],pins)
csvout('sensor-tables.csv',['table','flash_address','index','raw_signed16','temperature_signed16'],[[name,f'0x{0x08000000+off+i*4:08X}',i,*struct.unpack_from('<hh',b,off+i*4)]for name,off,n in [('bed',0x4c5b4,20),('extruder',0x4c604,29)]for i in range(n)])
labels={row['address']:row for row in csv.DictReader((out/'function-labels.tsv').open(encoding='utf-8'),delimiter='\t')}
raw=(out/'ghidra/decompiled.c').read_text(encoding='utf-8')
funcs={m[1]:dict(address=m[1],name=m[2],size=int(m[3]),code=m[4]) for m in re.finditer(r'/\* FUNCTION ([0-9a-f]+) ([^\r\n]+) SIZE (\d+) \*/\r?\n([\s\S]*?)(?=\r?\n/\* FUNCTION|$)',raw)}
for f in funcs.values():
    f.update(confidence=labels.get(f['address'],{}).get('confidence','unreviewed'),evidence=labels.get(f['address'],{}).get('evidence','Automatic Ghidra recovery; not manually characterized'),calls=[],callers=[],strings=[],registers=[])
strs=json.loads((out/'firmware-strings.json').read_text())
strmap={s['address'][2:]:s['text'] for s in strs}
refs=list(csv.DictReader((out/'ghidra/references.tsv').open(encoding='utf-8'),delimiter='\t'))
edges=set()
for r in refs:
    f=funcs.get(r['function'])
    if not f:continue
    if 'CALL' in r['type']:
        f['calls'].append(r['to'])
        if r['to'] in funcs:funcs[r['to']]['callers'].append(f['address']);edges.add((f['address'],r['to']))
    if r['to'] in strmap:f['strings'].append([r['to'],strmap[r['to']]])
    if not re.fullmatch('[0-9a-fA-F]+',r['to']):continue
    v=int(r['to'],16)
    if 0x40000000<=v<0x60000000 or 0xe000e000<=v<0xe0100000:f['registers'].append(r['to'])
def literal(m):
    off=int(m[1],16)-0x08000000
    return m[0]+(f' /* pool value 0x{struct.unpack_from("<I",b,off)[0]:08X} */' if 0<=off<=len(b)-4 else '')
for f in funcs.values():
    f['calls']=sorted(set(f['calls']));f['callers']=sorted(set(f['callers']));f['registers']=sorted(set(f['registers']))
    f['strings']=list({x[0]:x for x in f['strings']}.values())
    f['code']=re.sub(r'(?:PTR_)?DAT_([0-9a-f]{8})',literal,f['code'])
(out/'function-map.json').write_text(json.dumps(list(funcs.values()),indent=2),encoding='utf-8')
csvout('call-graph.csv',['caller','caller_name','callee','callee_name'],[[a,funcs[a]['name'],z,funcs[z]['name']] for a,z in sorted(edges)])
csvout('string-references.csv',['function','name','string_address','text'],[[a,f['name'],s,t]for a,f in funcs.items()for s,t in f['strings']])
csvout('hardware-references.csv',['function','name','address'],[[a,f['name'],r]for a,f in funcs.items()for r in f['registers']])
# Recover the bounded state tables directly. These are edges, not assertions of state semantics.
switches=[]
for adr,n,label in [(0x08011f40,13,'homing candidate'),(0x080121b2,7,'print resume states 0x81-0x87'),(0x08012b24,10,'command service'),(0x08017eca,5,'sensor status'),(0x08020c82,7,'UI heating state'),(0x08037784,10,'language selector')]:
    switches.extend([[label,f'0x{adr:08X}',i,f'0x{adr+4+b[adr+4-0x08000000+i]*2:08X}']for i in range(n)])
csvout('bounded-switch-targets.csv',['role','instruction','index','target'],switches)
index=list(csv.DictReader((out/'ghidra/functions.tsv').open(encoding='utf-8'),delimiter='\t'))
meta=dict(function_count=len(funcs),manually_labeled=sum(a in labels for a in funcs),call_edges=len(edges),string_references=sum(len(f['strings'])for f in funcs.values()),hardware_references=sum(len(f['registers'])for f in funcs.values()),decompiler_error_functions=[f['address']for f in index if f['decompile_ok']!='true'],sha256=hashlib.sha256(b).hexdigest())
meta['decompiler_bad_instruction_warnings']=[a for a,f in funcs.items()if 'Control flow encountered bad instruction' in f['code']]
meta['manually_overridden_switch_functions']=[a for a,f in funcs.items()if 'Switch is manually overridden' in f['code']]
(out/'analysis-summary.json').write_text(json.dumps(meta,indent=2))
page='''<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width"><title>Creator Pro 2 firmware reference</title><style>
body{margin:0;background:#10151e;color:#e3eaf2;font:15px system-ui}header{padding:22px 28px;background:#192332;border-bottom:1px solid #34465d}h1{margin:0 0 8px}input,select{background:#10151e;color:#fff;border:1px solid #789;padding:10px;margin:12px 8px 0 0;border-radius:5px}main{display:grid;grid-template-columns:350px 1fr;height:calc(100vh - 180px)}nav{overflow:auto;border-right:1px solid #34465d}nav a{display:block;padding:9px 15px;border-bottom:1px solid #233041;color:#a5d7ff;text-decoration:none}nav small{display:block;color:#b1bccd}article{overflow:auto;padding:20px 28px}pre{white-space:pre-wrap;font:13px/1.55 Consolas,monospace;color:#c6e3ce;background:#0a1018;padding:20px}a{color:#8ccfff}.pill{background:#263b51;padding:4px 8px;border-radius:5px}p{line-height:1.55}.muted{color:#b1bccd}.links a{margin-right:12px} @media(max-width:800px){main{grid-template-columns:1fr;height:auto}nav{max-height:250px}article{overflow:visible}}
</style><header><h1>Creator Pro 2 · Firmware reference</h1><div>Read-only static analysis · V1.8 20210221 · __COUNT__ recovered functions</div><div class="muted">Decompiler output is reconstructed pseudocode, not original or buildable source. Names marked candidate remain hypotheses.</div><input id="q" placeholder="Search name, address, code, strings…" size="40"><select id="filter"><option value="all">All functions</option><option value="reviewed">Labeled functions</option><option value="app">Application only</option><option value="boot">Bootloader region</option><option value="unreviewed">Unreviewed</option></select><span id="count"></span></header><main><nav id="list"></nav><article id="detail"><h2>Start with the main loop</h2><p>Select a function on the left. Search works across names, addresses, decompiled code and referenced strings.</p><p>Useful addresses: <a href="#0801033e">0801033e — main</a>, <a href="#0801177a">0801177a — G-code dispatch</a>, <a href="#080295fc">080295fc — motion ISR</a>, <a href="#08017e7c">08017e7c — heater control</a>.</p><p>The combined program reconstructs application RAM. Use the separate bootloader Ghidra archive for boot-specific RAM state.</p></article></main><script>
const data=__DATA__;const by=new Map(data.map(f=>[f.address,f]));const el=s=>document.getElementById(s);const esc=s=>String(s).replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
function links(xs){return xs.map(a=>'<a href="#'+a+'">'+esc(by.has(a)?by.get(a).name:a)+'</a>').join(' · ')||'None recovered';}
function render(){const q=el('q').value.toLowerCase(),mode=el('filter').value;const xs=data.filter(f=>(mode==='all'||mode==='reviewed'&&f.confidence!=='unreviewed'||mode==='unreviewed'&&f.confidence==='unreviewed'||mode==='app'&&f.address>='08010000'||mode==='boot'&&f.address<'08010000')&&(!q||JSON.stringify(f).toLowerCase().includes(q)));el('count').textContent=xs.length+' matches';el('list').innerHTML=xs.map(f=>'<a href="#'+f.address+'">'+esc(f.name)+'<small>'+f.address+' · '+f.size+' bytes · '+f.confidence+'</small></a>').join('');}
function select(){const f=by.get(location.hash.slice(1));if(!f)return;el('detail').innerHTML='<h2>'+esc(f.name)+'</h2><span class="pill">0x'+f.address+'</span> <span class="pill">'+f.confidence+'</span><p>'+esc(f.evidence)+'</p><h3>Calls</h3><p>'+links(f.calls)+'</p><h3>Called by</h3><p>'+links(f.callers)+'</p><h3>Referenced strings</h3><p>'+f.strings.map(s=>esc(s[0]+': '+s[1])).join('<br>')+'</p><h3>Hardware addresses</h3><p>'+esc(f.registers.join(', '))+'</p><h3>Annotated decompiler output</h3><pre>'+esc(f.code)+'</pre>';el('detail').scrollTop=0;}
el('q').addEventListener('input',render);el('filter').addEventListener('change',render);window.addEventListener('hashchange',select);render();select();</script></html>'''
page=page.replace('__COUNT__',str(len(funcs))).replace('__DATA__',json.dumps(list(funcs.values())).replace('<','\\u003c').replace('>','\\u003e'))
(out/'Firmware-Explorer.html').write_text(page,encoding='utf-8')
print(json.dumps(meta,indent=2))
