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
    _QWE,
    _TAP,
    _NAV,
    _MOU,
    _MED,
    _NUM,
    _SYM,
    _FUN,
    _BTN,
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
    TD_QWE,
    TD_TAP,
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
        default_layer_set((default_layer_state & ((layer_state_t)1<<_TAP)) | ((layer_state_t)1<<_BASE));
        eeconfig_update_default_layer(default_layer_state);
    }
};

void tap_dance_layer_qwerty(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((default_layer_state & ((layer_state_t)1<<_TAP)) | ((layer_state_t)1<<_QWE));
        eeconfig_update_default_layer(default_layer_state);
    }
};

void tap_dance_layer_tap(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_xor((layer_state_t)1 << _TAP);
        eeconfig_update_default_layer(default_layer_state);
    }
};

void tap_dance_layer_left(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        switch (get_highest_layer(default_layer_state | layer_state)) {
            case _NAV:
            case _NUM:
                default_layer_set((layer_state_t)1 << _NUM);
                break;
            case _MOU:
            case _SYM:
                default_layer_set((layer_state_t)1 << _SYM);
                break;
            case _MED:
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
            case _MOU:
            case _SYM:
                default_layer_set((layer_state_t)1 << _MOU);
                break;
            case _MED:
            case _FUN:
                default_layer_set((layer_state_t)1 << _MED);
                break;
        }
    }
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN (tap_dance_boot),
    [TD_BASE] = ACTION_TAP_DANCE_FN (tap_dance_layer_base),
    [TD_QWE] = ACTION_TAP_DANCE_FN (tap_dance_layer_qwerty),
    [TD_TAP] = ACTION_TAP_DANCE_FN (tap_dance_layer_tap),
    [TD_LEFT] = ACTION_TAP_DANCE_FN (tap_dance_layer_left),
    [TD_RIGHT] = ACTION_TAP_DANCE_FN (tap_dance_layer_right),
};

/* Transparen Mod Taps */
#define MT_LG MT(MOD_LGUI, KC_TRANSPARENT)
#define MT_LA MT(MOD_LALT, KC_TRANSPARENT)
#define MT_LC MT(MOD_LCTL, KC_TRANSPARENT)
#define MT_LS MT(MOD_LSFT, KC_TRANSPARENT)
#define MT_RG MT(MOD_RGUI, KC_TRANSPARENT)
#define MT_RA MT(MOD_RALT, KC_TRANSPARENT)
#define MT_RC MT(MOD_RCTL, KC_TRANSPARENT)
#define MT_RS MT(MOD_RSFT, KC_TRANSPARENT)

/* Extra Mod Taps */
#define MTS_LPRN LSFT_T(KC_LPRN)
#define MTS_RPRN RSFT_T(KC_RPRN)
#define MTC_LCBR LCTL_T(KC_LCBR)
#define MTC_RCBR RCTL_T(KC_RCBR)

/* Transparen Layer Taps */
#define LT_NAV LT(_NAV, KC_TRANSPARENT)
#define LT_MOU LT(_MOU, KC_TRANSPARENT)
#define LT_MED LT(_MED, KC_TRANSPARENT)
#define LT_NUM LT(_NUM, KC_TRANSPARENT)
#define LT_SYM LT(_SYM, KC_TRANSPARENT)
#define LT_FUN LT(_FUN, KC_TRANSPARENT)
#define LT_BTN LT(_BTN, KC_TRANSPARENT)

