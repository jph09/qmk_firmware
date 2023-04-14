/* Copyright 2022 Khoa Truong <foureight84@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include <string.h>
#include "lib/lib8tion/lib8tion.h"


enum sofle_layers {
    _BASE = 0,
    _QWERTY,
    _TAP,
    _NAV,
    _MOUSE,
    _MEDIA,
    _NUM,
    _SYM,
    _FUN,
    _BUTTON,
};

// enum custom_keycodes {
//     KC_UND = SAFE_RANGE,
//     KC_RDO
//     KC_CPY,
//     KC_PST,
// };

/* Safety Tap Dance on special functions */
enum {
    TD_BOOT = 0,
    TD_BASE,
    TD_QWERTY,
    TD_TAP,
    TD_NAV,
    TD_MOUSE,
    TD_MEDIA,
    TD_NUM,
    TD_SYM,
    TD_FUN,
    TD_LEFT,
    TD_RIGHT,
};

void tap_dance_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        reset_keyboard();
    }
};

void tap_dance_layer_base(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        // set_single_persistent_default_layer(_BASE);
        default_layer_set((layer_state_t)1 << _BASE);
    }
};

void tap_dance_layer_qwerty(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        // set_single_persistent_default_layer(_QWERTY);
        default_layer_set((layer_state_t)1 << _QWERTY);
    }
};

void tap_dance_layer_tap(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << _TAP);
    }
};

void tap_dance_layer_left(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        switch (get_highest_layer(default_layer_state | layer_state)) {
            case _NAV:
            case _NUM:
                default_layer_set((layer_state_t)1 << _NUM);
                break;
            case _MOUSE:
            case _SYM:
                default_layer_set((layer_state_t)1 << _SYM);
                break;
            case _MEDIA:
            case _FUN:
                default_layer_set((layer_state_t)1 << _FUN);
                break;
        }
    }
};
void tap_dance_layer_right(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        switch (get_highest_layer(default_layer_state | layer_state)) {
            case _NAV:
            case _NUM:
                default_layer_set((layer_state_t)1 << _NAV);
                break;
            case _MOUSE:
            case _SYM:
                default_layer_set((layer_state_t)1 << _MOUSE);
                break;
            case _MEDIA:
            case _FUN:
                default_layer_set((layer_state_t)1 << _MEDIA);
                break;
        }
    }
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN (tap_dance_boot),
    [TD_BASE] = ACTION_TAP_DANCE_FN (tap_dance_layer_base),
    [TD_QWERTY] = ACTION_TAP_DANCE_FN (tap_dance_layer_qwerty),
    [TD_TAP] = ACTION_TAP_DANCE_FN (tap_dance_layer_tap),
    [TD_LEFT] = ACTION_TAP_DANCE_FN (tap_dance_layer_left),
    [TD_RIGHT] = ACTION_TAP_DANCE_FN (tap_dance_layer_right),
};

/* Mod Tap defs for COLEMAK-DH */
#define MTG_A LGUI_T(KC_A) // same as QWERTY
#define MTA_R LALT_T(KC_R)
#define MTC_S LCTL_T(KC_S)
#define MTS_T LSFT_T(KC_T)
#define MTS_N RSFT_T(KC_N)
#define MTC_E RCTL_T(KC_E)
#define MTA_I LALT_T(KC_I) // LALT to avoid AltGr
#define MTG_O RGUI_T(KC_O)

/* Mod Tap defs for QWERTY */
// #define MTG_A LGUI_T(KC_A) // same as COLEMAK-DH
#define MTA_S LALT_T(KC_S)
#define MTC_D LCTL_T(KC_D)
#define MTS_F LSFT_T(KC_F)
#define MTS_J RSFT_T(KC_J)
#define MTC_K RCTL_T(KC_K)
#define MTA_L LALT_T(KC_L) // LALT to avoid AltGr
#define MTG_SC RGUI_T(KC_SEMICOLON)
#define MTG_QU RGUI_T(KC_QUOTE)

