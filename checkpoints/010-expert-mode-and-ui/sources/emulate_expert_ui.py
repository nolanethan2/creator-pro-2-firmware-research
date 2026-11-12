from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
env={'calls':[],'writes':[]}
def stub(uc,a,size,data):
    r0,r1=[uc.reg_read(r)for r in [UC_ARM_REG_R0,UC_ARM_REG_R1]];value=None
    if a==0x080425ae:value=r0 # fake source handle equals widget ID
    elif a==0x08042518:value=r1 # fake returned handle equals requested ID
    elif a==0x0801b50a:env['writes'].append(dict(offset=r0,word=hex(r1),value=flt(r1)));value=0
    elif a==0x08016f7a:value=0
    elif a==0x08023f7e:env['calls'].append(dict(address=hex(a),operation='return_settings'));value=0
    elif 0x08035d3c<=a<0x08049500:
        env['calls'].append(dict(address=hex(a),r0=r0,r1=r1))
        if a==0x08037a74:uc.mem_write(r0,b'emulated\0')
        value=0
    if value is not None:uc.reg_write(UC_ARM_REG_R0,value);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,stub)
def wf(a,v):u.mem_write(a,struct.pack('<f',v))
def rf(a):return struct.unpack('<f',u.mem_read(a,4))[0]
def reset():
    u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram)
    u.mem_write(0x200000c0,bytes(4));env.update(calls=[],writes=[])
def event(widget):
    p=0x20010000;u.mem_write(p,struct.pack('<4I',0x26,0x55,widget,2));call(0x08028688,p)
results=[]
for widget,axis,expected in [(0x172,'X',-.05),(0x174,'X',.05),(0x175,'Y',-.05),(0x177,'Y',.05)]:
    reset();event(widget);delta=rf(0x200004b0+(4 if axis=='Y'else 0));assert abs(delta-expected)<1e-7
    assert not env['writes'];results.append(dict(test='adjust',widget=hex(widget),axis=axis,delta=delta,persistent_writes=0))
reset();wf(0x20001028,1.);wf(0x2000102c,2.);wf(0x200004b0,.1);wf(0x200004b4,-.2);event(0x178)
assert abs(rf(0x20001028)-1.1)<1e-6 and abs(rf(0x2000102c)-1.8)<1e-6
assert [x['offset']for x in env['writes']]==[0,4]and rf(0x200004b0)==rf(0x200004b4)==0
results.append(dict(test='OK commits X/Y additions and clears staging',writes=env['writes'][:]))
reset();wf(0x20001028,1.);wf(0x2000102c,2.);wf(0x200004b0,.1);wf(0x200004b4,-.2);event(0x179)
assert not env['writes']and rf(0x20001028)==1. and rf(0x2000102c)==2. and rf(0x200004b0)==rf(0x200004b4)==0
results.append(dict(test='Cancel clears staging without committing',persistent_writes=0))
for widget in [1,2]:
    reset();wf(0x200004b0,.1);event(widget);assert not env['writes']and abs(rf(0x200004b0)-.1)<1e-6
    results.append(dict(test='generic close notification',widget=widget,staged_delta_retained=rf(0x200004b0),limit='Not proof these notification IDs are reachable by a normal touch control'))
reset();p=0x20010000;u.mem_write(p,struct.pack('<4I',0x26,0x55,0x179,2))
call(0x08023e2e,p)
assert any(x.get('address')=='0x803c27c' and x.get('r0')==0x080ad84c for x in env['calls'])
results.append(dict(test='Settings Expert Mode button creates intro dialog',widget='0x179',table='0x080AD84C'))
result=dict(method='Original callback and finite float arithmetic instructions in offline Unicorn. GUI window/widget APIs, formatting, delays and EEPROM persistence are intercepted. No hardware access. This tests callbacks, not the complete physical touchscreen flow.',checks=results)
(root/'outputs/expert-mode-verification.json').write_text(json.dumps(result,indent=2));print(json.dumps(result,indent=2))
