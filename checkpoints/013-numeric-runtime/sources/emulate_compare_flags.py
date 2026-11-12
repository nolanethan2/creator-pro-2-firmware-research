from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
import random
rng=random.Random(40732);results=[]
pairs=[(x,y)for x in [-1e20,-2.,-1.,-0.,0.,1.,2.,1e20]for y in [-1e20,-2.,-1.,-0.,0.,1.,2.,1e20]]
pairs += [(rng.uniform(-1e8,1e8),rng.uniform(-1e8,1e8))for _ in range(1000)]
for address,reverse,precision in [(0x0804b7d8,False,32),(0x0804b8a0,False,32),(0x0804b982,True,32),(0x0804b02c,False,64),(0x0804ae1c,False,64),(0x0804b2a0,True,64)]:
    patterns={};samples=[]
    for x,y in pairs:
        if precision==32:x=flt(bits(x));y=flt(bits(y));args=[bits(x),bits(y)]
        else:args=list(struct.unpack('<4I',struct.pack('<dd',x,y)))
        call(address,*args);flags=(u.reg_read(UC_ARM_REG_CPSR)>>28)&15
        ng,zr,cy,ov=[(flags>>i)&1 for i in [3,2,1,0]]
        lhs,rhs=(y,x)if reverse else(x,y)
        assert zr==(lhs==rhs)and cy==(lhs>=rhs),(hex(address),x,y,hex(flags))
        relation='less'if lhs<rhs else('greater'if lhs>rhs else'equal');patterns.setdefault(relation,set()).add(f'{flags:04b}')
        if len(samples)<8:samples.append(dict(x=x,y=y,nzcv=f'{flags:04b}'))
    results.append(dict(address=hex(address),precision=precision,reversed_operands=reverse,cases=len(pairs),flag_patterns={k:sorted(v)for k,v in patterns.items()},samples=samples))
result=dict(method='Original six comparison helpers; 1064 finite pairs each, including both signed zeros and mixed signs. No replacement comparison or peripheral hooks. CY/ZR numeric relations asserted; all NZCV patterns recorded. NaN exceptional paths are outside this finite test.',total_cases=sum(x['cases']for x in results),helpers=results)
(root/'outputs/comparison-flags-verification.json').write_text(json.dumps(result,indent=2));print(json.dumps(result,indent=2))
