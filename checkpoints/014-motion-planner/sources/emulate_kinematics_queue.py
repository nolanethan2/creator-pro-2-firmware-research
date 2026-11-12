from pathlib import Path
exec((Path(__file__).parent/'emulate_numeric.py').read_text().split('tests=[]')[0])
import random
def f32(x):return flt(bits(x))
rng=random.Random(40716);checks=[]
for a,sign in [(0x08049a34,1),(0x08049b90,-1)]:
    count=0
    for _ in range(512):
        accel=f32(rng.uniform(-1000,1000));velocity=f32(rng.uniform(-100,100));distance=f32(rng.uniform(0,50))
        radicand=f32(float(f32(velocity*velocity))+sign*float(f32(accel*distance))*2.)
        expected=f32(math.sqrt(radicand))if radicand>0 else 0.
        actual=call(a,bits(accel),bits(velocity),bits(distance));assert actual==bits(expected),(hex(a),accel,velocity,distance,flt(actual),expected);count+=1
    checks.append(dict(address=hex(a),formula='sqrt(max(0, v*v '+('+'if sign>0 else'-')+' 2*a*d)) with original rounding order',cases=count,all_passed=True))
queue=[]
for head in range(16):
    for tail in range(16):
        u.mem_write(0x200005b1,bytes([head,tail]));u.mem_write(0x20009a9c,bytes(16*128))
        count=call(0x08049d00);empty=call(0x08029b72);ptr=call(0x08049d3c)
        assert count==(head-tail)&15 and bool(empty)==(head==tail)
        assert ptr==(0 if head==tail else 0x20009a9c+tail*128)
        if ptr:assert u.mem_read(ptr+0x76,1)[0]==1
        call(0x08049d18);next_tail=u.mem_read(0x200005b2,1)[0];assert next_tail==(tail if head==tail else(tail+1)&15)
        queue.append(dict(head=head,tail=tail,count=count,empty=bool(empty),current_block=hex(ptr),tail_after_discard=next_tail))
result=dict(method='Original kinematic and queue instructions, no subsystem stubs. Kinematic normal finite cases compared bit-exact with an independent operation-rounded model. All 256 valid head/tail pairs tested for count, empty, current-block/busy marking and discard.',kinematic_checks=checks,queue_cases=queue)
(root/'outputs/kinematics-queue-verification.json').write_text(json.dumps(result,indent=2));print('1024 finite kinematic cases and all 256 planner ring states passed')
