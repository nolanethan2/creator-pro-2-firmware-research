from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
import re,itertools
def w8(a,v):u.mem_write(a,bytes([v&255]))
def w32(a,v):u.mem_write(a,struct.pack('<I',v&0xffffffff))
def wf(a,v):w32(a,bits(v))
def r8(a):return u.mem_read(a,1)[0]
def ri(a):return struct.unpack('<i',u.mem_read(a,4))[0]
def rf(a):return struct.unpack('<f',u.mem_read(a,4))[0]
environment={'writes':[],'gpio':[]}
def env(uc,a,size,data):
    result=None
    args=[uc.reg_read(r)for r in [UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2]]
    if a==0x0801361c:
        environment['writes'].append(dict(offset=args[0],value=args[1]&255));environment['eeprom'][args[0]]=args[1]&255;result=0
    elif a==0x080105fa:
        cursor=int.from_bytes(uc.mem_read(0x2000023c,4),'little')
        tail=bytes(uc.mem_read(cursor+1,80)).split(b'\0')[0].decode()
        token=re.match(r'\s*[-+]?(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][-+]?\d+)?',tail)
        result=bits(float(token[0])if token else 0.)
    elif a==0x08013760:result=environment.get('eeprom',{}).get(args[0],args[1])
    elif a==0x0802b19e:result=0 # planner reinitialization is outside this profile test
    elif a in [0x0803005c,0x08030060]:
        environment['gpio'].append(dict(port=hex(args[0]),mask=hex(args[1]),high=a==0x0803005c));result=0
    if result is not None:uc.reg_write(UC_ARM_REG_R0,result);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,env)
def reset():
    u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram)
    w8(0x2000003c,0);w8(0x20000350,1);w32(0x200000c0,0)
    for off,value in [(0x54,200),(0x58,148),(0x5c,150)]:w32(0x20000110+off,value)
    wf(0x20001028+8,0)
    environment.update(writes=[],gpio=[],eeprom={})
def command(text):u.mem_write(0x20000b9c,text.encode()+bytes(96-len(text)));w8(0x2000003c,0)
def flags():return {hex(a):r8(a)for a in [0x2000000e,0x20000011,0x20000012,0x2000001d,0x2000001e,0x2000001f,0x2000002a,0x20000044,0x20000217]}
cases=[]
for text in ['M118 X20 Y20 Z20 T0','M118 X20 Y20 Z20 T0 T1','M118 X20 Y20 Z20 T0 T1 D1','M118 X20 Y20 Z20 T0 T1 D2','M118 X20 Y20 Z20 T0 T1 D3']:
    reset();command(text)
    try:call(0x08011266)
    except Exception as e:raise RuntimeError(f'{text}: pc={u.reg_read(UC_ARM_REG_PC):08x}: {e}')from e
    cases.append(dict(command=text,flags=flags()))
assert [x['flags']['0x2000000e']for x in cases]==[0,1,1,1,1]
assert [x['flags']['0x2000001e']for x in cases]==[0,0,1,1,0]
profiles=[]
for profile in [0x11,0x12]:
    reset();call(0x08013ab4,profile)
    profiles.append(dict(profile=hex(profile),index=r8(0x2000010c),persisted_writes=environment['writes'][:],config_selected_fields={hex(off):ri(0x20000110+off)for off in [8,12,0x7c,0x80,0x84,0x88,0x90,0x94]}))
assert profiles[0]['config_selected_fields']==profiles[1]['config_selected_fields']
selectors=[]
for selector in [1,2,3]:
    reset();call(0x08013940,selector)
    selectors.append(dict(input=selector,persisted=environment['writes'][:],config_selector=r8(0x2000012c),single_extruder_predicate=call(0x080135fc),x_home_steps=ri(0x20000118),y_home_steps=ri(0x2000011c)))
assert [x['config_selector']for x in selectors]==[1,2,2]
assert [x['single_extruder_predicate']for x in selectors]==[1,0,0]
moves=[]
for name,flags_in in [('ordinary',{}),('copy_calibration',{0x2000000c:1}),('mirror_compensation',{0x2000000d:1,0x20000012:1}),('duplicate_compensation',{0x2000000d:1,0x20000012:2})]:
    reset();command('G1 X20 Y20 Z20 E5 F600');wf(0x20000084,1.)
    for a,v in flags_in.items():w8(a,v)
    call(0x080106f4)
    moves.append(dict(mode=name,input_xyz=[20,20,20],parsed_xyz=[rf(0x20000fe0+x*4)for x in range(3)]))
assert [x['parsed_xyz'][0]for x in moves]==[20.,86.,-86.,-46.]
step_modes=[]
for mode in [1,2]:
    reset();command(f'M111 T{mode}');wf(0x2000a2a0,80.);call(0x080114b8)
    assert r8(0x20000001)==1 and r8(0x20000002)==1 and r8(0x20000013)==mode
    axis=0x2000a29c
    for off,value in [(0x1c,1),(0x24,0),(0x28,0),(0x2c,1)]:w32(axis+off,value)
    for off,value in [(1,0),(0x20,0),(0x21,1),(0x22,0),(0x23,1)]:w8(axis+off,value)
    w8(0x20000005,0);w32(0x20000684,0);w32(0x20000688,0)
    call(0x0804a3a8,0)
    primary,secondary=ri(0x20000684),ri(0x20000688)
    assert (primary,secondary)==(1,-1 if mode==1 else 1),(mode,primary,secondary)
    step_modes.append(dict(command=f'M111 T{mode}',primary_counter_delta=primary,secondary_counter_delta=secondary,gpio_requests=environment['gpio'][:]))
bounds=[]
for mode,x,y,z in [(0,100,74,150),(0,101,74,150),(1,47.5,74,150),(1,47.6,74,150),(2,47.5,74,150),(2,20,75,150),(2,20,20,151)]:
    reset();text=f'M118 X{x} Y{y} Z{z} T0 T1 D{mode}';command(text);call(0x08011266)
    bounds.append(dict(command=text,out_of_bounds_flag=r8(0x20000217)))
assert [x['out_of_bounds_flag']for x in bounds]==[0,1,0,1,0,1,1]
persistence=[]
reset();command('M118 X20 Y20 Z20 T0 T1 D1');call(0x08011266);command('M118 X20 Y20 Z20 T0');call(0x08011266)
persistence.append(dict(test='D omitted after D1',mode_still=r8(0x20000011),setup_flag=r8(0x2000001e)))
assert r8(0x20000011)==1 and r8(0x2000001e)==1
result=dict(method='Original instructions for field search/last-field search, selector handlers, math, coordinate parsing and axis stepping in Unicorn. Decimal-number conversion is stubbed from the cursor because C-runtime locale initialization is absent. EEPROM writes/readback, GPIO and planner reinitialization are intercepted in memory; no device access. Geometry limits are explicit test inputs 200/148/150, not a live settings read.',m118_cases=cases,profiles=profiles,machine_selector_cases=selectors,coordinate_transform_cases=moves,carriage_step_cases=step_modes,extent_boundary_cases=bounds,omitted_D_case=persistence)
(root/'outputs/idex-selector-verification.json').write_text(json.dumps(result,indent=2))
print(json.dumps(result,indent=2))
