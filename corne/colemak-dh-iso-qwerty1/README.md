# ⌨️ Corne Custom QMK Layout — Colemak-DH ISO + QWERTY (v1)

This directory contains a hand-written QMK keymap for a **Corne (crkbd rev1)** split keyboard (`LAYOUT_split_3x6_3`, 42 keys). It's a dual-base setup optimized for everyday typing in **Colemak-DH (ISO)** with a **QWERTY** alternate — reachable either momentarily (hold) or persistently (toggle via Layer 4).

The thumb cluster keeps the physical labels you're used to: **CMD on the outer thumbs, Enter and Space on the inner thumbs, RAlt on the right outer**. The two middle thumbs carry hold-for-layer keys, and the inner thumbs are dual-purpose Layer-Tap keys.

## 🛠️ Files Included
* `keymap.c` — Hand-written C source for `qmk compile`

To build:
```sh
qmk compile -kb crkbd/rev1 -km colemak-dh-iso-qwerty1
```
(after copying this directory into your QMK tree at `qmk_firmware/keyboards/crkbd/keymaps/colemak-dh-iso-qwerty1/`)

---

## 🗺️ Layer Architecture

```
Layer 0: Colemak-DH Base       (default on boot,        BLUE)
Layer 1: QWERTY Alternate Base (held or DF(1) swap,     RED)
Layer 2: Numbers + Arrows      (held via R-inner thumb, GREEN)
Layer 3: Symbols               (held via L-middle thumb, HOT PINK)
Layer 4: RGB Control + Boot    (held via R-middle thumb, YELLOW)
```

All four utility layers are **hold-only momentary** — release the thumb, you fall back to whichever base was active. No trap layers.

### 👍 Thumb Cluster (identical on Layer 0 and Layer 1)

The Corne 3x6 has **3 thumb keys per side**. This build uses all six:

| Position  | Keycode               | Tap        | Hold              |
|-----------|-----------------------|------------|-------------------|
| L-outer   | `KC_LGUI`             | CMD        | CMD (modifier)    |
| L-middle  | `MO(3)`               | —          | Symbols (L3)      |
| L-inner   | `LT(1, KC_ENT)`       | Enter      | QWERTY (L1)       |
| R-inner   | `LT(2, KC_SPC)`       | Space      | Numbers (L2)      |
| R-middle  | `MO(4)`               | —          | RGB / Boot (L4)   |
| R-outer   | `KC_RALT`             | Right Alt  | RAlt (modifier)   |

On Layers 2, 3, and 4 every thumb slot is `KC_TRNS` so releasing the held thumb returns you cleanly to whichever base (Colemak or QWERTY) was active underneath.

---

### Layer 0: Colemak-DH (ISO) — Base
* **Type:** Permanent base floor (default on boot)
* **Color:** 🔵 Blue
* **Purpose:** Primary layout for typing, programming, and writing.

```
┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ Tab │  Q  │  W  │  F  │  P  │  B  │   │  J  │  L  │  U  │  Y  │  ;  │ Bsp │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│Ctrl │  A  │  R  │  S  │  T  │  G  │   │  M  │  N  │  E  │  I  │  O  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
│Shift│  Z  │  X  │  C  │  D  │  V  │   │  K  │  H  │  ,  │  .  │  /  │ Esc │
└─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
              │ CMD │ L3  │ Ent │       │ Spc │ L4  │ Alt │
              │     │ MO  │ L1  │       │ L2  │ MO  │     │
              └─────┴─────┴─────┘       └─────┴─────┴─────┘
```

### Layer 1: QWERTY (ISO) — Alternate Base
* **Type:** Alternate base, reachable two ways:
  * **Momentary (hold):** Hold the **left-inner thumb** (Enter key) for a quick burst of QWERTY. Release to return to Colemak.
  * **Persistent (toggle):** Hold R-middle to reach Layer 4, then tap `DF(1)` — QWERTY is now your default base until you tap `DF(0)` to switch back.
* **Color:** 🔴 Red
* **Purpose:** Panic typing when muscle memory fails, handing the keyboard to someone else, or extended QWERTY sessions.
* **Thumbs:** Identical cluster to Layer 0, so Numbers and Symbols still open the same way from QWERTY.

### Layer 2: Numbers + Arrows
* **Type:** Temporary overlay (held via R-inner thumb on `LT(2, KC_SPC)`)
* **Color:** 🟢 Green
* **Top Row:** `1 2 3 4 5` ‖ `6 7 8 9 0`
* **Right Home Row (Arrows):** `←` `↓` `↑` `→`
* **All thumbs:** Transparent — release the R-inner thumb to fall back to the base.

### Layer 3: Symbols
* **Type:** Temporary overlay (held via L-middle thumb on `MO(3)`)
* **Color:** 🩷 Hot Pink / Magenta
* **Top Row:** `! @ # $ %` ‖ `^ & * ( )`
* **Right Home Row:** `- = [ ] \ \``
* **Right Bottom Row:** `_ + { } | ~`
* **All thumbs:** Transparent — release the L-middle thumb to fall back to the base.

### Layer 4: RGB + Firmware Adjust + Base Swap
* **Type:** Momentary overlay (held via R-middle thumb on `MO(4)`)
* **Color:** 🟡 Yellow
* **Trap Fix:** All thumb slots are `KC_TRNS`, so releasing your thumb instantly drops you back to your base.
* **Top-Left (Tab position):** `QK_BOOT` — jump into bootloader for flashing
* **Persistent Base Swap (right home row):**
  * Index finger: `DF(0)` ➡️ make **Colemak-DH** the default base
  * Middle finger: `DF(1)` ➡️ make **QWERTY** the default base