/* Extra Mod Taps */
#define MTS_LPRN LSFT_T(KC_LPRN)
#define MTS_RPRN RSFT_T(KC_RPRN)
#define MTC_LBRC LCTL_T(KC_LBRC)
#define MTC_RBRC RCTL_T(KC_RBRC)

/* Layer Taps for thumb keys */
#define LT_SPC LT(_NAV, KC_SPACE)
#define LT_TAB LT(_MOUSE, KC_TAB)
#define LT_ESC LT(_MEDIA, KC_ESC)
#define LT_BSPC LT(_NUM, KC_BACKSPACE)
#define LT_ENT LT(_SYM, KC_ENTER)
#define LT_DEL LT(_FUN, KC_DELETE)
#define LT_Z LT(_BUTTON, KC_Z)
#define LT_SLSH LT(_BUTTON, KC_SLSH)

/* Override shifted keys */
const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);
const key_override_t non_us_quot_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, S(KC_2));
const key_override_t non_us_two_override = ko_make_basic(MOD_MASK_SHIFT, KC_2, S(KC_QUOT));
const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    &non_us_quot_override,
    &non_us_two_override,
    NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK Mod-DH */
[_BASE] = LAYOUT( \
  KC_GRV,   KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                     KC_6, KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_LCBR,  KC_Q,  KC_W,  KC_F,  KC_P,  KC_B,                     KC_J, KC_L,  KC_U,    KC_Y,   KC_QUOT, KC_RCBR, \
  KC_LPRN,  MTG_A, MTA_R, MTC_S, MTS_T, KC_G,                     KC_M, MTS_N, MTC_E,   MTA_I,  MTG_O,   KC_RPRN, \
  KC_LBRC,  LT_Z,  KC_X,  KC_C,  KC_D,  KC_V, KC_MUTE,   XXXXXXX, KC_K, KC_H,  KC_COMM, KC_DOT, LT_SLSH, KC_RBRC, \
            KC_LGUI, KC_LALT, LT_ESC, LT_SPC, LT_TAB,     LT_ENT, LT_BSPC, LT_DEL, KC_RALT, KC_RGUI \
),

/* QWERTY */
[_QWERTY] = LAYOUT( \
  KC_GRV,   KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                     KC_6, KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_LCBR,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                     KC_Y, KC_U,  KC_I,    KC_O,   KC_P,    KC_RCBR, \
  KC_LPRN,  MTG_A, MTA_S, MTC_D, MTS_F, KC_G,                     KC_H, MTS_J, MTC_K,   MTA_L,  MTG_QU,  KC_RPRN, \
  KC_LBRC,  LT_Z,  KC_X,  KC_C,  KC_V,  KC_B, KC_MUTE,   XXXXXXX, KC_N, KC_M,  KC_COMM, KC_DOT, LT_SLSH, KC_RBRC, \
            KC_LGUI, KC_LALT, LT_ESC, LT_SPC, LT_TAB,     LT_ENT, LT_BSPC, LT_DEL, KC_RALT, KC_RGUI \
),

/* QWERTY without mod/taps */
[_TAP] = LAYOUT( \
  KC_GRV,    KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                     KC_6, KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, \
  DF(_BASE), KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                     KC_Y, KC_U,  KC_I,    KC_O,   KC_P,    KC_SCLN, \
  KC_LSFT,   KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                     KC_H, KC_J,  KC_K,    KC_L,   KC_QUOT, KC_RSFT, \
  KC_LCTL,   KC_Z,  KC_X,  KC_C,  KC_V,  KC_B, KC_MUTE,   XXXXXXX, KC_N, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RCTL, \
            KC_LGUI, KC_LALT, KC_ESC, KC_SPC, KC_TAB,       KC_ENT, KC_BSPC, KC_DEL, KC_RALT, KC_RGUI \
),

