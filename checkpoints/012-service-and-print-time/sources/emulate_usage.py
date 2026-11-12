from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
env={}
def w(a,v,n=1):u.mem_write(a,int(v).to_bytes(n,'little'))
def r(a,n=1):return int.from_bytes(u.mem_read(a,n),'little')
def hook(uc,a,size,data):
    result=None
    args=[uc.reg_read(x)for x in [UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2]]
    if a in [0x0801361c,0x08013658]:
        n=1 if a==0x0801361c else 2;env['writes'].append(dict(offset=args[0],bytes=n,value=args[1]&((1<<(n*8))-1)));result=0
    elif a in [0x08013760,0x080137a0]:result=env.get('storage',{}).get(args[0],args[1])
    elif a==0x08016f7a:result=0
    elif a==0x08049b88:result=env['now']
    elif a==0x0803429c:
        path=bytearray();p=args[1]
        while bytes(uc.mem_read(p,2))!=b'\0\0':path.extend(uc.mem_read(p,2));p+=2
        env['opens'].append(dict(path=path.decode('utf-16le'),mode=args[2]));result=env['open_result']
    elif a==0x080348b2:env['closes']+=1;result=0
    if result is not None:uc.reg_write(UC_ARM_REG_R0,result);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,hook)
def reset():
    u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram)
    w(0x200000c0,0,4);env.update(now=0,writes=[],storage={},opens=[],closes=0,open_result=4)
def totals():return dict(hours=r(0x200001ee,2),minutes=r(0x200001f0),writes=env['writes'][:])
checks=[]
reset();env['storage']={0x69:1234,0x6b:37};call(0x08013d3e);assert(r(0x200001ee,2),r(0x200001f0))==(1234,37);checks.append(dict(test='load stored hours/minutes',**totals()))
reset();w(0x200001ee,1234,2);w(0x200001f0,37);call(0x0801402c);assert(r(0x200001ee,2),r(0x200001f0))==(0,0);assert [x['offset']for x in env['writes']]==[0x69,0x6b];checks.append(dict(test='M615 reset handler',**totals()))
for flag,status in [(0,0),(0,4),(1,0)]:
    reset();env['open_result']=status;w(0x20000259,flag);w(0x200001ee,7,2);w(0x200001f0,8);call(0x08015826)
    succeeds=flag==0 and status==0
    assert(r(0x200001ee,2),r(0x200001f0))==((0,0)if succeeds else(7,8))
    assert len(env['opens'])==(0 if flag else 1) and env['closes']==(0 if flag else 1)
    checks.append(dict(test='startup service-file gate',flag=flag,open_status=status,opens=env['opens'][:],closes=env['closes'],**totals()))
for elapsed,expired in [(3599999999,False),(3600000000,True),(3600000001,True)]:
    reset();w(0x200001ee,12,2);call(0x080161f4,0x20001064,3600000000);env['now']=elapsed;call(0x0801407c)
    assert r(0x200001ee,2)==12+expired and r(0x2000020c)==expired
    checks.append(dict(test='one-hour timer boundary',elapsed_microseconds=elapsed,**totals()))
for minutes,elapsed,expected in [(10,5,(12,15)),(59,1,(13,0)),(59,59,(13,58))]:
    reset();w(0x200001ee,12,2);w(0x200001f0,minutes);call(0x080161f4,0x20001064,3600000000);env['now']=elapsed*60000000;call(0x0801410a)
    assert(r(0x200001ee,2),r(0x200001f0))==expected and r(0x20001064)==0
    checks.append(dict(test='finalize partial print session',minutes_before=minutes,session_minutes=elapsed,**totals()))
reset();w(0x200001ee,65535,2);call(0x080161f4,0x20001064,3600000000);env['now']=3600000000;call(0x0801407c);assert r(0x200001ee,2)==0;checks.append(dict(test='16-bit cumulative-hour rollover',**totals()))
reset();call(0x080161f4,0x20001064,3600000000);env['now']=600000000;call(0x08016248,0x20001064,1);env['now']=1800000000
assert call(0x08016276,0x20001064)==600000000
call(0x08016248,0x20001064,0);env['now']=2100000000;assert call(0x08016276,0x20001064)==900000000
call(0x0801410a);assert r(0x200001f0)==15;checks.append(dict(test='pause freezes timer; resume excludes 20 paused minutes',active_minutes=15,**totals()))
reset();env['now']=0xf0000000;call(0x080161f4,0x20001064,3600000000);env['now']=(0xf0000000+3600000000)&0xffffffff;call(0x0801407c);assert r(0x200001ee,2)==1;checks.append(dict(test='one-hour interval across unsigned clock wrap',**totals()))
result=dict(method='Original usage/timer/service-file instructions. Time, storage, delay and filesystem interfaces are intercepted. All writes are recorded in memory; no device or real service file was used.',checks=checks)
(root/'outputs/usage-service-verification.json').write_text(json.dumps(result,indent=2));print(f'{len(checks)} usage/service checks passed')