/* Override shifted keys */
const key_override_t ko_capsword = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);
const key_override_t ko_scln = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t ko_cln = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, S(KC_SCLN));
const key_override_t ko_non_us_quot = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, S(KC_2));
const key_override_t ko_non_us_two = ko_make_basic(MOD_MASK_SHIFT, KC_2, S(KC_QUOT));
const key_override_t ko_non_us_three = ko_make_basic(MOD_MASK_SHIFT, KC_3, KC_NUHS);
const key_override_t **key_overrides = (const key_override_t *[]){
    &ko_capsword,
    &ko_scln,
    &ko_cln,
    &ko_non_us_quot,
    &ko_non_us_two,
    &ko_non_us_three,
    NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK Mod-DH */
[_BASE] = LAYOUT( \
  KC_GRV,   KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                     KC_6,    KC_7,   KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_LBRC,  KC_Q,  KC_W,  KC_F,  KC_P,  KC_B,                     KC_J,    KC_L,   KC_U,    KC_Y,   KC_QUOT, KC_RBRC, \
  KC_LSFT,  KC_A,  KC_R,  KC_S,  KC_T,  KC_G,                     KC_M,    KC_N,   KC_E,    KC_I,   KC_O,    KC_RSFT, \
  KC_LCTL,  KC_Z,  KC_X,  KC_C,  KC_D,  KC_V, KC_MUTE,   XXXXXXX, KC_K,    KC_H,   KC_COMM, KC_DOT, KC_SLSH, KC_RCTL, \
            KC_LGUI, KC_LALT, KC_ESC, KC_SPC, KC_TAB,     KC_ENT, KC_BSPC, KC_DEL, KC_RALT, MO(_FUN) \
),

/* QWERTY */
[_QWE] = LAYOUT( \
  KC_GRV,   KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                     KC_6, KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_LBRC,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                     KC_Y, KC_U,  KC_I,    KC_O,   KC_P,    KC_RBRC, \
  KC_LSFT,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                     KC_H, KC_J,  KC_K,    KC_L,   KC_QUOT, KC_RSFT, \
  KC_LCTL,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B, KC_MUTE,   XXXXXXX, KC_N, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RCTL, \
            KC_LGUI, KC_LALT, KC_ESC, KC_SPC, KC_TAB,     KC_ENT, KC_BSPC, KC_DEL, KC_RALT, MO(_FUN) \
),

/* mod/taps */
[_TAP] = LAYOUT( \
  _______,  _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,  \
  _______,  _______, MT_RA,   _______, _______, _______,                     _______, _______, _______, MT_RA,   _______, _______,  \
  MTS_LPRN, MT_LG,   MT_LA,   MT_LC,   MT_LS,   _______,                     _______, MT_RS,   MT_RC,   MT_LA,   MT_RG,   MTS_RPRN, \
  MTC_LCBR, LT_BTN,  _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, LT_BTN,  MTC_RCBR, \
                _______, _______, LT_MED,  LT_NAV,  LT_MOU,              LT_SYM,  LT_NUM,  LT_FUN,  _______, KC_RGUI \
),

[_NAV] = LAYOUT( \
  XXXXXXX, XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX,      XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
  XXXXXXX, TD(TD_BOOT), TD(TD_TAP), TD(TD_QWE),    TD(TD_BASE),  CG_TOGG,                     KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,   XXXXXXX, \
  XXXXXXX, KC_LGUI,     KC_LALT,    KC_LCTL,       KC_LSFT,      CW_TOGG,                     CW_TOGG, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX, \
  XXXXXXX, MO(_BTN),    XXXXXXX,    TD(TD_LEFT),   TD(TD_RIGHT), XXXXXXX, KC_MUTE,   XXXXXXX, KC_AGIN, S(KC_INS), C(KC_INS), S(KC_DEL),  KC_UNDO, XXXXXXX, \
                                XXXXXXX, XXXXXXX, _______, _______, _______,          KC_ENT, KC_BSPC, KC_DEL, XXXXXXX, XXXXXXX \
),

[_MOU] = LAYOUT( \
  XXXXXXX, XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX,      XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, TD(TD_BOOT), TD(TD_TAP), TD(TD_QWE),    TD(TD_BASE),  CG_TOGG,                     XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, \
  XXXXXXX, KC_LGUI,     KC_LALT,    KC_LCTL,       KC_LSFT,      CW_TOGG,                     XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, \
  XXXXXXX, MO(_BTN),    XXXXXXX,    TD(TD_LEFT),   TD(TD_RIGHT), XXXXXXX, KC_MUTE,   XXXXXXX, KC_AGIN, S(KC_INS), C(KC_INS), S(KC_DEL),  KC_UNDO, XXXXXXX, \
                                      XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN1, KC_BTN2,          KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX \
),

[_MED] = LAYOUT( \
  XXXXXXX, XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX,      XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, TD(TD_BOOT), TD(TD_TAP), TD(TD_QWE),    TD(TD_BASE),  CG_TOGG,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_LGUI,     KC_LALT,    KC_LCTL,       KC_LSFT,      CW_TOGG,                     KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX, \
  XXXXXXX, MO(_BTN),    XXXXXXX,    TD(TD_LEFT),   TD(TD_RIGHT), XXXXXXX, KC_MUTE,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                      XXXXXXX, XXXXXXX, _______, _______, _______,          KC_MSTP, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX \
),

[_NUM] = LAYOUT( \
  XXXXXXX, KC_BSPC,    KC_SLSH, KC_ASTR, KC_PLUS, KC_MINS,                      XXXXXXX, XXXXXXX,     XXXXXXX,       XXXXXXX,    XXXXXXX,     XXXXXXX,  \
  KC_TAB,  KC_LBRC,    KC_7,    KC_8,    KC_9,    KC_RBRC,                      CG_TOGG, TD(TD_BASE), TD(TD_QWE),    TD(TD_TAP), TD(TD_BOOT), XXXXXXX, \
  KC_ENT,  S(KC_COMM), KC_4,    KC_5,    KC_6,    KC_EQL,                       CW_TOGG, KC_RSFT,     KC_RCTL,       KC_LALT,    KC_RGUI,     XXXXXXX, \
  XXXXXXX, KC_GRV,     KC_1,    KC_2,    KC_3,    KC_NUBS, KC_MUTE,    XXXXXXX, XXXXXXX, TD(TD_LEFT), TD(TD_RIGHT),  KC_RALT,    MO(_BTN),    XXXXXXX, \
                     KC_TAB, KC_ENTER, KC_DOT, KC_0,    KC_MINS,          _______, _______, _______, XXXXXXX, XXXXXXX \
),

[_SYM] = LAYOUT( \
  XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,    XXXXXXX,     XXXXXXX, \
  XXXXXXX,   S(KC_LBRC), S(KC_7), S(KC_8),    S(KC_9), S(KC_RBRC),                     CG_TOGG, TD(TD_BASE),   TD(TD_QWE),    TD(TD_TAP), TD(TD_BOOT), XXXXXXX, \
  XXXXXXX,   S(KC_DOT),  S(KC_4), S(KC_5),    S(KC_6), S(KC_EQL),                      CW_TOGG, KC_RSFT,       KC_RCTL,       KC_LALT,    KC_RGUI,     XXXXXXX, \
  XXXXXXX,   S(KC_NUHS), S(KC_1), S(KC_QUOT), KC_NUHS, S(KC_NUBS), KC_MUTE,   XXXXXXX, XXXXXXX, TD(TD_LEFT),   TD(TD_RIGHT),  KC_RALT,    MO(_BTN),    XXXXXXX, \
                  XXXXXXX, XXXXXXX, S(KC_3), S(KC_0), S(KC_MINS),          _______, _______, _______, XXXXXXX, XXXXXXX \
),

[_FUN] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX,     XXXXXXX,       XXXXXXX,    XXXXXXX,     XXXXXXX, \
  XXXXXXX, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                     CG_TOGG, TD(TD_BASE), TD(TD_QWE),    TD(TD_TAP), TD(TD_BOOT), XXXXXXX, \
  XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,                     CW_TOGG, KC_RSFT,     KC_RCTL,       KC_LALT,    KC_RGUI,     XXXXXXX, \
  XXXXXXX, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, KC_MUTE,   XXXXXXX, XXXXXXX, TD(TD_LEFT), TD(TD_RIGHT),  KC_RALT,    MO(_BTN),    XXXXXXX, \
                  XXXXXXX, XXXXXXX, KC_APP, KC_SPC, KC_TAB,          _______, _______, _______, XXXXXXX, XXXXXXX \
),