[_NAV] = LAYOUT( \
  XXXXXXX, XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX,      XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
  XXXXXXX, TD(TD_BOOT), TD(TD_TAP), TD(TD_QWERTY), TD(TD_BASE),  CG_TOGG,                     KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,   XXXXXXX, \
  XXXXXXX, KC_LGUI,     KC_LALT,    KC_LCTL,       KC_LSFT,      CW_TOGG,                     CW_TOGG, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX, \
  XXXXXXX, MO(_BUTTON), XXXXXXX,    TD(TD_LEFT),   TD(TD_RIGHT), XXXXXXX, KC_MUTE,   XXXXXXX, KC_AGIN, S(KC_INS), C(KC_INS), S(KC_DEL),  KC_UNDO, XXXXXXX, \
                                XXXXXXX, XXXXXXX, _______, _______, _______,          KC_ENT, KC_BSPC, KC_DEL, XXXXXXX, XXXXXXX \
),

[_MOUSE] = LAYOUT( \
  XXXXXXX, XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX,      XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, TD(TD_BOOT), TD(TD_TAP), TD(TD_QWERTY), TD(TD_BASE),  CG_TOGG,                     XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, \
  XXXXXXX, KC_LGUI,     KC_LALT,    KC_LCTL,       KC_LSFT,      CW_TOGG,                     XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, \
  XXXXXXX, MO(_BUTTON), XXXXXXX,    TD(TD_LEFT),   TD(TD_RIGHT), XXXXXXX, KC_MUTE,   XXXXXXX, KC_AGIN, S(KC_INS), C(KC_INS), S(KC_DEL),  KC_UNDO, XXXXXXX, \
                                      XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN1, KC_BTN2,          KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX \
),

[_MEDIA] = LAYOUT( \
  XXXXXXX, XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX,      XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, TD(TD_BOOT), TD(TD_TAP), TD(TD_QWERTY), TD(TD_BASE),  CG_TOGG,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_LGUI,     KC_LALT,    KC_LCTL,       KC_LSFT,      CW_TOGG,                     KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX, \
  XXXXXXX, MO(_BUTTON), XXXXXXX,    TD(TD_LEFT),   TD(TD_RIGHT), XXXXXXX, KC_MUTE,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                      XXXXXXX, XXXXXXX, _______, _______, _______,          KC_MSTP, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX \
),

[_NUM] = LAYOUT( \
  XXXXXXX, KC_BSPC, KC_SLSH, KC_ASTR, KC_PLUS, KC_MINS,                      XXXXXXX, XXXXXXX,     XXXXXXX,       XXXXXXX,    XXXXXXX,     XXXXXXX,  \
  KC_TAB,  KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                      CG_TOGG, TD(TD_BASE), TD(TD_QWERTY), TD(TD_TAP), TD(TD_BOOT), XXXXXXX, \
  KC_ENT,  KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                       CW_TOGG, KC_RSFT,     KC_RCTL,       KC_LALT,    KC_RGUI,     XXXXXXX, \
  XXXXXXX, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_NUBS, KC_MUTE,    XXXXXXX, XXXXXXX, TD(TD_LEFT), TD(TD_RIGHT),  KC_RALT,    MO(_BUTTON), XXXXXXX, \
            KC_TAB, KC_ENTER, KC_DOT, KC_0,    KC_MINS,          _______, _______, _______, XXXXXXX, XXXXXXX \
),

[_SYM] = LAYOUT( \
  XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,    XXXXXXX,     XXXXXXX, \
  XXXXXXX,   S(KC_LBRC), S(KC_7), S(KC_8), S(KC_9), S(KC_RBRC),                        CG_TOGG, TD(TD_BASE),   TD(TD_QWERTY), TD(TD_TAP), TD(TD_BOOT), XXXXXXX, \
  XXXXXXX,   S(KC_SCLN), S(KC_4), S(KC_5), S(KC_6), S(KC_EQL),                         CW_TOGG, KC_RSFT,       KC_RCTL,       KC_LALT,    KC_RGUI,     XXXXXXX, \
  XXXXXXX,   S(KC_NUHS), S(KC_1), S(KC_QUOT), S(KC_3), S(KC_NUBS), KC_MUTE,   XXXXXXX, XXXXXXX, TD(TD_LEFT),   TD(TD_RIGHT),  KC_RALT,    MO(_BUTTON), XXXXXXX, \
                  XXXXXXX, XXXXXXX, KC_NUHS, S(KC_0), S(KC_MINS),          _______, _______, _______, XXXXXXX, XXXXXXX \
),

