from pathlib import Path
import sys,struct,json,math
sys.path.insert(0,str(Path(__file__).parent/'pylibs'))
from unicorn import Uc,UC_ARCH_ARM,UC_MODE_THUMB,UC_HOOK_CODE
from unicorn.arm_const import *
root=Path(__file__).resolve().parent.parent
flash=Path(r'C:\Users\tech\Desktop\creator pro backup.bin').read_bytes()
ram=(root/'work/app-initialized-ram.bin').read_bytes()
u=Uc(UC_ARCH_ARM,UC_MODE_THUMB)
u.mem_map(0x08000000,0x101000);u.mem_write(0x08000000,flash)
u.mem_map(0x20000000,0x20000);u.mem_write(0x20000000,ram)
u.reg_write(UC_ARM_REG_C1_C0_2,0xf00000);u.reg_write(UC_ARM_REG_FPEXC,0x40000000)
stop=0x08100000
u.hook_add(UC_HOOK_CODE,lambda uc,a,size,data:uc.emu_stop() if a==stop else None)
def bits(x):return struct.unpack('<I',struct.pack('<f',x))[0]
def flt(x):return struct.unpack('<f',struct.pack('<I',x))[0]
def call(address,*args):
    u.reg_write(UC_ARM_REG_SP,0x2001f000);u.reg_write(UC_ARM_REG_LR,stop|1)
    for r,v in zip([UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3],args):u.reg_write(r,v&0xffffffff)
    u.emu_start(address|1,stop,count=200000)
    if u.reg_read(UC_ARM_REG_PC)!=stop:raise RuntimeError('Instruction budget exceeded')
    return u.reg_read(UC_ARM_REG_R0)
tests=[]
for a,name,x,y,expected in [(0x0804b79a,'fadd',3.5,2.25,5.75),(0x0804b7c4,'fdiv',7.5,2.5,3),(0x0804b8d0,'fmul',1.5,4,6),(0x0804b9bc,'fsub',7.5,2.5,5),(0x0804b9aa,'frsub',7.5,2.5,-5)]:
    result=flt(call(a,bits(x),bits(y)));assert result==expected
    tests.append(dict(test=name,inputs=[x,y],expected=expected,actual=result))
pid=0x20010000
u.mem_write(pid,bytes(0x40));u.mem_write(pid,struct.pack('<fff',1,.5,.25));u.mem_write(pid+0x2c,struct.pack('<i',100))
for measured,expected in [(90,34),(92,38)]:
    result=call(0x08015c10,pid,bits(measured));assert result==expected,(measured,result)
    tests.append(dict(test='PID_Update',measured=measured,expected=expected,actual=result))
sensor_results=[]
for table,raw,cap in [(0,1721,255),(0,4086,255),(1,1247,400),(1,1248,400),(1,2152,400)]:
    value=call(0x080175b8,raw,table,cap);sensor_results.append(dict(table=table,raw=raw,cap=cap,value=value))
assert [x['value']for x in sensor_results]==[126,0xffffffe3,240,400,400]
import random
rng=random.Random(407)
def f32(v):return flt(bits(v))
model=dict(integral=0.,last_error=0.,delta_sum=0.,history=[0.]*4,index=0)
u.mem_write(pid,bytes(0x40));kp,ki,kd=1.25,.125,.5
u.mem_write(pid,struct.pack('<fff',kp,ki,kd));u.mem_write(pid+0x2c,struct.pack('<i',100))
for i in range(128):
    measured=float(rng.randint(-200,400));error=f32(100-measured)
    model['integral']=max(-256.,min(256.,f32(model['integral']+error)))
    delta=f32(error-model['last_error']);index=model['index']
    model['delta_sum']=f32(f32(model['delta_sum']-model['history'][index])+delta)
    model['history'][index]=delta;model['index']=(index+1)%4;model['last_error']=error
    total=f32(f32(f32(kp*error)+f32(ki*model['integral']))+f32(kd*model['delta_sum']))
    expected=(math.trunc(total)*2)&0xffffffff
    actual=call(0x08015c10,pid,bits(measured));assert actual==expected,(i,measured,actual,expected)
    assert flt(int.from_bytes(u.mem_read(pid+0x28,4),'little'))==model['integral']
result=dict(method='Unicorn offline execution of original instructions; no peripheral/device access',tests=tests,sensor_boundary_cases=sensor_results,pid_sequence_check=dict(samples=128,seed=407,reference='finite float32 reconstructed algorithm, operation-by-operation rounding, integral clamp, four-slot history and truncation before doubling',all_passed=True))
(root/'outputs/numeric-emulation-verification.json').write_text(json.dumps(result,indent=2))
print(json.dumps(result,indent=2))
