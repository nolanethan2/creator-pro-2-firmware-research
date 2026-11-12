# Expert Mode and recovered UI

## What is available

The firmware contains an ordinary Settings → Expert Mode → Next path to **manual X/Y calibration fine tuning**. It is not evidence of a speed or temperature unlock. No printer setting was changed during this analysis.

The fine-calibration buttons stage changes of **0.05** in X or Y. **OK adds those deltas to the existing calibration offsets and requests persistent writes**; Cancel discards them. The unit is inferred to follow the printer's calibration units, rather than independently measured against hardware. Use this screen only as part of the printer's calibration procedure; this report does not establish a correction that your printer needs.

## Addresses and state

| Address | Recovered role |
|---|---|
| 0x08023E2E | Settings notification callback; button 0x179 opens Expert Mode |
| 0x08028A7E | Creates Expert Mode introduction using table 0x080AD84C |
| 0x0802893C | Intro callback; Next creates fine-calibration dialog, Back returns to Settings |
| 0x080AD8D8 | Fine-calibration widget table, 12 records |
| 0x08028432 | Fine-calibration initialization |
| 0x08028688 | Fine-calibration button callback |
| 0x200004B0 / 0x200004B4 | Staged X / Y deltas |
| 0x20001028 / 0x2000102C | Existing X / Y calibration offsets |
| 0x08013C7A / 0x08013C96 | X / Y offset persistence paths, storage offsets 0 / 4 |

Button IDs: X− 0x172, X+ 0x174, Y− 0x175, Y+ 0x177, OK 0x178, Cancel 0x179. Notifications 1 and 2 in the same callback close the dialog without clearing staged deltas; normal touchscreen reachability of those IDs has not been established. This is a branch-level observation, not a confirmed user-facing defect.

Nine original-instruction emulator checks passed: four increments, commit, cancel, two generic-close cases, and Settings entry. GUI, formatting, delay and persistent-write interfaces were intercepted. These tests validate the inspected callbacks in a modeled environment; they do not reproduce an entire physical touchscreen session.

## Screen inventory and correction

Static creation sites expose **33 distinct widget tables** across 37 matched creation branches. `ui-widgets.csv` contains 318 rows including tables repeated by alternative creation branches; it is not a count of unique physical controls. `ui-screen-catalog.json` preserves the creation-site/table/callback relationships, and `ui-resource-references.csv` links 51 functions to English resource text. Dynamic dialogs and calls without literal tables can be absent.

The Silver/Black selection belongs to a screen titled **Pulley Type**. Earlier wording that called it a case-color or case-variant selector was too specific and is corrected here. Stored values 0x11/0x12 still select table indices 0/1; the two inspected initialized motion-table rows are identical in this dump. That observation does not establish that every runtime consequence is identical.

Recovered message fields and 28-byte widget creation records are now defined in the Ghidra archive. Forty-five UI message functions have explicit callback-pointer parameters, and 83 additional functions have semantic labels, bringing the total to **431 of 2,220 recovered functions**. This is an inventory, not a percentage of complete understanding.

## Practical Ghidra continuation

Import the updated `CreatorPro2-Analyzed.gzf` and navigate to 0x08028688. Follow the typed message fields, compare button IDs against table 0x080AD8D8, then follow the two persistence calls. For wider UI work, start at the Settings and Tools callbacks and use the screen catalog to resolve indirect callback edges. Continue separating GUI-library behavior from printer-specific behavior; naming every library helper would not by itself establish all printer behavior.

The callback/widget layout is consistent with SEGGER emWin conventions; exact library version and source identity remain unproven. Reference: [SEGGER emWin manual](https://doc.segger.com/UM03001_emWin.html).