[_FUN] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX,     XXXXXXX,       XXXXXXX,    XXXXXXX,     XXXXXXX, \
  XXXXXXX, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                     CG_TOGG, TD(TD_BASE), TD(TD_QWERTY), TD(TD_TAP), TD(TD_BOOT), XXXXXXX, \
  XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,                     CW_TOGG, KC_RSFT,     KC_RCTL,       KC_LALT,    KC_RGUI,     XXXXXXX, \
  XXXXXXX, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, KC_MUTE,   XXXXXXX, XXXXXXX, TD(TD_LEFT), TD(TD_RIGHT),  KC_RALT,    MO(_BUTTON), XXXXXXX, \
                  XXXXXXX, XXXXXXX, KC_APP, KC_SPC, KC_TAB,          _______, _______, _______, XXXXXXX, XXXXXXX \
),

[_BUTTON] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_UNDO, S(KC_DEL),  C(KC_INS), S(KC_INS), KC_AGIN,                KC_AGIN, S(KC_INS), C(KC_INS), S(KC_DEL),  KC_UNDO,  XXXXXXX, \
  XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, CW_TOGG,                       CW_TOGG, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX, \
  XXXXXXX, KC_UNDO, S(KC_DEL),  C(KC_INS), S(KC_INS), KC_AGIN, KC_MUTE,     XXXXXXX, KC_AGIN, S(KC_INS), C(KC_INS), S(KC_DEL),  KC_UNDO,  XXXXXXX, \
              XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN1, KC_BTN2,             KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX \
),

};

#ifdef OLED_ENABLE

