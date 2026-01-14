# VQMK Agent Guide

## Quick background
- `~/hub/vqmk` is a fork of `vial-qmk` customized for the `umang` keyboard with an ST7735 display driving a live host shell.  
- Key components: `keyboards/umang/keymaps/mappa` + `/vial` (custom UI), `docs/` and `AGENTS/` for process docs, private repo `git@github.com:umgbhalla/priv-vial-hid.git`, host tool `~/hub/qmk-hid-host`.

## Immediate actions for new agent
1. Inspect `docs/AGENTS.md` and `docs/HANDOFF.md` for build/flash guidelines, responsibilities, and known pain points.  
2. Understand HID data flow: host sends `TextLine`/`TextClear`, firmware uses `raw_hid_receive_kb` to route to `display_process_raw_hid_data`.  
3. Rebuild via `qmk compile -kb umang -km vial`, copy UF2 to `/Volumes/RPI-RP2/` (Bootmagic top-left or double-tap reset the RP2040).  
4. Use `cargo run` inside `~/hub/qmk-hid-host` for host shell tests; `--lines` controls the number of visible rows.

## Repository hygiene
- Keep UI files in sync between `keymaps/mappa` and `keymaps/vial`.  
- After firmware tweaks, copy `keyboards/umang/` into `git@github.com:umgbhalla/priv-vial-hid.git` and push (this is the ongoing release location).  
- Document any new HID message types in both firmware and `qmk-hid-host/src/data_type.rs`.

## Communication hints
- Provide updated status via `docs/AGENTS.md` if you add new tools, dependencies, or instructions.  
- Call out any unresolved display artifacts, scaling issues, or new requirements before leaving the turn so the next agent picks up cleanly.
