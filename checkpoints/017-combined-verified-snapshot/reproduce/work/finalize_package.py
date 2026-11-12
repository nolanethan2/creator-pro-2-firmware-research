import os
from pathlib import Path
import hashlib,json,zipfile,re,csv
root=Path(__file__).resolve().parent.parent;out=root/'outputs'
expected='45e8691c1866211de3b9f74b74d784a902e5d63e4f6eba0559a7528532376502'
assert hashlib.sha256(Path(os.environ.get('CREATORPRO2_DUMP',str(root/'input/creator-pro-backup.bin'))).read_bytes()).hexdigest()==expected
review=json.loads((out/'deep-analysis-review.json').read_text());expected_functions=review['gui_function_count']
assert review['additional_entries']==review['imported_entries']==97 and review['missing_previous_entries']==0
assert review['flash_sha256']==expected
v=json.loads((out/'archive-verification.json').read_text());assert v['flash_sha256']==expected and v['function_count']==expected_functions
labels=list(csv.DictReader((out/'function-labels.tsv').open(encoding='utf-8'),delimiter='\t'))
curated=len(labels)
funs=json.loads((out/'function-map.json').read_text());assert len(funs)==expected_functions and sum(f['confidence']!='unreviewed'for f in funs)==curated
assert len(json.loads((out/'expert-mode-verification.json').read_text())['checks'])==9
assert len(json.loads((out/'dispatch-emulation-verification.json').read_text())['checks'])==30
assert len(json.loads((out/'usage-service-verification.json').read_text())['checks'])==14
assert json.loads((out/'immediate-route-verification.json').read_text())['tested_cases']==2010
assert len(json.loads((out/'g162-verification.json').read_text())['checks'])==6
assert json.loads((out/'comparison-flags-verification.json').read_text())['total_cases']==6384
assert json.loads((out/'double-math-verification.json').read_text())['total_cases']==5161
exception=json.loads((out/'math-exception-verification.json').read_text());assert len(exception['checks'])==12 and all(c['matches_ieee_classification'] for c in exception['checks'])
trapezoid=json.loads((out/'trapezoid-verification.json').read_text());assert trapezoid['profile_checks']==134 and trapezoid['extra_checks']==7
kinematics=json.loads((out/'kinematics-queue-verification.json').read_text());assert len(kinematics['queue_cases'])==256 and sum(c['cases'] for c in kinematics['kinematic_checks'])==1024
assert len(json.loads((out/'planner-init-verification.json').read_text())['checks'])==4
assert len(json.loads((out/'motion-block-verification.json').read_text())['checks'])==10
assert len(json.loads((out/'sd-bus-width-verification.json').read_text())['checks'])==18
assert json.loads((out/'planner-archive-verification.json').read_text())['checks_passed']
assert not json.loads((out/'analysis-summary.json').read_text())['decompiler_bad_instruction_warnings']
assert json.loads((out/'analysis-summary.json').read_text())['decompiler_error_functions']==['08002ee8','08018a54']
assert not any('Decompiler process died'in f['code'] for f in funs)
assert len(list(csv.DictReader((out/'ui-page-callbacks.csv').open())))==19
assert len(list(csv.DictReader((out/'ui-language-catalog.csv').open(encoding='utf-8-sig'))))==1803
assert json.loads((out/'numeric-emulation-verification.json').read_text())['pid_sequence_check']['all_passed']
assert len(json.loads((out/'thermal-emulation-verification.json').read_text())['checks'])==14
assert len(json.loads((out/'settings-emulation-verification.json').read_text())['checks'])==7
idex=json.loads((out/'idex-selector-verification.json').read_text())
assert sum(len(idex[k])for k in ['m118_cases','profiles','machine_selector_cases','coordinate_transform_cases','carriage_step_cases','extent_boundary_cases','omitted_D_case'])==24
assert [c['secondary_counter_delta']for c in idex['carriage_step_cases']]==[-1,1]
print_state=json.loads((out/'print-state-verification.json').read_text())
assert len(print_state['transitions'])==13 and len(print_state['hold_cases'])==7
config=list(csv.DictReader((out/'configuration-map.csv').open()))
assert len(config)==15 and all(None not in row for row in config)
manifest={}
for p in sorted(out.rglob('*')):
    if p.is_file() and p.name not in ['package-manifest.json','CreatorPro2-Analysis-Package.zip']:
        data=p.read_bytes();manifest[p.relative_to(out).as_posix()]={'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()}
(out/'package-manifest.json').write_text(json.dumps(manifest,indent=2))
with zipfile.ZipFile(out/'CreatorPro2-Analysis-Package.zip','w',compression=zipfile.ZIP_DEFLATED,compresslevel=6) as z:
    for p in sorted(out.rglob('*')):
        if p.is_file()and p.name!='CreatorPro2-Analysis-Package.zip':z.write(p,p.relative_to(out).as_posix())
with zipfile.ZipFile(out/'CreatorPro2-Analysis-Package.zip')as z:
    assert z.testzip()is None
    for name,meta in manifest.items():assert hashlib.sha256(z.read(name)).hexdigest()==meta['sha256']
print(json.dumps(dict(package_files=len(manifest)+1,zip_bytes=(out/'CreatorPro2-Analysis-Package.zip').stat().st_size,flash_sha256=expected,curated_labels=curated,tests_passed=True),indent=2))
