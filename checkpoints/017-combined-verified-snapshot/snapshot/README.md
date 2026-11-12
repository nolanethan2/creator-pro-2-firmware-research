# Creator Pro 2 firmware analysis package

Start with **Deconstruction-Report.md** for the findings and limitations. **Firmware-Explorer.html** is a self-contained, offline searchable function browser. It makes no network requests and needs no installation.

The annotated program has also been imported into your existing **CREATOR PRO 2** Ghidra project as **CreatorPro2-Analyzed** (first pass); the deeper pass is imported separately as **CreatorPro2-DeepAnalysis**. Your earlier `creator pro backup.bin` analysis entry is retained separately. The GZF in this package includes the newer IDEX, print-state, UI, motion/runtime annotations and desktop-analysis additions; GUI copies imported earlier may not contain those latest labels.

To import on another compatible Ghidra installation, choose **File â†’ Import File**, select **CreatorPro2-Analyzed.gzf**, retain the GZF format and open the imported program. It already contains analysis results; no fresh whole-image analysis is required. Use **G** to navigate to `App_Main`, `GCode_DispatchQueuedCommand`, `Motion_StepperISR` or `Heater_UpdateControlAndChecks`.

**CreatorPro2-Bootloader-Analyzed.gzf** models bootloader RAM separately and is the preferred view for bootloader-specific analysis. It contains only the first 64 KiB of actual flash bytes; its application address range is uninitialized. It does not represent a complete firmware dump.

The whole-image program includes modeled RAM/peripheral blocks. Its maximum address is therefore beyond 0x080FFFFF, and its total mapped byte count exceeds 1 MiB. The actual captured flash remains exactly 1 MiB and was verified unchanged after archive reimport. Reconstructed RAM is startup data decoded from flash, not live printer memory.

## Files

| File / folder | Purpose |
|---|---|
| Deconstruction-Report.md | Detailed subsystem findings, evidence, caveats and remaining work |
| Firmware-Explorer.html | Search all 2,317 recovered functions and follow call links |
| CreatorPro2-Analyzed.gzf | Whole-image Ghidra program with application-state reconstruction |
| CreatorPro2-Bootloader-Analyzed.gzf | Bootloader-specific Ghidra program |
| function-labels.tsv | 477 manually assigned semantic labels with confidence and evidence |
| command-map.csv | Queued/immediate command routes and observed behavior |
| motor-pin-table.csv | Restored motor pin table; roles marked where inferred |
| sensor-tables.csv | Packed bed/extruder conversion table values |
| bounded-switch-targets.csv | Exact target addresses for six bounded TBB switches |
| call-graph.csv | 6,228 recovered direct/computed call edges; not a complete dynamic graph |
| string-references.csv | Recovered function-to-string references |
| hardware-references.csv | Direct peripheral/system register references |
| function-map.json | Function metadata, references and annotated pseudocode |
| ghidra/ | Complete whole-image disassembly, pseudocode and indexes |
| bootloader/ | Separate bootloader disassembly, pseudocode and indexes |
| archive-verification.json | Flash hash and function count after final GZF reimport |
| bootloader-verification.json | Separate bootloader program hash and count |
| explorer-verification.json | Offline browser logic smoke checks |
| analysis-summary.json | Summary counts |
| numeric-emulation-verification.json | Arithmetic, table boundaries and 128-sample PID comparison |
| thermal-emulation-verification.json | Offline heater limits and fault-path checks, with environment stubs |
| settings-emulation-verification.json | Configuration startup/default and offset-boundary checks with external-read stubs |
| configuration-map.csv | Partial 15-offset storage schema with evidence limits |
| IDEX-and-Profile-Findings.md | Tested selector behavior and practical interpretation |
| idex-selector-verification.json | Offline profile, header, coordinate and carriage-step cases |
| Print-Pause-Resume-Findings.md | Recovered pause/resume sequence and remaining limits |
| print-state-verification.json | 13 original-instruction transition tests and seven wait cases with subsystem stubs |
| Recovered-PID-Reference.c | Readable finite-input controller model; not replacement firmware |
| coverage-inventory.json | Regional inventory without an invented completion percentage |
| remaining-functions.csv | Outstanding functions ordered by recovered body size |
| ui-language-catalog.csv | 1,803 UTF-8 runs from ten localized resource blocks |
| ui-page-callbacks.csv | 19 periodic page-callback assignments and dialog registrations |
| Expert-Mode-and-UI-Findings.md | Calibration behavior, UI addresses and correction of Pulley Type interpretation |
| expert-mode-verification.json | Nine offline original-instruction UI checks |
| ui-screen-catalog.json and ui-widgets.csv | Static screen creation sites and widget records, with branch duplicates |
| ui-resource-references.csv | Functions referencing English UI resources |
| dispatch-emulation-verification.json | 30 queued-command routing and state checks with intercepted handlers |
| Service-and-Command-Findings.md | Service marker, M615 counter reset, timing and routing evidence |
| usage-service-verification.json | 14 offline usage, timer and service-file checks |
| immediate-route-verification.json | 2,010 original-dispatch routing cases with action stubs |
| g162-verification.json | Six internal G162 handler checks with planner stub |
| Motion-Planner-and-Runtime-Findings.md | Planner fields, acceleration, advance compensation and numeric-model limitations |
| planner-block-layout.csv | Recovered 128-byte motion-block schema |
| comparison-flags-verification.json and double-math-verification.json | Original numeric-helper checks |
| math-exception-verification.json | 12 exceptional arithmetic/return cases |
| trapezoid-verification.json and kinematics-queue-verification.json | Profile reference checks and all 256 ring states |
| planner-init-verification.json and motion-block-verification.json | Initialization and isolated block-construction cases |
| Deep-Analysis-Review.md and deep-analysis-review.json | Completed user-run comparison and integration evidence |
| deep-analysis-function-merge.tsv | 97 imported entries, including reviewed shared-tail split |
| planner-archive-verification.json | Reimported planner types, flag signatures and flow overrides |
| Decompiler-Limits-and-SD-Reconstruction.md | Two automatic C failures and separately tested manual reconstruction |
| Recovered-SD-BusWidth-Reference.c | Readable reference for boot/application SD bus-width routines; not firmware |
| sd-bus-width-verification.json | 18 original-instruction SD cases with all device interfaces intercepted |
| package-manifest.json | Deliverable SHA-256 hashes |
| firmware-report.md and firmware-*.json | Earlier byte-level baseline; the deconstruction report supersedes its preliminary interpretations |

All decompiled code is reconstructed pseudocode. Automatic function recovery, names and types can be incomplete or incorrect. Confidence labels describe a function's observed role, not proof of every branch or safety property. This package is an analysis artifact, not buildable source or a flashable firmware modification.
