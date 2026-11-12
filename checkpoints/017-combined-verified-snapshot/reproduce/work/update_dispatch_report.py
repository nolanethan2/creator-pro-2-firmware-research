import os
from pathlib import Path
import csv
out=Path(__file__).resolve().parent.parent/'outputs'
p=out/'command-map.csv'
with p.open(newline='',encoding='utf-8-sig')as f:r=csv.DictReader(f);fields=r.fieldnames;rows=list(r)
for row in rows:
    if row['route']!='queued':continue
    if row['command']=='G91':row.update(observed_behavior='Consumes command without changing relative-axis mask 0x200006AC or change counter; tested starting masks 0/1/31',status='original-instruction dispatch emulation; parser/handler stubs')
    if row['command']=='G90':row.update(status='original-instruction dispatch emulation; clears mask and increments change counter')
    if row['command']=='G161/G162':row.update(observed_behavior='G161 consumes without action; G162 dispatches 0x080116A4',status='original-instruction dispatch emulation; handler intercepted')
    if row['command']=='M109':row.update(observed_behavior='Defers queue consumption while motion-ready predicate is false; when true consumes without a heater-wait handler',status='static branch plus original-instruction false-predicate emulation')
    if row['command']in['M146','M201/M204/M205/M206/M221','M301/M304/M612/M999']:row['status']='original-instruction dispatch emulation; consume-only path confirmed'
with p.open('w',newline='',encoding='utf-8')as f:w=csv.DictWriter(f,fields);w.writeheader();w.writerows(rows)
p=out/'Deconstruction-Report.md';s=p.read_text(encoding='utf-8');s+='''

## 13. Queued-command instruction checks

Thirty additional original-instruction checks resolve several earlier dispatch uncertainties. G91 consumes its queue entry and leaves the relative-axis mask at 0x200006AC unchanged for starting masks 0, 1 and 31. G90 clears that mask and increments the change counter. G161 follows a consume-only path; G162 calls 0x080116A4. M146, M201, M204, M205, M206, M221, M301, M304, M612 and M999 all reach the intercepted common response helper with no other dispatched action in these tests. This is evidence about this dump and route, not universal G-code behavior.

G28, G93, M18, M108, M109, M110, M111 and M906 retain the queue entry when the motion-ready predicate returns false. External handlers and decimal parsing were intercepted; field search and finite numeric conversion used original instructions. See `dispatch-emulation-verification.json` and the updated command map. Nothing was sent to a printer.

Final UI-pass archive reimport confirms 2,220 functions, 463 nonautomatic names, 431 curated labels and the original 1 MiB flash SHA-256. Extra startup/vector names explain the difference between nonautomatic and curated counts. The offline explorer was checked against the new counts and typed Expert Mode callback.
''';p.write_text(s,encoding='utf-8')
p=out/'README.md';s=p.read_text(encoding='utf-8').replace('| package-manifest.json |','| dispatch-emulation-verification.json | 30 queued-command routing and state checks with intercepted handlers |\n| package-manifest.json |');p.write_text(s,encoding='utf-8')
print('Command map and report updated')
