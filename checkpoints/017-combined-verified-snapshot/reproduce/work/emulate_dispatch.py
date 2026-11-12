import os
from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
import re
functions={f['address']:f for f in json.loads((root/'outputs/function-map.json').read_text())}
callees={int(a,16) for a in functions['0801177a']['calls']}
allowed={0x08010662,0x0804b808,0x0804b816}
state={}
def hook(uc,a,size,data):
    result=None
    if a==0x080105fa:
        cursor=int.from_bytes(uc.mem_read(0x2000023c,4),'little')
        tail=bytes(uc.mem_read(cursor+1,80)).split(b'\0')[0].decode('ascii')
        token=re.match(r'\s*[-+]?(?:\d+(?:\.\d*)?|\.\d+)',tail)
        result=bits(float(token[0]) if token else 0.)
    elif a in callees and a not in allowed:
        state['calls'].append(dict(address=f'{a:08x}',name=functions.get(f'{a:08x}',{}).get('name'),r0=uc.reg_read(UC_ARM_REG_R0)))
        result=state['gate'] if a==0x08029b72 else 0
    if result is not None:
        uc.reg_write(UC_ARM_REG_R0,result);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,hook)
def run(command,mask=31,gate=1):
    u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram)
    u.mem_write(0x20000b9c,command.encode()+b'\0');u.mem_write(0x2000003c,b'\0');u.mem_write(0x20000040,b'\1')
    u.mem_write(0x200006ac,bytes([mask]));u.mem_write(0x20000048,b'\x20')
    state.update(calls=[],gate=gate)
    call(0x0801177a)
    return dict(command=command,gate=gate,mask_before=mask,mask_after=u.mem_read(0x200006ac,1)[0],queue_count=u.mem_read(0x20000040,1)[0],queue_read_index=u.mem_read(0x2000003c,1)[0],change_counter=u.mem_read(0x20000048,1)[0],calls=state['calls'][:])
checks=[]
for mask in [0,1,31]:
    r=run('G91',mask);assert r['mask_after']==mask and r['queue_count']==0 and r['queue_read_index']==1 and r['change_counter']==32;checks.append(r)
r=run('G90');assert r['mask_after']==0 and r['change_counter']==33;checks.append(r)
for command,handler in [('G0',0x080109f0),('G1',0x080109f0),('G4',0x08010b8a),('G28',0x08010bde),('G92',0x08010cd2),('G93',0x08010cd2),('G162',0x080116a4)]:
    r=run(command);assert f'{handler:08x}'in[x['address']for x in r['calls']];checks.append(r)
for command in ['G161','M146','M201','M204','M205','M206','M221','M301','M304','M612','M999']:
    r=run(command);assert [x['address']for x in r['calls']]==['080106b6'];assert r['queue_count']==0;checks.append(r)
for command in ['G28','G93','M18','M108','M109','M110','M111','M906']:
    r=run(command,gate=0);assert r['queue_count']==1 and r['queue_read_index']==0;assert [x['address']for x in r['calls']]==['08029b72'];checks.append(r)
result=dict(method='Original queued-dispatch instructions and field search/numeric conversion; decimal parser and all external handlers intercepted. Tests establish routing and queue/mode-state changes, not behavior of intercepted handlers. No printer/device access.',checks=checks)
(root/'outputs/dispatch-emulation-verification.json').write_text(json.dumps(result,indent=2));print(f'{len(checks)} queued-dispatch checks passed')
