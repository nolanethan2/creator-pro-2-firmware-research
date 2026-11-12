import os
from pathlib import Path
import struct, json
root=Path(__file__).resolve().parent
b=Path(os.environ.get('CREATORPRO2_DUMP',str(root/'input/creator-pro-backup.bin'))).read_bytes()
src,dst,length,decoder=struct.unpack_from('<4I',b,0xe4a24)
p=src-0x08000000
out=bytearray()
while len(out)<length:
    token=b[p];p+=1
    literal=token&7
    if not literal:literal=b[p];p+=1
    run=token>>4
    if not run:run=b[p];p+=1
    assert literal>=1
    out.extend(b[p:p+literal-1]);p+=literal-1
    if token&8:
        distance=b[p];p+=1
        assert distance>0 and distance<=len(out)
        for _ in range(run+2):out.append(out[-distance])
    else:out.extend(bytes(run))
assert len(out)==length
(root/'app-initialized-ram.bin').write_bytes(out)
print(json.dumps(dict(source=hex(src),destination=hex(dst),size=hex(length),decoder=hex(decoder),source_end=hex(p+0x08000000),output_size=len(out)),indent=2))
print('RAM pointer table:')
for off in range(0,len(out)-3,4):
    val=struct.unpack_from('<I',out,off)[0]
    if 0x08010000<=val<0x0804c000:print(hex(dst+off),hex(val))
