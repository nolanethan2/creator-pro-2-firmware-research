# Two automatic C failures, manually reconstructed

The completed desktop run and the combined annotated program both fail automatic C generation for **0x08002EE8** and **0x08018A54**, reporting `Could not finish collapsing block structure`. This is a decompiler limitation, not evidence of unreadable or encrypted firmware. Their assembly and function boundaries are available.

The two routines implement the same SD-card bus-width selection sequence with different boot/application helper addresses and RAM globals. The manual reference is **Recovered-SD-BusWidth-Reference.c**. Eighteen original-instruction cases across the two copies validated these observed branches, with response/SCR/command interfaces intercepted:

- Response bit 0x02000000 returns 14.
- An SCR-reader failure is propagated.
- Selector exactly 1 requires SCR word 1 mask 0x00040000; other tested selectors use mask 0x00010000. Missing support returns 37.
- The routine sends command 55 with RCA shifted left 16, checks its response, then sends command 6 with argument 2 for the wide branch or 0 for the single branch.
- Command-response errors are propagated, and success returns zero.

This sequence agrees with the wide/single-bus helpers in [STMicroelectronics' official STM32F4 SD driver](https://github.com/STMicroelectronics/stm32f4xx-hal-driver/blob/master/Src/stm32f4xx_hal_sd.c). That comparison supports the role; it does not establish that this binary uses that HAL release or its error-number scheme. The reconstructed return codes come from this dump.

`sd-bus-width-verification.json` records complete intercepted command descriptors and results. No SDIO peripheral, card, printer or physical storage was accessed. The tests ran the firmware's original routines, not a compiled copy of the manual C reference.

The package preserves the two failure markers in Ghidra's raw export and lists them in `analysis-summary.json`; it does not substitute handwritten C while presenting it as decompiler output. Three F32 comparison leaf functions also have the separately documented C-rendering limitation. Those limitations remain visible even though the earlier four bad-instruction warnings have been resolved.
