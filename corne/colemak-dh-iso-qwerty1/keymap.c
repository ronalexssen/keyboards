/* Copyright 2024
 *
 * Corne (crkbd/rev1) — Colemak-DH ISO + QWERTY keymap
 * Layout macro: LAYOUT_split_3x6_3
 *
 * ---------------------------------------------------------------------------
 * Fixed layer stack (order matters — higher layers win):
 *
 *   0  Colemak-DH      Default typing layer
 *   1  QWERTY          Alternate base (hold L-inner to use momentarily,
 *                      or DF(1) from Layer 4 to make it persistent)
 *   2  Numbers         Number row + arrow cluster
 *   3  Symbols         Shifted-number row + brackets/operators
 *   4  RGB / Utility   Backlight controls + bootloader + base swap
 *
 * ---------------------------------------------------------------------------
 * Thumb cluster (identical on Layer 0 and Layer 1):
 *
 *   L-outer:  KC_LGUI               plain modifier — CMD / Apple key
 *   L-middle: MO(3)                 hold = Symbols
 *   L-inner:  LT(1, KC_ENT)         tap = Enter,  hold = QWERTY
 *   R-inner:  LT(2, KC_SPC)         tap = Space,  hold = Numbers
 *   R-middle: MO(4)                 hold = RGB / Utility
 *   R-outer:  KC_RALT               plain modifier — Right Alt
 *
 * On every utility layer (2, 3, 4) all thumb positions are KC_TRNS so that
 * releasing the held thumb falls straight back through to whichever base
 * (Colemak or QWERTY) is active underneath — we never get layer-trapped.
 *
 * Persistent base swap:
 *   Layer 4 carries DF(0) and DF(1) so you can permanently flip the base
 *   floor between Colemak and QWERTY. Hold R-middle to reach Layer 4, tap
 *   DF(1) for QWERTY or DF(0) for Colemak.
 *
 * ---------------------------------------------------------------------------
 * Per-layer RGB color indicator (see bottom of file):
 *
 *   Layer 0 (Colemak) → Blue
 *   Layer 1 (QWERTY)  → Red
 *   Layer 2 (Numbers) → Green
 *   Layer 3 (Symbols) → Magenta / Hot Pink
 *   Layer 4 (RGB)     → Yellow
 * ---------------------------------------------------------------------------
 */

#include QMK_KEYBOARD_H

enum layers {
    _COLEMAK = 0,
    _QWERTY,
    _NUMS,
    _SYMS,
    _RGB,
};

/* Shorthand for the thumb cluster — used identically on both base layers */
#define TH_L_OUT KC_LGUI             /* L outer:  CMD / Apple              */
#define TH_L_MID MO(_SYMS)           /* L middle: hold for Symbols (L3)    */
#define TH_L_IN  LT(_QWERTY, KC_ENT) /* L inner:  Enter / QWERTY (L1)      */
#define TH_R_IN  LT(_NUMS, KC_SPC)   /* R inner:  Space / Numbers (L2)     */
#define TH_R_MID MO(_RGB)            /* R middle: hold for RGB/Util (L4)   */
#define TH_R_OUT KC_RALT             /* R outer:  Right Alt                */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* -------------------------------------------------------------------
     * Layer 0 — Colemak-DH (ISO)
     *
     * ,-----------------------------------.   ,-----------------------------------.
     * | TAB |  Q  |  W  |  F  |  P  |  B  |   |  J  |  L  |  U  |  Y  |  ;  |BSPC |
     * |-----+-----+-----+-----+-----+-----|   |-----+-----+-----+-----+-----+-----|
     * |LCTL |  A  |  R  |  S  |  T  |  G  |   |  M  |  N  |  E  |  I  |  O  |  '  |
     * |-----+-----+-----+-----+-----+-----|   |-----+-----+-----+-----+-----+-----|
     * |LSFT |  Z  |  X  |  C  |  D  |  V  |   |  K  |  H  |  ,  |  .  |  /  | ESC |
     * `-----------------+-----+-----+-----'   `-----+-----+-----+-----------------'
     *                   | CMD | L3  | ENT |   | SPC | L4  | ALT |
     *                   |     | MO  |  L1 |   |  L2 | MO  |     |
     *                   `-----+-----+-----'   `-----+-----+-----'
     */
    [_COLEMAK] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q, KC_W, KC_F, KC_P, KC_B,                          KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, KC_BSPC,
        KC_LCTL, KC_A, KC_R, KC_S, KC_T, KC_G,                          KC_M, KC_N, KC_E,    KC_I,   KC_O,    KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_D, KC_V,                          KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_ESC,
                              TH_L_OUT, TH_L_MID, TH_L_IN,    TH_R_IN, TH_R_MID, TH_R_OUT
    ),

    /* -------------------------------------------------------------------
     * Layer 1 — QWERTY (ISO)
     *
     * Reached either by holding the L-inner thumb (Enter) for a quick
     * burst, or by tapping DF(1) on Layer 4 to make it the persistent
     * base floor. Thumb cluster is identical to Colemak.
     */
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,                          KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,                          KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                          KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC,
                              TH_L_OUT, TH_L_MID, TH_L_IN,    TH_R_IN, TH_R_MID, TH_R_OUT
    ),

    /* -------------------------------------------------------------------
     * Layer 2 — Numbers (held via R-inner thumb / Space)
     *
     * Number row on top, arrow cluster on the right home row.
     * All thumb keys transparent so release returns to the base.
     */
    [_NUMS] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ESC,
                                _______, _______, _______,    _______, _______, _______
    ),

    /* -------------------------------------------------------------------
     * Layer 3 — Symbols (held via L-middle thumb)
     *
     * Top row: shifted number row (! @ # $ % ^ & * ( ))
     * Right cluster: math + brackets + grave/tilde/pipe/backslash
     */
    [_SYMS] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                                _______, _______, _______,    _______, _______, _______
    ),

    /* -------------------------------------------------------------------
     * Layer 4 — RGB / Utility (held via R-middle thumb)
     *
     * Top-left:   QK_BOOT          — jump into bootloader for flashing
     * Left home:  RGB controls     — toggle/hue/sat/val (note: per-layer
     *                                color indicator overrides RGB color,
     *                                so HUE/SAT/VAL/MODE changes are mostly
     *                                cosmetic; RM_TOGG still turns it off)
     * Right home: DF(0) / DF(1)    — persistently swap the base floor
     *
     * All thumb slots remain KC_TRNS so releasing R-middle returns you to
     * the (possibly newly-swapped) base layer without getting trapped.
     */
    [_RGB] = LAYOUT_split_3x6_3(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX,
        RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,           XXXXXXX, DF(_COLEMAK), DF(_QWERTY),  XXXXXXX, XXXXXXX, XXXXXXX,
        RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX,
                                _______, _______, _______,    _______, _______, _______
    ),
};