static void print_status(void) {

    if ( get_highest_layer(default_layer_state) <= _TAP) {

        oled_set_cursor(0, 1);
        oled_write_ln_P(PSTR("Mode "), false);

        switch (get_highest_layer(default_layer_state)) {
            case _BASE:
                oled_write_ln_P(PSTR("COLE"), false);
                break;
            case _QWERTY:
            case _TAP:
                oled_write_ln_P(PSTR("QWER"), false);
                break;
        }

        if (keymap_config.swap_lctl_lgui) {
            oled_write_ln_P(PSTR("MAC"), false);
        } else {
            oled_write_ln_P(PSTR("WIN"), false);
        }
    }

    oled_set_cursor(0, 8);
    oled_write_ln_P(PSTR("Layer"), false);

    switch (get_highest_layer(default_layer_state | layer_state)) {
        case _BASE:
        case _QWERTY:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _TAP:
            oled_write_ln_P(PSTR("TAP"), true);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("NAV"), true);
            break;
        case _MOUSE:
            oled_write_ln_P(PSTR("MOU"), true);
            break;
        case _MEDIA:
            oled_write_ln_P(PSTR("MED"), true);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("NUM"), true);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("SYM"), true);
            break;
        case _FUN:
            oled_write_ln_P(PSTR("FUN"), true);
            break;
        case _BUTTON:
            oled_write_ln_P(PSTR("BTN"), true);
            break;
        default:
            oled_write_ln_P(PSTR("OTHER"), true);

    }

    oled_set_cursor(0, 14);

    // Capslock indicator
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR("CAPS"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// Remove all the animation to save space - but don't reflash the right half and it will still work!
//
//
// /* Animation bit by j-inc https://github.com/qmk/qmk_firmware/tree/master/keyboards/kyria/keymaps/j-inc */
// // WPM-responsive animation stuff here
// #define IDLE_FRAMES 1
// #define IDLE_SPEED 40 // below this wpm value your animation will idle

// // #define PREP_FRAMES 1 // uncomment if >1

// #define TAP_FRAMES 2
// #define TAP_SPEED 60 // above this wpm value typing animation to triggere

// #define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
// // #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
// #define ANIM_SIZE 320 // number of bytes in array, minimize for adequate firmware size, max is 1024

// uint32_t anim_timer = 0;
// uint32_t anim_sleep = 0;
// uint8_t current_idle_frame = 0;
// // uint8_t current_prep_frame = 0; // uncomment if PREP_FRAMES >1
// uint8_t current_tap_frame = 0;

// // Implementation credit j-inc(/James Incandenza), pixelbenny, and obosob.
// // Bongo cat images changed and adapted for sofle keyboard oled size.
// // Original gif can be found here: https://www.pixilart.com/art/bongo-cat-bd2a8e9323aa705
// static void render_anim(void) {
//     static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {
//         {
//         0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0x03, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00,
//         0xe1, 0x1e, 0x00, 0xc0, 0xbc, 0x83, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x3c, 0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xe0, 0x1f,
//         0x01, 0xc0, 0x3c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x31, 0x05, 0x41, 0x12, 0x04,
//         0x00, 0x00, 0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0, 0x3f, 0x03, 0x80,
//         0x78, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x03, 0x05,
//         0x00, 0x00, 0xf0, 0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80, 0x78, 0x07,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0xe0, 0x1e, 0x01, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x07, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0xf0, 0x0f, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x18, 0x60, 0x80, 0x00, 0x00, 0xe1, 0x1e, 0x01, 0xf0, 0x8f, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
//         0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19,
//         0x19, 0x41, 0x0a, 0x22, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18,
//         0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
//         0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x70, 0x80,
//         0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02,
//         0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02, 0x01,
//         }
//     };
//     static const char PROGMEM tap[TAP_FRAMES][ANIM_SIZE] = {
//         {
//         0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0xff, 0xff, 0xff, 0x7c, 0x70, 0x40, 0x40,
//         0x61, 0x5e, 0x80, 0xc0, 0xbc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x3c, 0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0f, 0x3f, 0xf8, 0xf0, 0xf0, 0x20,
//         0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0, 0x3f, 0x03, 0x80,
//         0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04,
//         0x00, 0x00, 0xf0, 0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80, 0x78, 0x07,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0xe0, 0x1e, 0x01, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x07, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0xf0, 0x0f, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x18, 0x60, 0x80, 0x00, 0x00, 0xe1, 0x1e, 0x01, 0xf0, 0x8f, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
//         0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19,
//         0x19, 0x41, 0x0a, 0x22, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18,
//         0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
//         0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x70, 0x80,
//         0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02,
//         0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02, 0x01,
//         },
//         {
//         0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0x03, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00,
//         0xe1, 0x1e, 0x00, 0xc0, 0xbc, 0x83, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x3c, 0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xe0, 0x1f,
//         0x01, 0xc0, 0x3c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x31, 0x05, 0x41, 0x12, 0x04,
//         0x00, 0x00, 0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0, 0x3f, 0x03, 0x80,
//         0x78, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x03, 0x05,
//         0x00, 0x00, 0xf0, 0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80, 0x78, 0x07,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0xe0, 0xfe, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x07, 0x03, 0x0f, 0x3f, 0xff, 0x03, 0x01, 0x03, 0x07, 0x18, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x18, 0x60, 0x80, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3c, 0x00, 0x00, 0x00, 0x00,
//         0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf3, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18,
//         0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x70, 0x80,
//         0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02,
//         0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02, 0x01
//         },
//     };

//     //assumes 1 frame prep stage
//     void animation_phase(void) {
//         if(get_current_wpm() <=IDLE_SPEED){
//             oled_write_raw_P(idle[0], ANIM_SIZE);
//          }
//          if(get_current_wpm() >=TAP_SPEED){
//              current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
//              oled_write_raw_P(tap[abs((TAP_FRAMES-1)-current_tap_frame)], ANIM_SIZE);
//          }
//     }
//     if(get_current_wpm() != 000) {
//         oled_on(); // not essential but turns on animation OLED with any alpha keypress
//         if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
//             anim_timer = timer_read32();
//             animation_phase();
//         }
//         anim_sleep = timer_read32();
//     } else {
//         if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
//             // oled_off(); // causes flicker because the oled state is synced from the master half
//         } else {
//             if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
//                 anim_timer = timer_read32();
//                 animation_phase();
//             }
//         }
//     }
// }

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        print_status();
    // } else {
    //     render_anim();
    //     oled_set_cursor(1,12);
    //     oled_write_P(PSTR("WPM"), false);
    //     oled_set_cursor(1,13);
    //     oled_write(get_u8_str(get_current_wpm(), '0'), false);
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        // case KC_CUT:
        //     // may be better to use Shift+Del to work anywhere (e.g. linux terminal)
        //     // need to test on macOS
        //     if (record->event.pressed) {
        //         // cmd on macOS but CW_TOGG swaps this
        //         register_mods(mod_config(MOD_LCTL));
        //         register_code(KC_X);
        //     } else {
        //         unregister_mods(mod_config(MOD_LCTL));
        //         unregister_code(KC_X);
        //     }
        //     return false;
        //     break;
        // case KC_COPY:
        //     // may be better to use Ctrl+Ins to work anywhere (e.g. linux terminal)
        //     // need to test on macOS
        //     if (record->event.pressed) {
        //         register_mods(mod_config(MOD_LCTL));
        //         register_code(KC_C);
        //     } else {
        //         unregister_mods(mod_config(MOD_LCTL));
        //         unregister_code(KC_C);
        //     }
        //     return false;
        //     break;
        // case KC_PASTE:
        //     // may be better to use Shift+Ins to work anywhere (e.g. linux terminal)
        //     // need to test on macOS
        //     if (record->event.pressed) {
        //         register_mods(mod_config(MOD_LCTL));
        //         register_code(KC_V);
        //     } else {
        //         unregister_mods(mod_config(MOD_LCTL));
        //         unregister_code(KC_V);
        //     }
        //     return false;
        //     break;
        case KC_UNDO:
            if (record->event.pressed) {
                // cmd on macOS but CW_TOGG swaps this
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
            break;
        case KC_AGIN:
            if (keymap_config.swap_lctl_lgui) {
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LCTL | MOD_LSFT));
                    register_code(KC_Z);
                } else {
                    unregister_mods(mod_config(MOD_LCTL | MOD_LSFT));
                    unregister_code(KC_Z);
                }
            } else {
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_Y);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_Y);
                }
            }
            return false;
            break;

    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

