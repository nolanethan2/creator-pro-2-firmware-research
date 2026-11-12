from pathlib import Path
import os,sys,hashlib,shutil,subprocess,json
root=Path(__file__).resolve().parent
dump=Path(os.environ.get('CREATORPRO2_DUMP',str(root/'input/creator-pro-backup.bin')))
assert hashlib.sha256(dump.read_bytes()).hexdigest()=='45e8691c1866211de3b9f74b74d784a902e5d63e4f6eba0559a7528532376502','Wrong source dump'
os.environ['CREATORPRO2_DUMP']=str(dump.resolve())
(root/'outputs').mkdir(exist_ok=True)
shutil.copy2(root.parent/'snapshot/function-map.json',root/'outputs/function-map.json')
scripts=['emulate_numeric.py','emulate_thermal.py','emulate_settings.py','emulate_idex.py','emulate_print_state.py','emulate_expert_ui.py','emulate_dispatch.py','emulate_immediate_routes.py','emulate_usage.py','emulate_g162.py','emulate_compare_flags.py','emulate_double_math.py','emulate_trapezoid.py','emulate_planner_init.py','emulate_motion_blocks.py','emulate_kinematics_queue.py','emulate_math_exceptions.py','emulate_sd_bus_width.py']
checks=[]
for name in scripts:
    p=subprocess.run([sys.executable,str(root/'work'/name)],cwd=root,text=True,capture_output=True)
    if p.returncode:print(p.stdout,p.stderr);raise SystemExit(f'FAILED: {name}')
    checks.append(name);print('PASS',name)
(root/'outputs/reproduction-verification.json').write_text(json.dumps(dict(scripts_passed=checks,source_sha256=hashlib.sha256(dump.read_bytes()).hexdigest()),indent=2))
