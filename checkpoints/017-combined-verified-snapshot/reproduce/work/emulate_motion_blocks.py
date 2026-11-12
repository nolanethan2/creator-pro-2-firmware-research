import os
from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
stubs={0x0802b19e,0x08017218,0x0802b55c,0x0802b5c8,0x0802b5c2,0x0802b5a8,0x08029a88,0x0802b064,0x0804a150,0x0802a32c}
def hook(uc,a,size,data):
    if a in stubs:uc.reg_write(UC_ARM_REG_R0,0);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,hook)
def put(a,v,n=4):u.mem_write(a,int(v).to_bytes(n,'little',signed=v<0))
def ri(a):return int.from_bytes(u.mem_read(a,4),'little')
def rf(a):return struct.unpack('<f',u.mem_read(a,4))[0]
def wf(a,v):u.mem_write(a,struct.pack('<f',v))
cases=[dict(name='X move',delta=[10,0,0,0,0],speed=20),dict(name='X plus extrusion',delta=[10,0,0,1,0],speed=20),dict(name='extrusion only',delta=[0,0,0,1,0],speed=20),dict(name='second extruder only',delta=[0,0,0,0,1],speed=20),dict(name='negative X direction',delta=[-10,0,0,0,0],speed=20),dict(name='ring head wraps',delta=[10,0,0,0,0],speed=20,head=15),dict(name='queue low-water slowdown',delta=[10,0,0,0,0],speed=20,head=4,tail=0,slow_guard=0),dict(name='high speed with internal clamp gate',delta=[10,0,0,0,0],speed=1000,limit_gate=1),dict(name='high speed without internal clamp gate',delta=[10,0,0,0,0],speed=1000,limit_gate=0),dict(name='nonaccelerated X',delta=[10,0,0,0,0],speed=20,accelerated=0)]
rows=[]
for c in cases:
    u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram)
    scales=[80.,80.,400.,96.,96.]
    for i,scale in enumerate(scales):wf(0x2000a29c+i*0x30+4,scale);wf(0x2000a29c+i*0x30+8,[150,150,20,100,100][i])
    call(0x0802b5f0)
    head=c.get('head',0);tail=c.get('tail',head);put(0x200005b1,head,1);put(0x200005b2,tail,1);put(0x2000058c,c.get('slow_guard',1),1);put(0x200006a0,c.get('limit_gate',0),1)
    deltas=c['delta'];target=[round(x*s)for x,s in zip(deltas,scales)];steps=[abs(x)for x in target];events=max(steps);dominant=steps.index(events);length=math.sqrt(sum(x*x for x in deltas[:3]))or abs(deltas[3]or deltas[4]);nominal=round(c['speed']/length*events)
    for i in range(5):put(0x20009a38+i*4,steps[i]);put(0x20009a74+i*4,target[i]);wf(0x20009a24+i*4,deltas[i])
    put(0x2000059c,events);put(0x200005a0,dominant,1);wf(0x20000598,length);put(0x2001f000,0x15)
    call(0x0802a37c,bits(c['speed']),nominal,0,c.get('accelerated',1))
    block=0x20009a9c+head*128
    result=dict(axis_steps=[ri(block+i*4)for i in range(5)],step_events=ri(block+0x14),direction_bits=ri(block+0x38)&255,tool=(ri(block+0x38)>>8)&255,advance_enabled=u.mem_read(block+0x3b,1)[0],nominal_speed=rf(block+0x48),nominal_rate=ri(block+0x60),initial_rate=ri(block+0x68),final_rate=ri(block+0x6c),accelerate_until=ri(block+0x2c),decelerate_after=ri(block+0x30),next_head=u.mem_read(0x200005b1,1)[0],final_steps=[ri(0x20009a60+i*4)for i in range(5)])
    assert result['axis_steps']==steps and result['step_events']==events and result['next_head']==(head+1)%16
    assert result['final_steps']==[x&0xffffffff for x in target]
    assert result['direction_bits']==sum(1<<i for i,x in enumerate(target)if x<0)
    assert result['advance_enabled']==int(any(deltas[:3])and any(deltas[3:])and c.get('accelerated',1))
    rows.append(dict(inputs=c,result=result))
assert rows[6]['result']['nominal_speed']==10.
assert rows[7]['result']['nominal_speed']==150. and rows[8]['result']['nominal_speed']==500. # other minimum-segment-time limiting remains active
assert rows[3]['result']['tool']==1
result=dict(method='Original motion-block builder, trapezoid and arithmetic instructions; seeded initialized configuration/scales and displacement inputs. Axis/I/O/timer setup, motor-enable, interrupt wrappers and final multi-block lookahead pass intercepted. This isolates block construction, not the full command-to-motor path.',checks=rows)
(root/'outputs/motion-block-verification.json').write_text(json.dumps(result,indent=2));print(json.dumps(result,indent=2))