#endif

#ifdef POINTING_DEVICE_ENABLE

static uint32_t       last_mouse_activity = 0;
static report_mouse_t last_mouse_report   = {0};
static bool           trackball_scrolling = false;

// void pointing_device_init_user(void) {
//     set_auto_mouse_layer(_BUTTON);
//     set_auto_mouse_enable(true);
// }

report_mouse_t smooth_mouse_movement(report_mouse_t mouse_report) {

    mouse_report.x = ease8InOutApprox(lerp8by8(last_mouse_report.x, mouse_report.x, 0.5));
    mouse_report.y = ease8InOutApprox(lerp8by8(last_mouse_report.y, mouse_report.y, 0.5));

    return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    if (has_mouse_report_changed(&last_mouse_report, &mouse_report)) {
        last_mouse_activity = timer_read32();
        memcpy(&last_mouse_report, &mouse_report, sizeof(mouse_report));
    }

    mouse_report = smooth_mouse_movement(mouse_report);

    if (trackball_scrolling) {
        mouse_report.h = -0.2*mouse_report.x;
        mouse_report.v = 0.2*mouse_report.y;
        mouse_report.x = mouse_report.y = 0;
    }

    return mouse_report;
}

layer_state_t layer_state_set_user(layer_state_t layer_state) {

    switch (get_highest_layer(layer_state)) {
        case _NAV:
        case _MOUSE:
            // set_auto_mouse_enable(false);
            trackball_scrolling = true;
            break;
        default:
            // set_auto_mouse_enable(true);
            trackball_scrolling = false;
    }

    return layer_state;
}

#endif
