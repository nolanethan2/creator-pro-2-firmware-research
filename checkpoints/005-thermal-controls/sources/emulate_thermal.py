"""Execute original heater instructions offline, replacing only environment interfaces."""
exec((__import__('pathlib').Path(__file__).parent/'emulate_numeric.py').read_text())
state={'status':0,'temp':20,'expired':set(),'output':[],'ready':1}
heater=0x20011000
def environment(uc,a,size,data):
    result=None
    if a==0x0801786c:
        uc.mem_write(0x20000312,struct.pack('<hh',state['temp'],state['temp']))
        result=state['status']
    elif a==0x080176f8:
        uc.mem_write(0x200002fc,struct.pack('<h',state['temp']));result=state['status']
    elif a==0x08049b88:result=0
    elif a==0x08016212:result=int(uc.reg_read(UC_ARM_REG_R0) in state['expired'])
    elif a==0x08017d4c:result=state['ready']
    elif a==0x08017aca:
        state['output'].append([uc.reg_read(UC_ARM_REG_R0),uc.reg_read(UC_ARM_REG_R1)]);result=0
    if result is not None:
        uc.reg_write(UC_ARM_REG_R0,result);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,environment)
def fresh(id=4,target=100,temp=20):
    u.mem_write(heater,bytes(0xac));u.mem_write(heater+0x90,bytes([id]))
    u.mem_write(heater+0x24,struct.pack('<hh',temp,temp));u.mem_write(heater+0x30,struct.pack('<fff',1,.5,.25))
    u.mem_write(0x20000248,bytes(4));state.update(status=0,temp=temp,expired=set(),output=[],ready=1)
    call(0x08017c98,heater,target)
def rd(off,n=1):return int.from_bytes(u.mem_read(heater+off,n),'little')
checks=[]
for id,request,want in [(2,999,120),(4,999,240),(3,-5,0)]:
    fresh(id,request);actual=rd(0x5c,4);assert actual==want
    checks.append(dict(test='target_clamp',heater_id=id,request=request,expected=want,actual=actual))
for bypass in [0x65,0x8f]:
    fresh();u.mem_write(heater+bypass,b'\x01');call(0x08017c98,heater,200)
    assert rd(0x5c,4)==0;checks.append(dict(test='target_inhibited',field=hex(bypass),actual=0))
for name,status,temp,timers,expected in [('sensor_status_3',3,20,[],2),('sensor_status_4',4,20,[],32),('over_temperature',0,261,[],4),('rise_timeout',0,20,[0x7c],8),('long_term_deficit',0,60,[0x6c],16)]:
    fresh();state.update(status=status,temp=temp,expired={heater+x for x in timers})
    for i in range(50):call(0x08017e7c,heater)
    assert rd(0x65)==0,(name,'early fault')
    call(0x08017e7c,heater)
    code=rd(0x68);disabled=rd(0x65);target=rd(0x5c,4);record=int.from_bytes(u.mem_read(0x20000248,2),'little')
    assert (code,disabled,target,state['output'][-1],record)==(expected,1,0,[4,0],0x400|expected),(name,code,disabled,target,record)
    checks.append(dict(test=name,calls_to_trip=51,fault_code=code,disabled=disabled,target=target,last_output=state['output'][-1],record=hex(record)))
for status in [1,2]:
    fresh();state['status']=status
    for i in range(60):call(0x08017e7c,heater)
    assert rd(0x65)==0 and rd(0x66)==0
    checks.append(dict(test='busy_sensor_status',status=status,calls=60,disabled=0,sensor_error_count=0))
fresh(target=100,temp=20);call(0x08017e7c,heater);assert state['output'][-1]==[4,255]
checks.append(dict(test='cold_full_power',error=80,output=255))
fresh(target=0,temp=20);call(0x08017e7c,heater);assert state['output'][-1]==[4,0]
checks.append(dict(test='zero_target_output',output=0))
result=dict(method='Original ARM instructions in Unicorn only. Sensor readings, timer expiry, readiness predicate and output driver are deterministic stubs. No hardware access; not a hardware safety certification.',checks=checks)
(root/'outputs/thermal-emulation-verification.json').write_text(json.dumps(result,indent=2))
print(json.dumps(result,indent=2))
