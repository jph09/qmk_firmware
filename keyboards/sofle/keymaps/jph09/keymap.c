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
    _NUM,
    _NAV,
    _FUN,
    _MOU,
};

 enum custom_keycodes {
//     KC_UND = SAFE_RANGE,
//     KC_RDO
//     KC_CPY,
//     KC_PST,
     KC_SCROLLING,
 };

/* Safety Tap Dance on special functions */
enum {
    TD_BOOT = 0,
};

void tap_dance_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        reset_keyboard();
    }
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN (tap_dance_boot),
};

/* Override shifted keys */
const key_override_t ko_capsword = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);
const key_override_t ko_scln = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t ko_cln = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, S(KC_SCLN));
const key_override_t ko_non_us_quot = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, S(KC_2));
const key_override_t **key_overrides = (const key_override_t *[]){
    &ko_capsword,
    &ko_scln,
    &ko_cln,
    &ko_non_us_quot,
    NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK Mod-DH */
[_BASE] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                        KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, XXXXXXX, \
  XXXXXXX, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                        KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    XXXXXXX, \
  XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_MUTE,   XXXXXXX, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX, \
                 XXXXXXX, XXXXXXX, KC_MINS, OSL(_NAV),  KC_SPC,    OSM(MOD_LSFT),  OSL(_NUM), XXXXXXX, XXXXXXX, XXXXXXX \
),

[_NUM] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                        _______,    _______, _______, _______, _______, _______, \
  _______, KC_GRV,  KC_EXLM, KC_DQUO, KC_CIRC, KC_AMPR,                        KC_EQL,     KC_MINS, KC_PLUS, KC_ASTR, KC_NUBS, _______, \
  _______, KC_7,    KC_5,    KC_3,    KC_1,    KC_9,                           KC_8,       KC_0,    KC_2,    KC_4,    KC_6,    _______, \
  _______, KC_PIPE, KC_PERC, KC_HASH, KC_DLR,  RALT(KC_4), _______,   _______, S(KC_NUBS), KC_NUHS, KC_COMM, KC_DOT,  KC_SLSH, _______, \
                    _______, _______, KC_UNDS, _______,    KC_TAB,    KC_ENT,  _______, _______, _______, _______ \
),

[_NAV] = LAYOUT( \
  _______, _______,       _______,       _______,       _______,       _______,                      _______, _______, _______, _______, _______,  _______, \
  _______, KC_LABK,       KC_LCBR,       KC_LBRC,       KC_LPRN,       KC_AGIN,                      KC_UNDO, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   _______, \
  _______, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), KC_APP,                       KC_TAB,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, \
  _______, KC_RABK,       KC_RCBR,       KC_RBRC,       KC_RPRN,       KC_SPC,  _______,    _______, KC_SPC,  KC_ESC,  KC_BSPC, KC_DEL,  KC_INS,   _______, \
                                           _______, _______,  KC_UNDS, _______, _______,    KC_ENT,  _______, XXXXXXX, XXXXXXX, XXXXXXX \
),

[_FUN] = LAYOUT( \
  _______, _______,       _______,       _______,       _______,       _______,                      _______, _______,       _______,       _______,       _______,       _______, \
  _______, KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5,                        KC_F6,   KC_F7,         KC_F8,         KC_F9,         KC_F10,        _______, \
  _______, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), CW_TOGG,                      KC_PAUS, OSM(MOD_RSFT), OSM(MOD_RCTL), OSM(MOD_RALT), OSM(MOD_RGUI), _______, \
  _______, KC_PSCR,       KC_SCROLLING,  KC_MS_BTN2,    KC_MS_BTN1,    KC_SCRL, _______,    _______, KC_MUTE, KC_VOLD,       KC_VOLU,       KC_F11,        KC_F12,        _______, \
                                        _______, _______, TD(TD_BOOT), _______, CG_TOGG,    _______, _______, _______, _______, _______ \
),

[_MOU] = LAYOUT( \
  _______, _______, _______,      _______,    _______,    _______,                       _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,      _______,    _______,    _______,                       _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,      _______,    _______,    _______,                       _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_SCROLLING, KC_MS_BTN2, KC_MS_BTN1, _______, _______,     _______, _______, _______, _______, _______, _______, _______, \
                               _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______ \
),

};

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

        case KC_SCROLLING:
            // TODO: Toggle trackball scrolling
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
    oled_write_ln_P(PSTR("Colemak-DH"), false);
    

    oled_set_cursor(1, 3);

    switch (get_highest_layer(default_layer_state | layer_state)) {
        case _BASE:
            oled_write_P(PSTR("   "), false);
            break;
        case _NAV:
            oled_write_P(PSTR("NAV"), true);
            break;
        case _MOU:
            oled_write_P(PSTR("MOU"), true);
            break;
        case _NUM:
            oled_write_P(PSTR("NUM"), true);
            break;
        case _FUN:
            oled_write_P(PSTR("FUN"), true);
            break;
        default:
            oled_write_P(PSTR("???"), true);

    }

    oled_set_cursor(12, 3);

    // Capslock indicator
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR("CAPS"), led_usb_state.caps_lock);

}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_270;
    }
}

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
    } else {
        // render_anim();
        oled_set_cursor(1,12);
        oled_write_P(PSTR("WPM"), false);
        oled_set_cursor(1,13);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);
    }
    return false;
}
#endif

#ifdef POINTING_DEVICE_ENABLE

static bool           trackball_scrolling = false;

static uint32_t       last_mouse_activity = 0;
static report_mouse_t last_mouse_report   = {0};

report_mouse_t smooth_mouse_movement(report_mouse_t mouse_report) {

    mouse_report.x = ease8InOutApprox(lerp8by8(last_mouse_report.x, mouse_report.x, 0.5));
    mouse_report.y = ease8InOutApprox(lerp8by8(last_mouse_report.y, mouse_report.y, 0.5));

    return mouse_report;
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOU); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
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

#endif
