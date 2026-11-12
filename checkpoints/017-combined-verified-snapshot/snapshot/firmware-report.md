# Creator Pro 2 firmware: read-only findings

Analyzed C:/Users/tech/Desktop/creator pro backup.bin, located after the requested /mnt/data path proved unavailable. No firmware bytes were modified, no device was accessed, and nothing was flashed. Source SHA-256 was checked again after analysis and remained unchanged.

## Identity and integrity

- Size: 1,048,576 bytes (0x100000).
- SHA-256: 45e8691c1866211de3b9f74b74d784a902e5d63e4f6eba0559a7528532376502
- Bootloader string at 0x08002438: Bootloader V1.3 20201210.
- Application version at 0x080150AC and 0x0801C608: V1.8 20210221.
- Product string at 0x08015064 and 0x0801C5EC: Flashforge Creator Pro 2.
- The separate Desktop file creatorp2_v1.8_20210221.bin is 872,156 bytes (0xD4EDC), SHA-256 c6f07092dce5797bae0ce9b650f63f3adf34fe9a0b8eb99ab8a64fddfbe70dfc. Its entire contents exactly match backup offsets 0x10000 through 0xE4EDB.
- This establishes identity with that local application copy, not independent vendor authenticity or a successful device read. No vendor signature/checksum algorithm was identified or validated. A second independently obtained hardware read would be the stronger acquisition check.
- Both 98-entry vector tables have plausible SRAM stack values and all 97 subsequent entries are either zero or odd pointers inside this flash image. Reserved exception entries are zero.
- Long FF runs: 0x0800C6F0–0x0800FFFF (14,608 bytes) and 0x080E4EDC–0x080FFFFF (110,884 bytes). These are consistent with unused flash, not themselves evidence of missing data.
- No evidence from these checks suggests truncation, a whole-image byte swap, or whole-image encryption. These checks cannot prove every bootloader byte is correct.

## Memory layout

| Address range | Interpretation |
|---|---|
| 0x08000000–0x08000187 | Bootloader vectors, 98 words |
| 0x08000188–0x0800C6EF | Bootloader startup/code/constants/resources; internal boundaries not fully resolved |
| 0x0800C6F0–0x0800FFFF | FF padding |
| 0x08010000–0x08010187 | Application vectors, 98 words |
| 0x08010188–approximately 0x0804BFFF | Substantial code and interspersed data/strings; approximate boundary |
| Approximately 0x0804C000–0x080E4EDB | Predominantly resources/tables/fonts/localized text; do not indiscriminately disassemble |
| 0x080E4EDC–0x080FFFFF | FF tail |

16 KiB windows of the main code area have entropy roughly 6.6–6.9 bits/byte. Later regions vary from low-entropy zero-heavy data to approximately 7.4 bits/byte. This is descriptive, not proof of compression or encryption.

For Ghidra, flash base is 0x08000000 and file offset = address - 0x08000000. Add uninitialized SRAM 0x20000000–0x2001FFFF and optionally CCM RAM 0x10000000–0x1000FFFF. These RAM contents are not in the dump. Peripheral regions should be volatile, non-executable; create named blocks only as needed. Flash at address zero is a boot alias, so do not import a second independent initialized copy there.

## Vector table and startup

| Item | Bootloader | Application |
|---|---|---|
| Vector base | 0x08000000 | 0x08010000 |
| Initial MSP | 0x20005F28 | 0x2001D988 |
| Stored reset pointer | 0x08000231 | 0x0802C311 |
| Reset instruction address | 0x08000230 | 0x0802C310 |
| NMI | 0x080026A0 | 0x08016158 |
| HardFault | 0x080026A2 | 0x0801615A |
| SysTick | 0x08000248 | 0x0801619A |
| Shared default external IRQ | 0x0800024A | 0x0802C32A |

Odd function pointers carry the Thumb bit; navigate to the corresponding even instruction address.

