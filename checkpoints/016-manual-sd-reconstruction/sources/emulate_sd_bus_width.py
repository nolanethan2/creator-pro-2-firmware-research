from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
env={}
def hook(uc,a,size,data):
    variant=env['variant'];result=None
    if a==variant['response']:result=env['locked']<<25
    elif a==variant['scr']:
        p=uc.reg_read(UC_ARM_REG_R1);uc.mem_write(p,struct.pack('<2I',0,env['support']));result=env['scr_error']
    elif a==variant['send']:
        p=uc.reg_read(UC_ARM_REG_R0);env['commands'].append(list(struct.unpack('<5I',uc.mem_read(p,20))));result=0
    elif a==variant['check']:
        cmd=uc.reg_read(UC_ARM_REG_R0);env['checked'].append(cmd);result=env['cmd55_error']if cmd==55 else env['cmd6_error']
    if result is not None:uc.reg_write(UC_ARM_REG_R0,result);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,hook)
variants=[dict(name='boot',entry=0x08002ee8,response=0x08001aa0,scr=0x08002d44,send=0x08001a5e,check=0x08002c16,rca=0x20000040),dict(name='application',entry=0x08018a54,response=0x08030728,scr=0x080188b0,send=0x080306e6,check=0x08018782,rca=0x20000324)]
cases=[dict(name='locked',locked=1,expect=14),dict(name='SCR failure',scr_error=5,expect=5),dict(name='wide unsupported',support=0,expect=37),dict(name='wide success',expect=0),dict(name='single success',wide=0,support=0x10000,expect=0),dict(name='non-one selector follows single branch',wide=2,support=0x10000,expect=0),dict(name='single unsupported',wide=0,support=0x40000,expect=37),dict(name='CMD55 failure',cmd55_error=9,expect=9),dict(name='ACMD6 failure',cmd6_error=7,expect=7)]
rows=[]
for variant in variants:
    for c in cases:
        u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram);u.mem_write(variant['rca'],struct.pack('<H',0x1234))
        env.update(variant=variant,locked=c.get('locked',0),support=c.get('support',0x40000),scr_error=c.get('scr_error',0),cmd55_error=c.get('cmd55_error',0),cmd6_error=c.get('cmd6_error',0),commands=[],checked=[])
        wide=c.get('wide',1);actual=call(variant['entry'],wide);assert actual==c['expect']
        commands=env['commands'][:]
        if commands:
            assert commands[0]==[0x12340000,55,0x40,0,0x400]
            if len(commands)==2:assert commands[1]==[2 if wide==1 else 0,6,0x40,0,0x400]
        rows.append(dict(variant=variant['name'],test=c['name'],selector=wide,result=actual,commands=commands,response_checks=env['checked'][:]))
result=dict(method='Original two bus-width routines. SD response, SCR reader, command sender and response checker intercepted; no SDIO/card or physical storage access. Reconstructed control flow tested against return codes and complete command descriptors.',checks=rows)
(root/'outputs/sd-bus-width-verification.json').write_text(json.dumps(result,indent=2));print('18 SD bus-width cases passed across boot/application copies')
