import os
from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
import re
functions={f['address']:f for f in json.loads((root/'outputs/function-map.json').read_text())}
callees={int(a,16)for a in functions['08014c68']['calls']};state={}
def hook(uc,a,size,data):
    result=None
    if a==0x0804a908:
        p=uc.reg_read(UC_ARM_REG_R0);tail=bytes(uc.mem_read(p,80)).split(b'\0')[0].decode('ascii');m=re.match(r'\s*[-+]?\d+',tail);state['parsed']=int(m[0])if m else 0;result=0;uc.reg_write(UC_ARM_REG_R1,0)
    elif a==0x0804ae94:result=state['parsed']&0xffffffff
    elif a in callees and a!=0x08010608:
        # The real strchr entry is selected below from the recovered name.
        if a==strchr:return
        state['calls'].append(f'{a:08x}');result=0
    if result is not None:uc.reg_write(UC_ARM_REG_R0,result);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
strchr=int(next(f['address']for f in functions.values()if f['name']=='Lib_StrChr_Candidate'),16)
u.hook_add(UC_HOOK_CODE,hook)
def run(text,channel):
    u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram);u.mem_write(0x200010b4,text.encode()+b'\0');u.mem_write(0x20000241,bytes([channel]));state.update(parsed=0,calls=[])
    result=call(0x08014c68)
    return dict(command=text,channel=channel,consumed=bool(result),calls=state['calls'][:])
by_channel={};count=0
expected=[23,24,25,26,27,28,29,105,112,114,115,119,502,504,600,601,602,650,651]
for channel in [0,1]:
    routes=[];unhandled=[]
    for n in range(1001):
        r=run(f'M{n}',channel);count+=1
        if r['calls']:routes.append(r)
        elif not r['consumed']:unhandled.append(n)
    if channel==0:
        assert [int(r['command'][1:])for r in routes]==[601,615] and not unhandled
    else:
        recognized=[n for n in range(1001)if n not in unhandled];assert recognized==expected,recognized
    by_channel[str(channel)]=dict(routes=routes,unhandled_count=len(unhandled),unhandled_numbers=unhandled)
extra=[]
for text in ['G1 X10','M-1','M1001','hello']:
    for channel in [0,1]:
        r=run(text,channel);assert r['consumed']==(channel==0);extra.append(r);count+=1
result=dict(method='Original immediate dispatcher and strchr instructions; decimal-to-double and integer conversion modeled, all external action/report handlers intercepted. Sweep M0..M1000, channels 0/1, initialized inactive print state. This validates routing only; no host or device requests sent.',tested_cases=count,channels=by_channel,extra_cases=extra)
(root/'outputs/immediate-route-verification.json').write_text(json.dumps(result,indent=2));print(f'{count} immediate-route checks passed; 19 active-channel recognized M numbers, 2 zero-channel action routes')
