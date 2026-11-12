# FlashForge Creator Pro 2 firmware research

Read-only reverse engineering of a 1 MiB STM32F407 flash backup. The current verified snapshot has **2,317 recovered functions and 477 curated semantic labels**. Firmware SHA-256: `45e8691c1866211de3b9f74b74d784a902e5d63e4f6eba0559a7528532376502`.

Start with [the complete report](checkpoints/017-combined-verified-snapshot/snapshot/Deconstruction-Report.md), [desktop-analysis review](checkpoints/015-user-deep-analysis/Deep-Analysis-Review.md), or [offline function explorer](checkpoints/017-combined-verified-snapshot/snapshot/Firmware-Explorer.html). Download the explorer to open it locally. [The combined package](checkpoints/017-combined-verified-snapshot/snapshot/CreatorPro2-Analysis-Package.zip) contains the annotated Ghidra archive and reports.

This is not recovered original source, replacement firmware, or a verified flashable upgrade. Two functions have manual reconstructions because automatic C generation fails. Three comparison leaf C renderings also have documented limitations. Tests execute original instructions in an emulator and explicitly stub device interfaces where recorded. No printer writes, settings changes or flashing were performed.

## History and preservation

The numbered checkpoints below are a **retrospective reconstruction of the analysis history from retained files**, committed at publication time. They are not fabricated earlier commits or exact historical filesystem snapshots. Topic folders contain the retained report/result revisions, including later corrections. The original raw byte-level report is preliminary and superseded by later findings. Raw chat transcripts, credentials, unrelated PC files and native runtime dependencies are excluded.

Each commit adds a new checkpoint; no earlier checkpoint is replaced or deleted. Future updates must follow the same pattern. The Ghidra archives embed original flash bytes; a separate raw `.bin` is not included. No license for third-party firmware is asserted here.

## Checkpoints

1. [Flash integrity, vectors and strings](checkpoints/001-byte-baseline/CHECKPOINT.md)
2. [Memory reconstruction and separate bootloader model](checkpoints/002-memory-and-boot/CHECKPOINT.md)
3. [Command routes and nonstandard behavior](checkpoints/003-command-map/CHECKPOINT.md)
4. [Motor pins, sensor tables and PID arithmetic](checkpoints/004-motion-pins-and-pid/CHECKPOINT.md)
5. [Heater limits and fault paths](checkpoints/005-thermal-controls/CHECKPOINT.md)
6. [Persistent settings and calibration boundaries](checkpoints/006-settings-and-calibration/CHECKPOINT.md)
7. [Recovered filesystem and peripheral references](checkpoints/007-filesystem-and-peripherals/CHECKPOINT.md)
8. [IDEX modes and corrected Pulley Type interpretation](checkpoints/008-idex-and-pulley-profiles/CHECKPOINT.md)
9. [Print pause/resume transitions and waits](checkpoints/009-pause-and-resume/CHECKPOINT.md)
10. [Expert calibration screen and UI resource catalog](checkpoints/010-expert-mode-and-ui/CHECKPOINT.md)
11. [Queued and immediate command routing](checkpoints/011-dispatch-instruction-checks/CHECKPOINT.md)
12. [Service marker, M615, time counters and G162](checkpoints/012-service-and-print-time/CHECKPOINT.md)
13. [Flag returns, binary64 operations and exception flow](checkpoints/013-numeric-runtime/CHECKPOINT.md)
14. [Block schema, trapezoids, queue and extrusion advance](checkpoints/014-motion-planner/CHECKPOINT.md)
15. [Review and merge of 97 newly recovered entries](checkpoints/015-user-deep-analysis/CHECKPOINT.md)
16. [Two C-generation failures reconstructed from assembly](checkpoints/016-manual-sd-reconstruction/CHECKPOINT.md)
17. [Combined Ghidra archive, complete results and reproduction sources](checkpoints/017-combined-verified-snapshot/CHECKPOINT.md)

## Reproduction

See [reproduction instructions](checkpoints/017-combined-verified-snapshot/reproduce/README.md). Original source dump bytes are needed to rerun instruction tests. Dependency installers and device connection are not run by these instructions automatically.
