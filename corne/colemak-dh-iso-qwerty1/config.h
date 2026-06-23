/* Keymap-level config overrides for the Corne (crkbd/rev1).
 *
 * Anything not set here falls back to the keyboard-level defaults in
 * qmk_firmware/keyboards/crkbd/rev1/config.h.
 */

#pragma once

/* -----------------------------------------------------------------------
 * RGB Matrix brightness
 *
 * RGB_MATRIX_DEFAULT_VAL is the boot-time brightness (HSV "value"), 0–255.
 * Stock QMK boots at 255 (full blast). Drop it to keep your eyes intact.
 *
 * 32  ≈ 12% — very dim, ambient
 * 64  ≈ 25% — comfortable in a lit room
 * 128 ≈ 50% — bright but not painful
 *
 * Live tweak with RM_VALU / RM_VALD on Layer 4.
 * ----------------------------------------------------------------------- */
#define RGB_MATRIX_DEFAULT_VAL 48

/* Note: the Corne keyboard.json already caps RGB_MATRIX_MAXIMUM_BRIGHTNESS
 * at 120 (≈47%), so RM_VALU can't push past that. If you ever want it
 * higher, you'd need to #undef + #define here:
 *
 *   #undef  RGB_MATRIX_MAXIMUM_BRIGHTNESS
 *   #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
 */
