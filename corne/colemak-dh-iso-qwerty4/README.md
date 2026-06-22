# ⌨️ My Custom QMK ISO Keyboard Layout

This repository contains my personal QMK keyboard layout configurator JSON file and ready-to-flash firmware for a **Corne (crkbd rev1)** split keyboard (`LAYOUT_split_3x6_3`, 42 keys). It features a dual-base setup optimized for everyday typing in **Colemak-DH (ISO)**, with an emergency escape layer for **QWERTY**.

## 🛠️ Files Included
* `colemak-dh-iso-qwerty4.json` — The QMK Configurator keymap backup (import this to make changes)
* `crkbd_rev1_colemak-dh-iso-qwerty4.hex` — Pre-compiled, ready-to-flash firmware

---

## 🗺️ Layer Architecture

The layout uses `DF()` (Default Layer) to cleanly swap the keyboard foundation between Colemak-DH and QWERTY, with `MO()` (momentary hold) overlays for numbers, symbols, and RGB control.

```
Layer 0: Colemak Base
Layer 1: QWERTY Alternate Base
Layer 2: Numbers Layout
Layer 3: Symbols Layout
Layer 4: RGB Control & Bootloader Mode
```

### Layer 0: Colemak-DH (ISO) — Base
* **Type:** Permanent Base Floor (Default on boot)
* **Purpose:** Primary layout for typing, programming, and writing.
* **Thumbs (L → R):** `LGUI` · `MO(2)` · `Enter` ‖ `Space` · `MO(3)` · `RAlt`

```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ Tab │  Q  │  W  │  F  │  P  │  B  │   │  J  │  L  │  U  │  Y  │  ;  │ Bsp │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│Ctrl │  A  │  R  │  S  │  T  │  G  │   │  M  │  N  │  E  │  I  │  O  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│Shift│  Z  │  X  │  C  │  D  │  V  │   │  K  │  H  │  ,  │  .  │  /  │ Esc │
└─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
              │ GUI │MO(2)│ Ent │       │ Spc │MO(3)│ Alt │
              └─────┴─────┴─────┘       └─────┴─────┴─────┘
```

### Layer 1: QWERTY (ISO) — Alternate Base
* **Type:** Permanent Base Floor (alternate)
* **Purpose:** For fast, panic typing when muscle memory fails (or when someone else needs to type).
* **Activation:** From the Numbers or Symbols layer, tap the left-pinky bottom-row key — `DF(1)`.
* **Exit:** From the Numbers or Symbols layer, tap the left-index bottom-row key — `DF(0)` — to fall back to Colemak-DH.
* **Thumbs:** Same cluster as Layer 0 (`MO(2)` / `MO(3)`), so the Numbers and Symbols overlays open perfectly from QWERTY too.

### Layer 2: Numbers & Arrows
* **Type:** Temporary Overlay (held via `MO(2)` on the left thumb)
* **Purpose:** Number row, arrow cluster, and the jump pad for swapping base layouts.
* **Top Row:** `1 2 3 4 5` ‖ `6 7 8 9 0`
* **Right Home Row (Arrows):** `←` `↓` `↑` `→`
* **Left Bottom Row — Layer Jump Pad:**
  * **Pinky:** `DF(1)` ➡️ Switch base floor to **QWERTY**
  * **Ring:** `MO(4)` ➡️ Momentary jump to **RGB / Bootloader**
  * **Index:** `DF(0)` ➡️ Switch base floor back to **Colemak-DH**
* **Right Thumb:** `MO(4)` (also reaches the RGB layer momentarily)

### Layer 3: Symbols
* **Type:** Temporary Overlay (held via `MO(3)` on the right thumb)
* **Purpose:** Programming symbols, laid out so shifted-number symbols stay in their familiar columns.
* **Top Row:** `! @ # $ %` ‖ `^ & * ( )`
* **Right Home Row:** `- = [ ] \ \``
* **Right Bottom Row:** `_ + { } | ~`
* **Left Bottom Row:** also exposes `DF(1)` (pinky) and `DF(0)` (index) so you can swap base layouts from here too.
* **Left Thumb:** `MO(4)` (momentary jump to RGB)

### Layer 4: RGB & Firmware Adjust
* **Type:** Momentary Overlay — reached via `MO(4)` from Layer 2 (left-ring) or Layer 3 (left-thumb / right-thumb).
* **Trap Fix:** The activation key is `KC_TRNS`, so releasing your thumb instantly drops you back to your base layout — no more getting stuck here.
* **Purpose:** RGB matrix control and bootloader access. No typing happens here.
* **Top-Left (Tab position):** `QK_BOOT` ➡️ jump into bootloader for flashing
* **RGB Controls:**
  * `RM_TOGG` — toggle RGB on/off
  * `RM_HUEU` / `RM_HUED` — hue up/down
  * `RM_SATU` — saturation up
  * `RM_VALU` / `RM_VALD` — brightness up/down
  * `RM_NEXT` — cycle to next effect

---

## 🚀 How to Edit This Layout
1. Go to the [QMK Configurator](https://config.qmk.fm).
2. Click the **Import Keymap (JSON)** button (up arrow).
3. Upload `colemak-dh-iso-qwerty4.json` from this repository.
4. Make your tweaks, compile, and download the new `.hex`!

## ⚡ How to Flash
1. Put the Corne into bootloader mode — hold `MO(2)` (left thumb) to enter the Numbers layer, then hold `MO(4)` (left-ring bottom row) to reach Layer 4, then tap the top-left key (`QK_BOOT`).
2. Use [QMK Toolbox](https://github.com/qmk/qmk_toolbox) (or `dfu-programmer` / `avrdude`) to flash `crkbd_rev1_colemak-dh-iso-qwerty4.hex`.
3. Repeat for the other half of the split.