[_BTN] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   XXXXXXX,   XXXXXXX,                       XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_UNDO, S(KC_DEL),  C(KC_INS), S(KC_INS), KC_AGIN,                       KC_AGIN, S(KC_INS), C(KC_INS), S(KC_DEL), KC_UNDO, XXXXXXX, \
  XXXXXXX, KC_LGUI, KC_LALT,    KC_LCTL,   KC_LSFT,   CW_TOGG,                       CW_TOGG, KC_RSFT,   KC_RCTL,   KC_RALT,   KC_RGUI, XXXXXXX, \
  XXXXXXX, KC_UNDO, S(KC_DEL),  C(KC_INS), S(KC_INS), KC_AGIN, KC_MUTE,     XXXXXXX, KC_AGIN, S(KC_INS), C(KC_INS), S(KC_DEL), KC_UNDO, XXXXXXX, \
                      XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN1, KC_BTN2,             KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX \
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_LG:
        case MT_LA:
        case MT_LC:
        case MT_LS:
        case MT_RG:
        case MT_RA:
        case MT_RC:
        case MT_RS:
        case LT_NAV:
        case LT_MOU:
        case LT_MED:
        case LT_NUM:
        case LT_SYM:
        case LT_FUN:
        case LT_BTN:
            if (record->tap.count && record->event.pressed) {
                layer_state_t alpha_layer = get_highest_layer(default_layer_state & (((layer_state_t)1<<_BASE) | ((layer_state_t)1<<_QWE))); // get current alpha layout
                uint16_t tap_keycode = keymap_key_to_keycode(alpha_layer, record->event.key); // get alpha keycode
                tap_code16(tap_keycode); // send keycode on tap
                return false;
            }
            break;
        case MTS_LPRN:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LPRN);
                return false;
            }
            break;
        case MTS_RPRN:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_RPRN);
                return false;
            }
            break;
        case MTC_LCBR:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_LCBR);
                return false;
            }
            break;
        case MTC_RCBR:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_RCBR);
                return false;
            }
            break;

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