Boot reset bytes confirm:
    08000230  ldr r0, [pc, #0x24]   ; pool 08000258 -> 0800256D
    08000232  blx r0               ; calls 0800256C
    08000234  ldr r0, [pc, #0x24]   ; pool 0800025C -> 08000189
    08000236  bx r0                ; branches to 08000188

Application reset follows the same pattern:
    0802C310  ldr r0, [pc, #0x24]   ; pool 0802C338 -> 0802C42D
    0802C312  blx r0               ; calls 0802C42C
    0802C314  ldr r0, [pc, #0x24]   ; pool 0802C33C -> 08010189
    0802C316  bx r0                ; branches to 08010188

The called routines are strong SystemInit candidates; the subsequent destinations are runtime startup candidates, not yet confirmed main(). This layout resembles ARM/Keil startup but toolchain attribution remains an inference.

VTOR address 0xE000ED08 is loaded at 0x08010308 (pool 0x08010380) and 0x0802C470 (pool 0x0802C53C). Inspect the subsequent writes and operands to establish exactly when vectors are relocated.
Bootloader instructions at 0x08002078, 0x08002368 and 0x08002370 load application base 0x08010000 from pool 0x08002380. The latter pair are particularly useful handoff candidates; surrounding control flow must confirm the jump and stack setup.

Application external IRQ targets differing from the shared default:
| IRQ | Hardware vector name | Instruction address |
|---|---|---|
| 42 | OTG_FS_WKUP | 0x080161A2 |
| 44 | TIM8_UP_TIM13 | 0x08017120 |
| 45 | TIM8_TRG_COM_TIM14 | 0x0801713A |
| 49 | SDIO | 0x080161D0 |
| 59 | DMA2_Stream3 | 0x080161D8 |
| 67 | OTG_FS | 0x080161C6 |

TIM13/TIM14-related handlers are promising timing/control starting points, but naming a vector does not prove it drives steppers or heaters. USB, SDIO and DMA entries are stronger hardware-specific entry points. Very short handlers can delegate to shared drivers or be stubs.

## Strings and useful reference locations

Extracted 3,301 candidate runs of at least five characters using ASCII and ASCII-subset UTF-16LE scans, including incidental code/font false positives. This is not a complete multilingual Unicode extraction.

| String address | Content | Candidate instruction reference |
|---|---|---|
| 0x08002384 | ASCII 1:/sys/creatorp.bin | ADR at 0x08002080 and 0x0800234C |
| 0x08002438 | Bootloader V1.3 20201210 | ADR at 0x08002306 |
| 0x08015064 | Flashforge Creator Pro 2 | ADR at 0x08014D80 |
| 0x080150AC | V1.8 20210221 | ADR at 0x08014DA8 |
| 0x08014B7F | Endstop: X-max: %d Y-max: %d Z-min: %d | Find references in Ghidra |
| 0x08015B1C | UTF-16LE 1:/sys/creatorp.bin | ADR at 0x08015770 and 0x08015782 |
| 0x08024408 | UTF-16LE 1:/Creatorp.bin | ADR at 0x08024102 and 0x08024286 |
| 0x08024428 | UTF-16LE 1:/sys/Creatorp.bin | Find references in Ghidra |
| 0x0802959C | Creator Pro 2 Config | ADR at 0x080294E4 and 0x080294F0 |
| 0x080295B4 | Creator Pro 2 Port | Find references in Ghidra |
| 0x0804BB39 | HEAT_SHUTDOWN | Find references in Ghidra |
| 0x0809AAA6 | Extruder is not heating. Check the wiring. | Likely UI/resource text |
| 0x0809B14D | Temperature reads are failing. Please check wiring. | Likely UI/resource text |
| 0x0809B19D | Temperature limit reached. Please shutdown or restart. | Likely UI/resource text |
| 0x0809B1ED | Not heating properly. Please check wiring. | Likely UI/resource text |
| 0x0809B23D | Temperature dropping. Please check wiring. | Likely UI/resource text |
| 0x0809B28D | Temperature reads are out of range.Please check wiring. | Likely UI/resource text |

Other UTF-16LE paths include 1:log.txt at 0x08012C14, 0:Font18.bin at 0x0801BF9C, and Korean/Chinese font filenames at 0x080378C0–0x08037900. Their presence supports filesystem and multilingual display functionality. UI error text alone does not establish the implementation or effectiveness of a safety check.

Reference candidates were decoded from Thumb 16-bit ADR/LDR-literal patterns at halfword boundaries, not confirmed through a full control-flow disassembly. Validate them in Ghidra before naming their containing functions. Missing direct pointers do not imply unused strings: PC-relative ADR references are common here.

## Practical Ghidra sequence

1. Work in an analysis project with raw binary imported as ARM:LE:32:Cortex, little-endian, base 0x08000000. Check the end is 0x080FFFFF. Keep flash non-writable in the analysis map.
2. Define both vector tables as DWORD data/pointers, preserving stack words as values and reserved entries as zero. Create labels for boot and application vector bases.
3. At 0x08000230 and 0x0802C310 use Disassemble Thumb (F12 in the standard keymap), then create functions. Ensure TMode=1 for code. Avoid treating vector tables, literal pools and resources as instructions.
4. Follow the application call to 0x0802C42C, then runtime startup at 0x08010188. Trace initialized-data copy and zero-fill setup before identifying main. Add SRAM blocks so RAM references resolve. Any flash-to-RAM mappings should come from the startup tables, not guessed image offsets.
5. Run normal auto-analysis from these validated entry points and actual interrupt handlers. Avoid aggressive whole-image instruction discovery initially.
6. Inspect 0x08002368/0x08002370 for boot handoff and 0x0802C470 for vector relocation. Use provisional labels until control flow establishes behavior.
7. Inspect application timer handlers 0x08017120 and 0x0801713A, following their calls and register accesses. Look for TIM13 (0x40001C00), TIM14 (0x40002000), TIM8 (0x40010400) and GPIO register references to distinguish timing, motion and heater tasks. Shared IRQ names alone cannot make this distinction.
8. Define important strings, then show their references. For command/identity output begin at 0x08014D80/0x08014DA8; for configuration/USB descriptors begin around 0x080294E4. For update-file handling begin at 0x08015770 and 0x08024102.
9. For temperature logic, follow code referencing HEAT_SHUTDOWN, error-ID tables and thermistor/ADC data; localized UI strings may be reached through tables rather than direct calls. Confirm the ADC path, conversion, bounds checks and output-disable path before assigning heater-control names.
10. Save labels and notes in the Ghidra project. No patch/export/flash step is needed for this investigation.

This pass performed byte-level structure, string, statistics, exact comparison and selected Thumb instruction analysis. It did not run a full Ghidra decompilation or definitively identify main, a G-code parser, PID, thermistor conversion, or step generation.

## Primary references

- ST STM32F407 datasheet, memory map: https://www.st.com/resource/en/datasheet/stm32f407vg.pdf
- ST RM0090, interrupt vectors and peripheral map: https://www.st.com/resource/en/reference_manual/rm0090-stm32f407-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
- Ghidra official Thumb disassembly help: https://github.com/NationalSecurityAgency/ghidra/blob/master/Ghidra/Features/Base/src/main/help/help/topics/DisassemblerPlugin/Disassembly.htm
