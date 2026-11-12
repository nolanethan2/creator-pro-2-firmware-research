import os
from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
events=[]
def record(uc,a,size,data):
    if a in [0x0804b1f8,0x0804b8e2]:events.append(dict(address=hex(a),lr=hex(uc.reg_read(UC_ARM_REG_LR)),sp=hex(uc.reg_read(UC_ARM_REG_SP))))
u.hook_add(UC_HOOK_CODE,record)
cases=[('add infinity',0x0804a9f4,[math.inf,1.],math.inf),('opposite infinities',0x0804a9f4,[math.inf,-math.inf],math.nan),('add NaN',0x0804a9f4,[math.nan,1.],math.nan),('divide by zero',0x0804ab6c,[1.,0.],math.inf),('negative divide by zero',0x0804ab6c,[-1.,0.],-math.inf),('zero divided by zero',0x0804ab6c,[0.,0.],math.nan),('zero times infinity',0x0804b0a4,[0.,math.inf],math.nan),('subtract infinity',0x0804b570,[math.inf,1.],math.inf),('round infinity',0x0804b30c,[math.inf],math.inf),('round NaN',0x0804b30c,[math.nan],math.nan),('sqrt negative',0x0804b3d8,[-1.],math.nan),('sqrt infinity',0x0804b3d8,[math.inf],math.inf)]
rows=[]
for name,a,values,expected in cases:
    u.mem_write(0x20000000,bytes(0x1e000));u.mem_write(0x20000000,ram);events.clear();args=struct.unpack('<'+'I'*len(values)*2,struct.pack('<'+'d'*len(values),*values))
    try:
        call(a,*args);actual=struct.unpack('<d',struct.pack('<II',u.reg_read(UC_ARM_REG_R0),u.reg_read(UC_ARM_REG_R1)))[0]
        match=math.isnan(actual)if math.isnan(expected)else actual==expected
        rows.append(dict(test=name,address=hex(a),inputs=[repr(v)for v in values],actual=repr(actual),expected=repr(expected),matches_ieee_classification=match,dispatch=events[:],returned_to_original_caller=True))
    except Exception as e:rows.append(dict(test=name,address=hex(a),inputs=[repr(v)for v in values],status='unresolved emulation',error=str(e),pc=hex(u.reg_read(UC_ARM_REG_PC)),dispatch=events[:]))
result=dict(method='Original exceptional arithmetic, no replacement arithmetic or exception hooks. Entry tracing only. Classification comparison allows NaN payload differences. This tests the core arithmetic, not external error reporting or all exception descriptors.',checks=rows)
(root/'outputs/math-exception-verification.json').write_text(json.dumps(result,indent=2));print(json.dumps(result,indent=2))
