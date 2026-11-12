import os
from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
env={}
def hook(uc,a,size,data):
    if a==0x0802ba16:
        env['plan']=dict(target=list(struct.unpack('<5f',uc.mem_read(uc.reg_read(UC_ARM_REG_R0),20))),feed=flt(uc.reg_read(UC_ARM_REG_R1)))
        uc.reg_write(UC_ARM_REG_R0,0);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,hook)
checks=[]
for mask in [0,1]:
    for command in ['G162','G162 Z-900','G162 Z999']:
        u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram)
        u.mem_write(0x20000b9c,command.encode()+b'\0');u.mem_write(0x2000003c,b'\0');u.mem_write(0x200006ac,bytes([mask]))
        u.mem_write(0x20000fe0,struct.pack('<5f',10,20,30,40,50));u.mem_write(0x20000ff4,struct.pack('<5f',1,2,3,4,5))
        u.mem_write(0x2000016c,struct.pack('<I',150));u.mem_write(0x20000090,struct.pack('<f',600));env.clear();call(0x080116a4)
        z=150. if 'Z'in command else(0. if mask else 3.)
        target=[10.,20.,z,40.,50.];current=[x+y for x,y in zip([1,2,3,4,5],target)]if mask else target
        actual=list(struct.unpack('<5f',u.mem_read(0x20000ff4,20)))
        assert env['plan']['target']==target and env['plan']['feed']==10. and actual==current and u.mem_read(0x20000089,1)[0]==1
        checks.append(dict(command=command,relative_mask=mask,staged_before=[10,20,30,40,50],current_before=[1,2,3,4,5],planned=env['plan'],current_after=actual))
result=dict(method='Original G162 handler and float instructions with planner intercepted; F field omitted. Deliberately seeded staging values test retained fields, not normal job preconditions. No device access.',checks=checks)
(root/'outputs/g162-verification.json').write_text(json.dumps(result,indent=2));print(f'{len(checks)} G162 checks passed')
