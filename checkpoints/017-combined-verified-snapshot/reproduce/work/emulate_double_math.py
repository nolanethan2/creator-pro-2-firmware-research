import os
from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
import random
rng=random.Random(40764)
def double_call(address,*values):
    args=list(struct.unpack('<'+'I'*len(values)*2,struct.pack('<'+'d'*len(values),*values)));call(address,*args)
    return struct.unpack('<d',struct.pack('<II',u.reg_read(UC_ARM_REG_R0),u.reg_read(UC_ARM_REG_R1)))[0]
def same(a,b):return struct.pack('<d',a)==struct.pack('<d',b)
pairs=[(rng.uniform(-1000,1000)*2**rng.randint(-20,20),rng.uniform(.125,1000)*rng.choice([-1,1])*2**rng.randint(-20,20))for _ in range(512)]
checks=[]
for address,name,model in [(0x0804a9f4,'add',lambda x,y:x+y),(0x0804b570,'subtract',lambda x,y:x-y),(0x0804b3c0,'reverse_subtract',lambda x,y:y-x),(0x0804b0a4,'multiply',lambda x,y:x*y),(0x0804ab6c,'divide',lambda x,y:x/y)]:
    failures=[]
    for x,y in pairs:
        actual=double_call(address,x,y);expected=model(x,y)
        if not same(actual,expected):failures.append(dict(x=x,y=y,actual=actual,expected=expected))
    assert not failures,(name,failures[:3]);checks.append(dict(address=hex(address),operation=name,cases=len(pairs),comparison='bit-exact finite IEEE binary64 reference',all_passed=True))
round_inputs=[x+.5 for x in range(-20,21)]+[x for x,y in pairs]
for x in round_inputs:
    actual=double_call(0x0804b30c,x);expected=float(round(x));expected=math.copysign(expected,x)if expected==0 else expected
    assert same(actual,expected),(x,actual,expected)
checks.append(dict(address='0x0804b30c',operation='nearest integer, ties to even, signed zero preserved',cases=len(round_inputs),all_passed=True))
for address in [0x0804b3d8,0x08049fcc]:
    for x,y in pairs:
        x=abs(x);actual=double_call(address,x);expected=math.sqrt(x);assert same(actual,expected),(hex(address),x,actual,expected)
    checks.append(dict(address=hex(address),operation='square root',cases=len(pairs),all_passed=True))
for x,y in pairs:
    fx=flt(bits(x));call(0x0804b744,bits(fx));actual=struct.unpack('<d',struct.pack('<II',u.reg_read(UC_ARM_REG_R0),u.reg_read(UC_ARM_REG_R1)))[0];assert same(actual,float(fx))
    args=struct.unpack('<2I',struct.pack('<d',x));actual=flt(call(0x0804a990,*args));assert bits(actual)==bits(x)
checks.append(dict(operation='F32/F64 conversion pair',cases=len(pairs)*2,all_passed=True))
result=dict(method='Original arithmetic/conversion instructions, no replacement arithmetic hooks. Deterministic normal finite inputs; NaN, subnormal, overflow and FPU rounding-mode variations not covered.',total_cases=sum(x['cases']for x in checks),checks=checks)
(root/'outputs/double-math-verification.json').write_text(json.dumps(result,indent=2));print(json.dumps(result,indent=2))