#ifdef OLED_ENABLE

static void print_status(void) {

    oled_set_cursor(1, 1);

    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(PSTR("Mac"), false);
    } else {
        oled_write_P(PSTR("Win"), false);
    }

    oled_set_cursor(5, 1);

    if ( default_layer_state & ((layer_state_t)1<<_QWE) ) {
        oled_write_ln_P(PSTR("QWERTY"), false);
    } else {
        oled_write_ln_P(PSTR("Colemak-DH"), false);
    }

    oled_set_cursor(1, 3);

    switch (get_highest_layer(default_layer_state | layer_state)) {
        case _BASE:
        case _QWE:
        case _TAP:
            oled_write_P(PSTR("   "), false);
            break;
        case _NAV:
            oled_write_P(PSTR("NAV"), true);
            break;
        case _MOU:
            oled_write_P(PSTR("MOU"), true);
            break;
        case _MED:
            oled_write_P(PSTR("MED"), true);
            break;
        case _NUM:
            oled_write_P(PSTR("NUM"), true);
            break;
        case _SYM:
            oled_write_P(PSTR("SYM"), true);
            break;
        case _FUN:
            oled_write_P(PSTR("FUN"), true);
            break;
        case _BTN:
            oled_write_P(PSTR("BTN"), true);
            break;
        default:
            oled_write_P(PSTR("???"), true);

    }

    oled_set_cursor(12, 3);

    // Capslock indicator
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR("CAPS"), led_usb_state.caps_lock);

    oled_set_cursor(17, 3);
    oled_write_P(PSTR("TAP"), !(default_layer_state & (layer_state_t)1<<_TAP));
}

// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     return OLED_ROTATION_270;
// }

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
    if (is_keyboard_master()) {
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

#ifdef POINTING_DEVICE_ENABLE

static bool           trackball_scrolling = false;

// static uint32_t       last_mouse_activity = 0;
// static report_mouse_t last_mouse_report   = {0};

// report_mouse_t smooth_mouse_movement(report_mouse_t mouse_report) {

//     mouse_report.x = ease8InOutApprox(lerp8by8(last_mouse_report.x, mouse_report.x, 0.5));
//     mouse_report.y = ease8InOutApprox(lerp8by8(last_mouse_report.y, mouse_report.y, 0.5));

//     return mouse_report;
// }

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    // if (has_mouse_report_changed(&last_mouse_report, &mouse_report)) {
    //     last_mouse_activity = timer_read32();
    //     memcpy(&last_mouse_report, &mouse_report, sizeof(mouse_report));
    // }

    // mouse_report = smooth_mouse_movement(mouse_report);

    if (trackball_scrolling) {
        mouse_report.h = -0.2*mouse_report.x;
        mouse_report.v = 0.2*mouse_report.y;
        mouse_report.x = mouse_report.y = 0;
    }

    return mouse_report;
}

layer_state_t layer_state_set_user(layer_state_t layer_state) {
    // scroll with trackball if _NAV layer is on
    trackball_scrolling = (bool)(layer_state & ((layer_state_t)1 << _NAV));
    return layer_state;
}

#endif