#ifdef RGB_MATRIX_ENABLE
/* ===========================================================================
 * Per-Layer Color Indicator
 * ===========================================================================
 * Paints every LED a solid color tied to the currently active layer:
 *
 *   Layer 0 (Colemak) → Blue
 *   Layer 1 (QWERTY)  → Red
 *   Layer 2 (Numbers) → Green
 *   Layer 3 (Symbols) → Magenta / Hot Pink
 *   Layer 4 (RGB)     → Yellow
 *
 * Uses the *advanced* indicators callback so it runs after the active RGB
 * matrix effect, cleanly overriding it. RM_TOGG is still honored: if RGB
 * is disabled, the callback bails out and the board stays dark.
 *
 * "Highest active layer" comes from (layer_state | default_layer_state)
 * so a persistent DF(1) swap correctly shows red even with no thumb held.
 * ===========================================================================
 */
/* Helper: paint a single LED if it's inside the current callback's range.
 * The advanced indicators callback is called in led_min..led_max chunks,
 * so we have to range-check before writing.
 */
static void rgb_paint_key(uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b,
                          uint8_t led_min, uint8_t led_max) {
    uint8_t led = g_led_config.matrix_co[row][col];
    if (led != NO_LED && led >= led_min && led < led_max) {
        rgb_matrix_set_color(led, r, g, b);
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_is_enabled()) {
        return false;
    }

    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    uint8_t r = 0, g = 0, b = 0;
    switch (layer) {
        case _COLEMAK: r =   0; g =   0; b = 255; break;  /* Blue            */
        case _QWERTY:  r = 255; g =   0; b =   0; break;  /* Red             */
        case _NUMS:    r =   0; g = 255; b =   0; break;  /* Green           */
        case _SYMS:    r = 255; g =   0; b = 128; break;  /* Hot Pink        */
        case _RGB:     r = 255; g = 255; b =   0; break;  /* Yellow          */
        default: return false;
    }

    /* Scale the layer color by the user-controlled brightness (val),
     * so RM_VALU / RM_VALD still raise/lower brightness live and we
     * inherit RGB_MATRIX_DEFAULT_VAL at boot from config.h.
     */
    uint8_t val = rgb_matrix_get_val();
    r = (uint16_t)r * val / 255;
    g = (uint16_t)g * val / 255;
    b = (uint16_t)b * val / 255;

    /* Wash everything in the (brightness-scaled) layer color first. */
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, r, g, b);
    }

    /* On Layer 4, override the two DF keys with the colors of the layer
     * they'd swap you to, so you can see at a glance which is which:
     *   DF(0) → Colemak → Blue
     *   DF(1) → QWERTY  → Red
     *
     * DF keys live on keymap row 2 (the home row) of the right hand:
     *   DF(_COLEMAK) is at the right index finger    (matrix [5][4])
     *   DF(_QWERTY)  is at the right middle finger   (matrix [5][3])
     * These matrix coordinates come from how LAYOUT_split_3x6_3 reverses
     * the right-hand columns; see qmk_firmware/keyboards/crkbd/crkbd.h.
     *
     * Brightness-scale these too so they dim along with everything else.
     */
    if (layer == _RGB) {
        uint8_t df0_b = (uint16_t)255 * val / 255;       /* Blue channel  */
        uint8_t df1_r = (uint16_t)255 * val / 255;       /* Red channel   */
        rgb_paint_key(5, 4, 0,     0, df0_b, led_min, led_max); /* DF(0) */
        rgb_paint_key(5, 3, df1_r, 0,     0, led_min, led_max); /* DF(1) */
    }

    return false;
}
#endif
