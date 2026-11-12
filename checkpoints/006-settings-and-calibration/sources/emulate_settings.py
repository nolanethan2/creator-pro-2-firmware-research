exec((__import__('pathlib').Path(__file__).parent/'emulate_numeric.py').read_text())
state={'raw':0,'calls':[]}
def settings_environment(uc,a,size,data):
    value=None
    r0=uc.reg_read(UC_ARM_REG_R0);r1=uc.reg_read(UC_ARM_REG_R1)
    if a==0x0801b58e:
        state['calls'].append(dict(operation='float_word_read',storage_address=r0));value=state['raw']
    elif a in [0x08016f7a,0x08031988,0x0803005c,0x08030060]:value=0
    elif a in [0x08013760,0x080137a0,0x080137e6]:
        state['calls'].append(dict(operation={0x08013760:'read_byte_default',0x080137a0:'read_u16_default',0x080137e6:'read_u32_default'}[a],storage_address=r0,default=r1));value=r1
    elif a==0x08013870:
        length=uc.reg_read(UC_ARM_REG_R2);uc.mem_write(r0,bytes([255])*length)
        state['calls'].append(dict(operation='block_read',storage_address=r1,length=length,destination=hex(r0)));value=0
    if value is not None:uc.reg_write(UC_ARM_REG_R0,value);uc.reg_write(UC_ARM_REG_PC,uc.reg_read(UC_ARM_REG_LR))
u.hook_add(UC_HOOK_CODE,settings_environment)
u.mem_write(0x20000350,b'\x01');u.mem_write(0x200000c0,bytes(4))
checks=[]
for x in [-6.,-5.,-4.,0.,4.,5.,6.]:
    state['raw']=bits(x);call(0x08013bca);actual=struct.unpack('<f',u.mem_read(0x20001028,4))[0]
    expected=x if -5<x<5 else 5.
    assert actual==expected,(x,actual)
    checks.append(dict(test='calibration_offset_bounds',input=x,expected=expected,actual=actual))
sentinels=[]
for raw in [0x4f800000,0xffffffff,0,0x3f800000]:
    state['raw']=raw;actual=call(0x08013828,0,bits(2.5))
    sentinels.append(dict(stored_word=hex(raw),returned_word=hex(actual),returned_float_text=str(flt(actual))))
assert [x['returned_word']for x in sentinels]==['0x40200000','0xffffffff','0x0','0x3f800000']
state['raw']=bits(0);state['calls']=[];call(0x08013d70)
result=dict(method='Offline execution only. EEPROM float reads and high-level default reads are stubbed; delays and GPIO/PWR calls are suppressed. Records one serial-backend startup path, not actual saved EEPROM values.',checks=checks,float_default_sentinel_cases=sentinels,serial_startup_reads=state['calls'])
(root/'outputs/settings-emulation-verification.json').write_text(json.dumps(result,indent=2))
print(json.dumps(result,indent=2))
