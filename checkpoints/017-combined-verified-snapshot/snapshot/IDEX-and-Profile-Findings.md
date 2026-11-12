# Creator Pro 2: profile and IDEX selector findings

## Answer

The inspected selectors expose **existing mirror/duplicate printing and single/dual-extruder configuration**, not a discovered premium or performance unlock. No new capability was enabled on the printer. Firmware and external settings remain untouched.

Mirror and duplicate printing are documented Creator Pro 2 features. The [official FlashForge guide, PDF page 50 / printed page 48](https://en.fss.flashforge.com/10000/software/899daf8848060aa85e584cda439514c0.pdf#page=50) describes simultaneous two-extruder printing and selecting the modes in FlashPrint. FlashPrint 5 is already installed on this PC under `C:\Program Files\FlashForge\FlashPrint 5`. The installed default slicer configuration also contains a `[dittoPrint]` section with enable/mirror/extruderGap settings. That generic configuration is not a validated Creator Pro 2 override recipe.

## Findings by selector

| Selector | Recovered behavior | Practical meaning |
|---|---|---|
| Stored profile 0x11 | UI option 0, **Silver**, profile table index 0 | Pulley Type hardware-profile selection; no performance unlock found |
| Stored profile 0x12 | UI option 1, **Black**, profile table index 1 | Pulley Type hardware-profile selection; no performance unlock found |
| M611 S1 | Stores 1 at configuration +0x0E; one-extruder predicate true | Persistent one-extruder setup, not an extra feature |
| M611 S2 | Stores 2 at configuration +0x0E; one-extruder predicate false | Persistent two-extruder setup; not a complete live subsystem reinitialization |
| M118 first/last T | First and last matching T values differ → two-tool job flag | Job header / slicer metadata |
| M118 D1 or D2 | Stores requested mode; arms setup/compensation scanning | Part of a multi-stage IDEX job initialization |
| M111 T1 | Enables both X carriage flags, active mode 1 | Opposite logical X count changes: mirror behavior |
| M111 T2 | Enables both X carriage flags, active mode 2 | Same logical X count changes: duplicate behavior |

These command forms are **reverse-engineering references, not a ready-to-send printer setup sequence**. All emulator examples were executed in memory only. The complete job also includes homing, positioning, tool state, heating, calibration passes and file markers. Sending only the internal selector omits that context.

## Black/Silver Pulley Type profiles: evidence

- `UI_PulleyTypeDialog_Initialize` at **0x08025FE4** adds localized strings at offsets 0x122C (Silver) and 0x120E (Black). It selects option 1 for configuration profile byte 0x12.
- The dialog title is **Pulley Type**; earlier case-color interpretations are superseded.
- Dialog callback **0x08026222** maps confirmed option 1 to profile 0x12 and the other option to 0x11.
- Profile setter **0x08013AB4** saves that byte at storage +0x26, sets the profile index at 0x2000010C, reloads selected home/motion fields and calls planner initialization.
- The two initialized 20-byte rows at **0x200000C4** and the two 16-byte rows at **0x200000EC** are byte-identical in this dump. Offline execution confirms the eight inspected output fields match for profile 0x11 and 0x12.
- These are raw copied fields; their values are not presented as millimetres or a proposed tuning configuration. Runtime setup can transform other fields later. The variant byte may still affect other UI behavior, so “identical selected tables” does not prove every effect is identical.

## Single/dual extruder selection

`Config_SetExtruderCount` at **0x08013940** normalizes input 1 to stored 1; other tested inputs 2/3 store 2. Predicate **0x080135FC** checks configuration byte 0x2000012C != 2. It affects:

- one-versus-two-extruder temperature report formatting;
- startup disabling of the second heater controller in the one-extruder path;
- selected home-offset entries at **0x080138C0**;
- UI elements and motion-offset initialization.

The emulator records storage writes as intercepted objects; it never writes EEPROM. Changing the setting while running would not by itself replay every startup action, so this is not a recommended way to “unlock IDEX.”

## IDEX job-header path

`GCode_M118_ConfigureJobIDEX` at **0x08011266** searches X/Y/Z, the first T via `strchr`, the last T via `strrchr`, and D. It writes only RAM in the inspected handler.

- A single `T0` produces first/last T equal and clears the two-tool-job flag.
- `T0 T1` produces different values and sets the flag.
- D1/D2 set **0x20000011**, arm setup flag **0x2000001E** and reset setup phase **0x2000002A**.
- The Z calibration offset is checked against approximately ±0.2 to decide whether compensation is needed.
- The code expects coordinate extents in the header. Missing X/Y/Z leave incoming saved-register values in use; they are not guaranteed zero defaults.
- **Omitting D retains the previous requested mode.** Tested sequence D1 followed by a header without D leaves mode 1 and the setup flag set. D0 explicitly selects the ordinary branch. Other stored D values do not establish additional supported modes.

For explicit emulator geometry inputs 200/148/150, ordinary header checks accept X=100, Y=74, Z=150 and reject X=101. The D1/D2 branch accepts X=47.5 and rejects 47.6; it rejects Y=75 or Z=151. These are handler checks on centered extent inputs, **not recommendations to enlarge a print area**. The firmware's guard does not replace slicer placement and carriage-clearance logic. The official guide's operational instructions remain the supported path.

## Motion behavior confirmed offline

`GCode_M111_SetSynchronizedCarriages` at **0x080114B8** sets both carriage-enable flags and active synchronized mode at **0x20000013** from T. It also resynchronizes the logical X position from carriage 0's current counter.

Using one enabled axis-0 step, clear simulated endstops and known initial counters, the original instructions at **0x0804A3A8** produced:

| Active mode | Primary counter change | Secondary counter change | Interpretation |
|---|---:|---:|---|
| T1 / mode 1 | +1 | -1 | Mirror |
| T2 / mode 2 | +1 | +1 | Duplicate |

Both paths requested pulses on the primary step pin and PC2. PC3 direction requests differed. GPIO requests were intercepted and recorded; no pins were driven.

Coordinate parser **0x080106F4** also has distinct temporary compensation transforms. For X=20, tested flag combinations yield ordinary X=20; one compensation path X=86; mirror compensation X=-86; duplicate compensation X=-46. These follow constants ±66 and the compensation-pass selector **0x20000012**. Requested mode, compensation-pass mode and active synchronized mode are **three distinct state bytes**, not interchangeable switches.

## Why a complete slicer job matters

The queue service at **0x08012AAA**, calibration scanner **0x0801252A**, and special line reader **0x0801268C** implement a larger workflow:

- locate `;calPad A/B/SA/SB start/end` file markers;
- wait for heaters/motion and replay selected calibration segments;
- advance Z in compensation passes and reset file/queue state;
- select stored internal G-code sequences at **0x08016710**;
- convert file-side tool-change markers into sequences that include M111 T1/T2.

These paths explain why a raw mode command is not equivalent to a FlashPrint-generated mirror/duplicate job. Complete end-to-end job execution and physical carriage clearances were not emulated or tested here.

## What is usable now

Use the normal Creator Pro 2 mirror/duplicate workflow in FlashPrint for these capabilities; a firmware patch is unnecessary. The next useful offline validation would compare the header and calibration markers of a small FlashPrint-generated job against this recovered state flow. No printer connection, generated print submission, persistent printer setting change or firmware modification was performed.

The tests are in **idex-selector-verification.json**. They execute original selector, math, coordinate-parser and stepper instructions; numeric text conversion is a deterministic stub because the isolated emulator lacks the C runtime locale initialization. EEPROM, GPIO and planner-reinitialization interfaces are stubbed. They establish the tested internal behavior, not a hardware safety certification or a complete slicer/printer protocol implementation.
