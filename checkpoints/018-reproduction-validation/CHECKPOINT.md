# Portable reproduction validation

All 18 emulator scripts in checkpoint 017 passed against the original dump using the portable runner. The generated verification records the source hash and each script.

## Dependency version correction

The verified preparation environment used **Unicorn 2.1.4 and Capstone 5.0.7**. Checkpoint 017's requirements file incorrectly listed Capstone 5.0.6. That file is retained under the requested additive-history policy. Use `requirements-verified.txt` in this checkpoint for the verified pins. This correction changes no firmware, report finding or emulator result.

This checkpoint adds validation evidence and the corrected version record without modifying prior checkpoints.
