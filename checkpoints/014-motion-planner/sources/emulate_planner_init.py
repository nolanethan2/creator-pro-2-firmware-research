from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
stubs={0x0802b19e,0x08017218,0x0802b55c,0x0802b5c8,0x0802b5c2,0x0802b5a8,0x08029a88}
def hook(uc,a,size,data):
    if a in stubs:uc.reg_write(UC_ARM_REG_R0,0);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,hook)
def put(a,v,n=4):u.mem_write(a,int(v).to_bytes(n,'little'))
def ri(a):return int.from_bytes(u.mem_read(a,4),'little')
def rf(a):return struct.unpack('<f',u.mem_read(a,4))[0]
checks=[]
for first,second,slowdown,accel,expected_accel in [(850,900,1,2000,2000),(0,0,0,2000,2000),(10000,20000,1,20000,10000),(12345,54321,0,3000,3000)]:
    u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram)
    for i,scale in enumerate([80.,80.,400.,96.,96.]):u.mem_write(0x2000a29c+i*0x30+4,struct.pack('<f',scale))
    put(0x20000154,first);put(0x20000158,second);put(0x20000160,slowdown,1);put(0x2000013a,accel,2);put(0x20000150,accel,2)
    call(0x0802b5f0)
    assert bits(rf(0x20000590))==bits(first/100000.)and bits(rf(0x20000594))==bits(second/100000.)
    assert ri(0x20000578)==expected_accel and ri(0x2000057c)==expected_accel and ri(0x20000588)==(8 if slowdown else 0)
    checks.append(dict(config_advance_fields=[first,second],advance_factors=[rf(0x20000590),rf(0x20000594)],slowdown_enabled=slowdown,queue_threshold=ri(0x20000588),requested_acceleration=accel,effective_accelerations=[ri(0x20000578),ri(0x2000057c)],axis_acceleration_limits=[ri(0x20009a10+i*4)for i in range(5)]))
result=dict(method='Original planner initialization and arithmetic. Axis scales seeded 80/80/400/96/96; lower-level axis/I/O/reset/timer setup calls intercepted. No hardware access. Defaults 850/900 and slowdown byte1 are present in decoded initialized RAM.',checks=checks)
(root/'outputs/planner-init-verification.json').write_text(json.dumps(result,indent=2));print(json.dumps(result,indent=2))
