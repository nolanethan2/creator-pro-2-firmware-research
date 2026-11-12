import os
from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
import random
def f32(v):return flt(bits(v))
def put(a,v):u.mem_write(a,struct.pack('<I',v&0xffffffff))
def read(a):return struct.unpack('<I',u.mem_read(a,4))[0]
def irq_hook(uc,a,size,data):
    if a==0x0802b064:uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,irq_hook)
block=0x20010000;rng=random.Random(407128)
cases=[(1000,2000,1000,0.,0.),(1000,100,1000,.1,.1),(1000,1,1000,0.,0.),(100,200,1000,.5,.5),(1000,2000,0,.25,.5),(1000,100,1000,1.5,1.5)]
cases += [(rng.randint(200,15000),rng.randint(1,5000),rng.randint(1,5000),rng.choice([0.,.125,.25,.5,1.,1.5]),rng.choice([0.,.125,.25,.5,1.,1.5]))for _ in range(128)]
checks=[]
def model(nominal,n,accel,entry,exit,enabled):
    initial=max(120,math.trunc(f32(f32(nominal)*min(f32(entry),1.))+0.5))if enabled else max(120,nominal)
    final=max(120,math.trunc(f32(f32(nominal)*min(f32(exit),1.))+0.5))if enabled else max(120,nominal)
    accsteps=math.trunc((nominal*nominal-initial*initial)/(2*accel))if accel and enabled else 0
    decsteps=math.trunc((nominal*nominal-final*final)/(2*accel))if accel and enabled else 0
    plateau=n-accsteps-decsteps
    if plateau<0:
        accsteps=math.trunc((2*accel*n-initial*initial+final*final)/(4*accel))if accel else 0
        accsteps=max(0,min(n,accsteps));plateau=0
    return dict(initial_rate=initial,final_rate=final,accelerate_until=accsteps,decelerate_after=accsteps+plateau,plateau_steps=plateau)
def run(nominal,n,accel,entry,exit,enabled=1,busy=0,advance=0):
    u.mem_write(block,bytes(128));put(block+0x14,n);put(block+0x60,nominal);put(block+0x64,nominal*nominal);put(block+0x70,accel)
    u.mem_write(block+0x74,bytes([enabled,0,busy]));u.mem_write(block+0x3b,bytes([advance]));u.mem_write(0x20000590,struct.pack('<ff',.125,0.))
    put(block+0x2c,0x11223344);put(block+0x30,0x55667788)
    before=bytes(u.mem_read(block,128));call(0x08029d88,block,bits(entry),bits(exit));after=bytes(u.mem_read(block,128))
    if busy:assert before==after;return dict(busy_preserved=True)
    expected=model(nominal,n,accel,entry,exit,enabled)
    assert read(block+0x68)==expected['initial_rate']and read(block+0x6c)==expected['final_rate'],(nominal,n,accel,entry,exit,expected,read(block+0x68),read(block+0x6c))
    if enabled:assert read(block+0x2c)==(expected['accelerate_until']&0xffffffff)and read(block+0x30)==(expected['decelerate_after']&0xffffffff),(nominal,n,accel,entry,exit,expected,read(block+0x2c),read(block+0x30))
    else:assert read(block+0x2c)==0x11223344 and read(block+0x30)==0x55667788
    if advance:
        peak=nominal if expected['plateau_steps'] else math.trunc(f32(math.sqrt(f32(expected['initial_rate']**2+2*accel*(expected['accelerate_until']+1)))))
        a0=max(0,math.trunc(f32(f32(peak-expected['initial_rate'])*.125)))if expected['accelerate_until']>0 else 0
        a1=max(0,math.trunc(f32(f32(peak-expected['final_rate'])*.125)))if expected['decelerate_after']+1<n else 0
        actual=struct.unpack('<hh',u.mem_read(block+0x3c,4));assert actual==(a0,a1),(expected,peak,actual,a0,a1)
        expected.update(advance_initial=a0,advance_final=a1)
    return expected
for nominal,n,accel,entry,exit in cases:
    checks.append(dict(nominal_rate=nominal,step_events=n,acceleration=accel,entry_factor=entry,exit_factor=exit,result=run(nominal,n,accel,entry,exit)))
extra=[]
for enabled,busy in [(0,0),(0,1),(1,1)]:extra.append(dict(enabled=enabled,busy=busy,result=run(1000,2000,1000,.25,.5,enabled,busy)))
for n,entry,exit in [(2000,0.,0.),(100,0.,0.),(100,.5,.25),(1,0.,0.)]:extra.append(dict(advance=True,step_events=n,entry=entry,exit=exit,result=run(1000,n,1000,entry,exit,advance=1)))
result=dict(method='Original 0x08029D88 instructions including all floating-point helpers; only interrupt-critical-section wrapper intercepted. Independent kinematic reference uses finite normal inputs with 32-bit products below overflow. Advanced extrusion test uses factor .125 and secondary factor zero.',profile_checks=len(checks),extra_checks=len(extra),checks=checks,extras=extra)
(root/'outputs/trapezoid-verification.json').write_text(json.dumps(result,indent=2));print(f'{len(checks)} trapezoid profiles and {len(extra)} busy/nonaccelerated/advance checks passed')
