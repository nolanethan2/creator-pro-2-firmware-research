import os
from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
env={'busy':0,'ready':True,'calls':[]}
def stub(uc,a,size,data):
    r0=uc.reg_read(UC_ARM_REG_R0);r1=uc.reg_read(UC_ARM_REG_R1);value=None
    if a==0x08049d00:value=env['busy']
    elif a==0x08017d4c:value=int(env['ready'])
    elif a==0x08017c98:
        uc.mem_write(r0+0x5c,struct.pack('<I',r1));env['calls'].append(dict(address=hex(a),heater=hex(r0),target=r1));value=0
    elif a==0x08030042:value=1
    elif a==0x080156a2:value=0
    elif a==0x0802b900:uc.mem_write(r0,bytes(20));value=0
    elif a in [0x08011be2,0x08011c28,0x08011d00,0x08011c1a,0x08015b04,0x0801bf76,0x080180a4,0x0801bf6a,0x08015852,0x0802c176,0x0803c99c,0x0801c28a,0x08018402]:
        env['calls'].append(dict(address=hex(a),r0=r0,r1=r1));value=0
    if value is not None:uc.reg_write(UC_ARM_REG_R0,value);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,stub)
def setstate(v):u.mem_write(0x2000004e,bytes([v]))
def state():return u.mem_read(0x2000004e,1)[0]
u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram)
for a,v in [(0x20000066,60),(0x20000068,200),(0x2000006a,210)]:u.mem_write(a,struct.pack('<h',v))
for a,v in [(0x20001e40,200),(0x20001eec,210),(0x20001f98,60)]:u.mem_write(a+0x5c,struct.pack('<I',v))
transitions=[]
for s,want in [(0x40,0x41),(0x41,0x42),(0x42,0x43),(0x43,0x44),(0x44,0x45),(0x45,1),(0x80,0x81),(0x81,0x83),(0x83,0x84),(0x84,0x85),(0x85,0x86),(0x86,0x87),(0x87,0)]:
    setstate(s);env['calls']=[];call(0x0801217e);actual=state();assert actual==want,(hex(s),hex(actual),hex(want))
    transitions.append(dict(state=hex(s),next=hex(actual),calls=env['calls'][:]))
holds=[]
for s in [0x41,0x43,0x45,0x85,0x87]:
    setstate(s);env['busy']=1;call(0x0801217e);assert state()==s;holds.append(dict(state=hex(s),condition='planner busy',next=hex(state())))
env['busy']=0;env['ready']=False
for s in [0x81,0x83]:
    setstate(s);call(0x0801217e);assert state()==s;holds.append(dict(state=hex(s),condition='required heater not ready',next=hex(state())))
result=dict(method='Original state-dispatch ARM instructions in offline Unicorn. Planner status, heater readiness/setters, GPIO read, motion/extrusion operations and UI interfaces are stubs. Tests validate state sequencing and waits, not physical motion or heating.',transitions=transitions,hold_cases=holds)
(root/'outputs/print-state-verification.json').write_text(json.dumps(result,indent=2));print('Passed',len(transitions),'state transitions and',len(holds),'wait cases')
