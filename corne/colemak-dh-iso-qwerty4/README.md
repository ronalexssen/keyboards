# ⌨️ My Custom QMK ISO Keyboard Layout

This repository contains my personal QMK keyboard layout configurator JSON file and ready-to-flash firmware for a **Corne (crkbd rev1)** split keyboard (`LAYOUT_split_3x6_3`, 42 keys). It features a dual-base setup optimized for everyday typing in **Colemak-DH (ISO)**, with an emergency escape layer for **QWERTY**.

## 🛠️ Files Included
* `colemak-dh-iso-qwerty4.json` — The QMK Configurator keymap backup (import this to make changes)
* `crkbd_rev1_colemak-dh-iso-qwerty4.hex` — Pre-compiled, ready-to-flash firmware

---

## 🗺️ Layer Architecture

The layout relies on the `DF()` (Default Layer) keycode to cleanly swap the keyboard foundation between Colemak-DH and QWERTY. Temporary overlays use `MO()` (momentary hold) and `TO()` (jump-to). Layer 3 is reached via the classic **tri-layer** pattern — holding both thumb layer keys at once.

### Layer 0: Colemak-DH (ISO) — Base
* **Type:** Permanent Base Floor (Default on boot)
* **Purpose:** Primary layout for typing, programming, and writing.
* **Thumbs (L → R):** `LGUI` · `MO(1)` · `Enter` ‖ `Space` · `MO(2)` · `RAlt`

```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ Tab │  Q  │  W  │  F  │  P  │  B  │   │  J  │  L  │  U  │  Y  │  ;  │ Bsp │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│Ctrl │  A  │  R  │  S  │  T  │  G  │   │  M  │  N  │  E  │  I  │  O  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│Shift│  Z  │  X  │  C  │  D  │  V  │   │  K  │  H  │  ,  │  .  │  /  │ Esc │
└─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
              │ GUI │MO(1)│ Ent │       │ Spc │MO(2)│ Alt │
              └─────┴─────┴─────┘       └─────┴─────┴─────┘
```

### Layer 1: Numbers, Arrows & Layer Jump Pad
* **Type:** Temporary Overlay (held via `MO(1)` on the left thumb)
* **Purpose:** Number row, arrow cluster, and the command center for jumping between layouts.
* **Top Row:** `1 2 3 4 5` ‖ `6 7 8 9 0`
* **Right Home Row (Arrows):** `←` `↓` `↑` `→`
* **Left Bottom Row — Layer Jump Pad:**
  * **Pinky:** `DF(4)` ➡️ Switch base floor to **QWERTY**
  * **Ring:** `TO(3)` ➡️ Jump to **RGB / Adjust**
  * **Middle:** `TO(1)` ➡️ Stay on **Numbers** (lock it on)
  * **Index:** `DF(0)` ➡️ Switch base floor back to **Colemak-DH**
* **Right Thumb:** `MO(3)` (combine with the held `MO(1)` to reach Layer 3)

### Layer 2: Symbols
* **Type:** Temporary Overlay (held via `MO(2)` on the right thumb)
* **Purpose:** Programming symbols, laid out so shifted-number symbols stay in their familiar columns.
* **Top Row:** `! @ # $ %` ‖ `^ & * ( )`
* **Right Home Row:** `- = [ ] \ \``
* **Right Bottom Row:** `_ + { } | ~`
* **Left Bottom Row:** also exposes `DF(4)` (pinky) and `DF(0)` (index) so you can swap base layouts from here too.
* **Left Thumb:** `MO(3)` (combine with the held `MO(2)` to reach Layer 3)

### Layer 3: RGB & Firmware Adjust
* **Type:** Temporary Overlay — reached by holding **both** `MO(1)` + `MO(2)` (tri-layer), or via `TO(3)` from Layer 1.
* **Purpose:** RGB matrix control and bootloader access. No typing happens here.
* **Top-Left (Tab position):** `QK_BOOT` ➡️ jump into bootloader for flashing
* **RGB Controls:**
  * `RM_TOGG` — toggle RGB on/off
  * `RM_HUEU` / `RM_HUED` — hue up/down
  * `RM_SATU` — saturation up
  * `RM_VALU` / `RM_VALD` — brightness up/down
  * `RM_NEXT` — cycle to next effect

### Layer 4: QWERTY (ISO) — Emergency Base
* **Type:** Permanent Base Floor (alternate)
* **Purpose:** For fast, panic typing when muscle memory fails (or when someone else needs to type).
* **Activation:** Hold `MO(1)`, then tap pinky on the left bottom row — `DF(4)`.
* **Exit:** Hold `MO(1)` again, then tap index on the left bottom row — `DF(0)` — to fall back to Colemak-DH.
* Same thumb cluster as Layer 0 (`MO(1)` / `MO(2)`), so all overlays remain accessible.

---

## 🚀 How to Edit This Layout
1. Go to the [QMK Configurator](https://config.qmk.fm).
2. Click the **Import Keymap (JSON)** button (up arrow).
3. Upload `colemak-dh-iso-qwerty4.json` from this repository.
4. Make your tweaks, compile, and download the new `.hex`!

## ⚡ How to Flash
1. Put the Corne into bootloader mode — easiest way is **Layer 1 → top-left key (`QK_BOOT`)** by holding `MO(1)` and tapping where `Tab` lives on the base layer... wait, that's actually on **Layer 3**: hold both thumb layer keys, then tap the top-left key.
2. Use [QMK Toolbox](https://github.com/qmk/qmk_toolbox) (or `dfu-programmer` / `avrdude`) to flash `crkbd_rev1_colemak-dh-iso-qwerty4.hex`.
3. Repeat for the other half of the split.
