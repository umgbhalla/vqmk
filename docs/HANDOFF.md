# VQMK Handoff Notes

## Intended audience
Next Codex agent or maintainer coming into `~/hub/vqmk`, focused on the `umang` keyboard + display shell + qmk-hid-host host toolchain.

## Setup overview
- Dependencies: Homebrew `qmk` CLI, arm-none-eabi toolchain (14.2), Python3 for LVGL build scripts.  
- Flash path: `qmk compile -kb umang -km vial` → `.build/umang_vial.uf2` → copy to `/Volumes/RPI-RP2/` with board in UF2 boot mode (double tap reset or Bootmagic top-left).  
- Host: `~/hub/qmk-hid-host` (`cargo run`) communicates with keyboard via Raw HID (VID=FEED PID=0899 usage_page=0xff60 usage=0x0061). Uses shell provider, other providers disabled unless flags passed.

## Current concerns
1. LVGL UI overshoots display bounds, introduces scrollbars; current layout is minimal status bar + textarea, but there may still be unwanted decorations or scaling needing adjustment.  
2. Display receives `TextLine`/`TextClear` HID data, and `raw_hid_receive_kb` forwards to `display_process_raw_hid_data`. Keep that path intact if modifying UI or HID protocol.
3. Vial config includes `VIAL_INSECURE` and Bootmagic top-left. Avoid reintroducing old Bootmagic combos unless necessary.

## Workflow reminders
- Copy `.build/umang_vial.uf2` to `/Volumes/RPI-RP2/` (flash).  
- Run `cargo run` inside `qmk-hid-host` to test host shell, `--lines` flag adjusts visible rows.  
- For firmware changes, sync to private repo `git@github.com:umgbhalla/priv-vial-hid.git` (tracks `keyboards/umang/` tree); commits there keep history needed for the host to pull.

## Testing expectations
- Once flashed, host shell should show new lines immediately via LVGL textarea; `/clear` empties screen.  
- Volume HID data should trigger temporary overlay bar on status area (scroll to the left) and vanish after a timer.  
- Status marquee text is currently static (`connected • battery 92%`); update it if new telemetry arrives via HID.

## TODOs for successor
- Nail down LVGL scaling: PPI, scrollbars, and the thin status bar margin need verification on actual hardware.  
- Remove any remaining `lv_textarea` chrome by ensuring `lv_obj_set_style_border_width(..., 0)` and `LV_OPA_TRANSP`.  
- Add actual data sources for the status marquee (e.g., host sending battery, wifi, or custom icons).  
