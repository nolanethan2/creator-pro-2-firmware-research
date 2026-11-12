# Reproducing the instruction checks

Use Python 3 with Unicorn and Capstone. The versions listed in requirements.txt describe the preparation environment. Install dependencies into your own virtual environment if needed. Ghidra Java scripts require a compatible Ghidra installation and the firmware imported as ARM little-endian Cortex/Thumb at 0x08000000, with the documented RAM model.

1. Place your original backup at `input/creator-pro-backup.bin`, or set `CREATORPRO2_DUMP` to its absolute path. The required SHA-256 is `45e8691c1866211de3b9f74b74d784a902e5d63e4f6eba0559a7528532376502`.
2. Install requirements in the selected Python environment, for example `python -m pip install -r requirements.txt`.
3. From this directory, run `python run_checks.py`.

The runner verifies the source hash, creates output folders, copies the current function map needed by dispatch tests, and runs the emulator checks. It does not connect to a device. External interfaces are intercepted as documented in each result. The copied initialized RAM is reconstructed from flash, not captured live memory.

The `work` directory also preserves annotation/export scripts and report builders for review. Some report builders describe specific earlier passes and are not a universal pipeline to recreate every historical report. Original per-topic source copies elsewhere in this repository retain their original paths; use this directory for portable test reruns. Ghidra project databases and native dependency binaries are excluded.
