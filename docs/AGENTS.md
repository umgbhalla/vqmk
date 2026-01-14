## Agent Handoff Guide

### Repository context
- repo: `~/hub/vqmk` (a fork of `vial-qmk` with custom `umang` keyboard + HID display)
- Primary features: ST7735 display via LVGL, Vial/VIA support, HID/text terminal from `qmk-hid-host`, Bootmagic top-left trigger, `live` shell streaming through USB.
- Build command: `qmk compile -kb umang -km vial` (produces `.build/umang_vial.uf2` for flashing).  
- Flashing: copy UF2 onto `RPI-RP2` volume or use `picotool` after double-tap reset.

### Tasks in progress
- UI evolution for ST7735 console: display text, simple status bar, volume overlay.  
- `qmk-hid-host` shell provider sends HID packets; `TextLine/TextClear` data types used.  
- Host terminal removes `>` prefix, retains history, etc.

### Follow-up priorities
1. Reconcile LVGL scaling (PPI) to remove stray scrollbars. Terminal should use raw text, no background card.  
2. Ensure Vial JSON reflects correct `layouts.keymap`.  
3. Regenerate UI when new pictures/specs arrive.

### Environment notes
- Local development uses `qmk` CLI (via `/opt/homebrew/bin/qmk`, QMK arm toolchain).  
- Host program located at `~/hub/qmk-hid-host` (Cargo + tokio).  
- UF2 output lives at `~/hub/vqmk/.build/umang_vial.uf2`.
- Private repo `git@github.com:umgbhalla/priv-vial-hid.git` mirrors `keyboards/umang/`.

### Testing
- Run `cargo run` in `qmk-hid-host` to confirm host shell sends text.  
- After flashing, re-open shell to ensure display shows live text (use `/clear` to flush).  

### Troubleshooting
- Bootloader: hold top-left Bootmagic while resetting for flashing or use double-tap reset (RP2040).  
- Display not refreshing? Check `raw_hid_receive_kb` override in both keymaps.

### Communication
- The UI has become “plain console + status bar + volume overlay.” If adjustments needed, focus on LVGL primitives (labels/textarea).  