* **RGB Controls (left home/bottom rows):** `RM_TOGG` `RM_HUEU` `RM_SATU` `RM_VALU` `RM_NEXT` `RM_HUED` `RM_SATD` `RM_VALD`
  * **Note:** the per-layer color indicator overrides the matrix color every frame, so hue/sat/val/mode changes are mostly cosmetic right now. `RM_TOGG` still works to turn RGB off entirely.

---

## 🌈 Per-Layer Color Indicator

A `rgb_matrix_indicators_advanced_user()` callback paints every LED a solid color tied to the current layer:

| Layer | Name      | Color           | RGB              |
|-------|-----------|-----------------|------------------|
| 0     | Colemak   | Blue            | `(  0,   0, 255)`|
| 1     | QWERTY    | Red             | `(255,   0,   0)`|
| 2     | Numbers   | Green           | `(  0, 255,   0)`|
| 3     | Symbols   | Hot Pink        | `(255,   0, 128)`|
| 4     | RGB       | Yellow          | `(255, 255,   0)`|

The "highest active layer" calculation uses `layer_state | default_layer_state`, so a persistent `DF(1)` swap correctly shows red even when no thumb is held.

**Layer 4 has a special override:** while on the RGB/Utility layer (yellow), the two `DF()` keys are painted with the color of the layer they'd switch you to, so you can see at a glance which is which:

| Key      | Lights up                       |
|----------|---------------------------------|
| `DF(0)`  | 🔵 **Blue** (jumps to Colemak)  |
| `DF(1)`  | 🔴 **Red** (jumps to QWERTY)    |

If you'd rather tune the colors, edit the `switch` block (and the per-key overrides just below it) at the bottom of `keymap.c`.

---

## 🧭 Navigation Between Layers

QMK layers work as a **stack**: higher-numbered active layers override lower ones, and each non-transparent key on the top layer wins. On this build, Layers 2/3/4 are all **hold-only** — they only stay active while the corresponding thumb is held. Layers 0 and 1 are the only candidates for the "base floor" (the layer that's always on underneath), and you swap between them with `DF()`.

### From Layer 0 (Colemak Base — Blue)

| To get to…                     | Do this                                                   | Returns when…                       |
|--------------------------------|-----------------------------------------------------------|-------------------------------------|
| Layer 1 (QWERTY, momentary)    | **Hold** L-inner thumb (Enter)                            | You release the thumb               |
| Layer 1 (QWERTY, permanent)    | Hold R-middle → tap right-home-row index (`DF(1)`)        | You tap `DF(0)` from Layer 4 again  |
| Layer 2 (Numbers)              | **Hold** R-inner thumb (Space)                            | You release the thumb               |
| Layer 3 (Symbols)              | **Hold** L-middle thumb                                   | You release the thumb               |
| Layer 4 (RGB / Utility)        | **Hold** R-middle thumb                                   | You release the thumb               |

### From Layer 1 (QWERTY Base — Red, when active as the floor)

| To get to…                     | Do this                                                   | Returns when…                       |
|--------------------------------|-----------------------------------------------------------|-------------------------------------|
| Layer 0 (Colemak, permanent)   | Hold R-middle → tap right-home-row index (`DF(0)`)        | You tap `DF(1)` from Layer 4 again  |
| Layer 2 (Numbers)              | **Hold** R-inner thumb (Space)                            | You release the thumb               |
| Layer 3 (Symbols)              | **Hold** L-middle thumb                                   | You release the thumb               |
| Layer 4 (RGB / Utility)        | **Hold** R-middle thumb                                   | You release the thumb               |

> **Note:** there is no "momentary Colemak from QWERTY" — `LT(1, KC_ENT)` only ever activates Layer 1. If QWERTY is already your floor (via `DF(1)`), holding L-inner re-asserts Layer 1 (no-op). To get back to Colemak you must use `DF(0)` from Layer 4.

### From Layer 2 (Numbers — Green, held)
* **Exit:** Release the R-inner thumb. You land back on the current base.

### From Layer 3 (Symbols — Hot Pink, held)
* **Exit:** Release the L-middle thumb. You land back on the current base.

### From Layer 4 (RGB / Utility — Yellow, held)
* **Exit:** Release the R-middle thumb. You land back on the current base.
* **What you can do here:**
  * Tap `DF(0)` to make Colemak the persistent base.
  * Tap `DF(1)` to make QWERTY the persistent base.
  * Tap `QK_BOOT` (top-left) to enter flashing mode.
  * Tap any `RM_*` key to control the RGB (note: layer indicator overrides color).

### Cheat Sheet

```
                   ┌──────────────────────┐
                   │   FLOOR (always on)  │
                   │  Layer 0 Colemak ─🔵 │
                   │     ⇅  via DF(0/1)   │
                   │  Layer 1 QWERTY  ─🔴 │
                   └──────────────────────┘
                              ▲
              held thumb adds an overlay:
                              ▼
   L-middle ──► Layer 3 Symbols    🩷  (release to drop)
   L-inner  ──► Layer 1 QWERTY     🔴  (release to drop, momentary only)
   R-inner  ──► Layer 2 Numbers    🟢  (release to drop)
   R-middle ──► Layer 4 RGB/Util   🟡  (release to drop)

   L-outer  ──► CMD modifier
   R-outer  ──► RAlt modifier
```

---

## ⚡ How to Flash
1. Enter bootloader: hold the **right-middle thumb** to reach Layer 4, then tap the **top-left** key (`QK_BOOT`).
2. Use [QMK Toolbox](https://github.com/qmk/qmk_toolbox) (or `dfu-programmer` / `avrdude`) to flash the compiled `.hex`.
3. Repeat for the other half of the split.
