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
    _COLEMAKDH = 0,
    _QWERTY,
    _TAP,
    _NUM_NAV,
    _SYM_MOU,
    _FUN_MED,
    _BUTTON_L,
    _BUTTON_R,
};

// enum custom_keycodes {
//     LT_NAV = SAFE_RANGE,
//     LT_MOU,
//     LT_MED,
//     LT_NUM,
//     LT_SYM,
//     LT_FUN,
// //     KC_UND,
// //     KC_RDO
// //     KC_CPY,
// //     KC_PST,
// };

/* Safety Tap Dance on special functions */
enum {
    TD_BOOT = 0,
    TD_LAYOUT,
    TD_TAP,
    TD_CG,
    TD_THIS,
    TD_THAT,
};

void tap_dance_boot(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            soft_reset_keyboard();
            break;
        case 3:
            reset_keyboard();
            break;
    }
};

void tap_dance_layout(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 2:
            // For two taps, set Colemak-DH and preserve current tap layer state
            default_layer_set(default_layer_state & (layer_state_t)1 << _TAP | (layer_state_t)1 << _COLEMAKDH);

            // make the alpha layout persistent but with mod taps always enabled after reboot
            eeconfig_update_default_layer((layer_state_t)1 << _TAP | (layer_state_t)1 << _COLEMAKDH);

            break;
        case 3:
            // For three taps set Qwerty and preserve current tap layer state
            default_layer_set(default_layer_state & (layer_state_t)1 << _TAP | (layer_state_t)1 << _QWERTY);

            // make the alpha layout persistent but with mod taps always enabled after reboot
            eeconfig_update_default_layer((layer_state_t)1 << _TAP | (layer_state_t)1 << _QWERTY);

            break;
    };
};

void tap_dance_tap(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        // toggle tap layer state
        default_layer_set(default_layer_state ^ (layer_state_t)1 << _TAP);
    }
};

void tap_dance_cg(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        // toggle Ctl/GUI swapping i.e. Win/Mac mode
        keymap_config.swap_lalt_lgui = !keymap_config.swap_lalt_lgui;
        keymap_config.swap_ralt_rgui = keymap_config.swap_lalt_lgui;
    }
}

void tap_dance_this_side(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        // lock left hand layer
        // to do
    }
};

void tap_dance_that_side(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        // lock right hand layer
        // to do
    }
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN (tap_dance_boot),
    [TD_LAYOUT] = ACTION_TAP_DANCE_FN (tap_dance_layout),
    [TD_TAP] = ACTION_TAP_DANCE_FN (tap_dance_tap),
    [TD_CG] = ACTION_TAP_DANCE_FN (tap_dance_cg),
    [TD_THIS] = ACTION_TAP_DANCE_FN (tap_dance_this_side),
    [TD_THAT] = ACTION_TAP_DANCE_FN (tap_dance_that_side),
};

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
[_COLEMAKDH] = LAYOUT( \
  KC_GRV,      KC_1, KC_2, KC_3, KC_4, KC_5,                     KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, \
  TD(TD_BOOT), KC_Q, KC_W, KC_F, KC_P, KC_B,                     KC_J, KC_L, KC_U,    KC_Y,   KC_QUOT, KC_SCLN, \
  KC_LSFT,     KC_A, KC_R, KC_S, KC_T, KC_G,                     KC_M, KC_N, KC_E,    KC_I,   KC_O,    KC_RSFT, \
  KC_LCTL,     KC_Z, KC_X, KC_C, KC_D, KC_V, KC_MUTE,   XXXXXXX, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_RCTL, \
          KC_LGUI, KC_LALT, KC_ESC, KC_SPC, KC_TAB,     KC_ENT, KC_BSPC, KC_DEL, KC_RALT, KC_RGUI \
),

/* QWERTY */
[_QWERTY] = LAYOUT( \
  KC_GRV,      KC_1, KC_2, KC_3, KC_4, KC_5,                     KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, \
  TD(TD_BOOT), KC_Q, KC_W, KC_E, KC_R, KC_T,                     KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_SCLN, \
  KC_LSFT,     KC_A, KC_S, KC_D, KC_F, KC_G,                     KC_H, KC_J, KC_K,    KC_L,   KC_QUOT, KC_RSFT, \
  KC_LCTL,     LT_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE,   XXXXXXX, KC_N, KC_M, KC_COMM, KC_DOT, LT_SLSH, KC_RCTL, \
          KC_LGUI, KC_LALT, KC_ESC, KC_SPC, KC_TAB,     KC_ENT, KC_BSPC, KC_DEL, KC_RALT, KC_RGUI \
),

[_TAP] = LAYOUT( \
  _______,         _______,         _______,         _______,         _______,         _______,                   _______, _______,         _______,         _______,         _______,         _______, \
  KC_LCBR,         _______,         _______,         _______,         _______,         _______,                   _______, _______,         _______,         _______,         _______,         KC_RCBR, \
  LSFT_T(KC_LPRN), LGUI_T(KC_TRNS), LALT_T(KC_TRNS), LCTL_T(KC_TRNS), LSFT_T(KC_TRNS), _______,                   _______, RSFT_T(KC_TRNS), RCTL_T(KC_TRNS), LALT_T(KC_TRNS), RGUI_T(KC_TRNS), RSFT_T(KC_RPRN), \
  LCTL_T(KC_LBRC), _______,         _______,         _______,         _______,         _______, _______, _______, _______, _______,         _______,         _______,         _______,         RCTL_T(KC_RBRC), \
                   _______, _______, LT(_FUN_MED, KC_ESC), LT(_NUM_NAV, KC_SPC), LT(_SYM_MOU, KC_TAB),    LT(_SYM_MOU, KC_ENT), LT(_NUM_NAV, KC_BSPC), LT(_FUN_MED, KC_DEL), _______, _______ \
),

[_BUTTON_L] = LAYOUT( \
  XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX,   XXXXXXX,     XXXXXXX,                       _______, _______, _______, _______, _______, _______, \
  TD(TD_BOOT), TD(TD_TAP), TD(TD_LAYOUT), TD(TD_CG), TD(TD_THAT), TD(TD_THIS),                   _______, _______, _______, _______, _______, _______, \
  XXXXXXX,     KC_LGUI,    KC_LALT,       KC_LCTL,   KC_LSFT,     CW_TOGG,                       _______, _______, _______, _______, _______, _______, \
  XXXXXXX,     KC_UNDO,    S(KC_DEL),     C(KC_INS), S(KC_INS),   KC_AGIN, _______,     _______, _______, _______, _______, _______, _______, _______, \
                                       KC_APP, KC_RALT, KC_BTN3, KC_BTN1, KC_BTN2,         _______, _______, _______, _______, _______ \
),

[_BUTTON_R] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                       XXXXXXX,     XXXXXXX,     XXXXXXX,   XXXXXXX,       XXXXXXX,    XXXXXXX, \
  _______, _______, _______, _______, _______, _______,                       TD(TD_THIS), TD(TD_THAT), TD(TD_CG), TD(TD_LAYOUT), TD(TD_TAP), TD(TD_BOOT), \
  _______, _______, _______, _______, _______, _______,                       CW_TOGG,     KC_RSFT,     KC_RCTL,   KC_LALT,       KC_RGUI,    XXXXXXX, \
  _______, _______, _______, _______, _______, _______, _______,     _______, KC_AGIN,     S(KC_INS),   C(KC_INS), S(KC_DEL),     KC_UNDO,    XXXXXXX, \
              _______, _______, _______, _______, _______,              KC_BTN2, KC_BTN1, KC_BTN3, KC_RALT, KC_APP \
),

[_NUM_NAV] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
  XXXXXXX, KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC,                      KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,   XXXXXXX, \
  XXXXXXX, KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,                       CW_TOGG, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX, \
  XXXXXXX, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_NUBS, KC_MUTE,    XXXXXXX, KC_AGIN, S(KC_INS), C(KC_INS), S(KC_DEL),  KC_UNDO, XXXXXXX, \
                    KC_ENTER, KC_TAB, KC_DOT, KC_0, KC_MINS,           KC_ENT, KC_BSPC, KC_DEL, XXXXXXX, XXXXXXX \
),

[_SYM_MOU] = LAYOUT( \
  XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, S(KC_LBRC), S(KC_7), S(KC_8),    S(KC_9), S(KC_RBRC),                     XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, \
  XXXXXXX, S(KC_SCLN), S(KC_4), S(KC_5),    S(KC_6), S(KC_EQL),                      XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, \
  XXXXXXX, S(KC_NUHS), S(KC_1), S(KC_QUOT), S(KC_3), S(KC_NUBS), KC_MUTE,   XXXXXXX, KC_AGIN, S(KC_INS), C(KC_INS), S(KC_DEL),  KC_UNDO, XXXXXXX, \
                        XXXXXXX, XXXXXXX, KC_NUHS, S(KC_0), S(KC_MINS),          KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX \
),

[_FUN_MED] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,                     XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, \
  XXXXXXX, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, KC_MUTE,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                XXXXXXX, XXXXXXX, _______, _______, _______,          KC_MSTP, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX \
),

};

#ifdef OLED_ENABLE

static void print_status_wide(void) {

    oled_write_ln_P(PSTR(""), false);

    // Capslock indicator
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR(" CAPS"), led_usb_state.caps_lock);

    // Print current mode
    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(PSTR(" MAC\n\n"), false);
    } else {
        oled_write_P(PSTR(" WIN\n\n"), false);
    }

    switch (get_highest_layer(default_layer_state ^ (layer_state_t)1<<_TAP)) {
        case _COLEMAKDH:
            oled_write_P(PSTR("COLEMAK-DH "), false);
            break;
        case _QWERTY:
            oled_write_P(PSTR("QWERTY "), false);
            break;
        default:
            oled_write_P(PSTR("OTHER "), true);
    }

    if (default_layer_state ^ (layer_state_t)1<<_TAP) {
        oled_write_P(PSTR("NO MODS"), true);
    }

    // // Show current layer
    // switch (get_highest_layer(default_layer_state | layer_state)) {
    //     case _COLEMAKDH:
    //         oled_write_ln_P(PSTR("BASE"), false);
    //         oled_write_P(PSTR("\n COLEMAK-DH"), false);
    //         break;
    //     case _QWERTY:
    //         oled_write_ln_P(PSTR("BASE"), true);
    //         oled_write_P(PSTR("\n QWERTY"), true);
    //         break;
    //     case _TAP:
    //         oled_write_ln_P(PSTR("TAP"), true);
    //         break;
    //     case _NAV:
    //         oled_write_ln_P(PSTR("NAV"), true);
    //         break;
    //     case _MOUSE:
    //         oled_write_ln_P(PSTR("MOU"), true);
    //         break;
    //     case _MEDIA:
    //         oled_write_ln_P(PSTR("MED"), true);
    //         break;
    //     case _NUM:
    //         oled_write_ln_P(PSTR("NUM"), true);
    //         break;
    //     case _SYM:
    //         oled_write_ln_P(PSTR("SYM"), true);
    //         break;
    //     case _FUN:
    //         oled_write_ln_P(PSTR("FUN"), true);
    //         break;
    //     case _BUTTON:
    //         oled_write_ln_P(PSTR("BTN"), true);
    //         break;
    //     default:
    //         oled_write_ln_P(PSTR("DEF"), true);
    // }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_left()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_270;
    }
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
        print_status_wide();
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
        // TODO need to override all the MT and LT keycodes



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

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_BUTTON);
    set_auto_mouse_enable(true);
}

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
        mouse_report.h = -0.3*mouse_report.x;
        mouse_report.v = 0.3*mouse_report.y;
        mouse_report.x = mouse_report.y = 0;

    // // setting pimoroni trackball led state doesn't work
    // // and causes big lag with split pointing (i.e. trackball
    // // on right half but left is master)
    // pimoroni_trackball_set_rgbw(50,0,0,0);
    // } else {
    //     if (timer_elapsed(last_mouse_activity) < TRACKBALL_LED_TIMEOUT) {
    //         pimoroni_trackball_set_rgbw(0,0,50,0);

    //     } else {
    //         pimoroni_trackball_set_rgbw(0,0,0,0);
    //     }
    }

    return mouse_report;
}

layer_state_t layer_state_set_user(layer_state_t layer_state) {

    switch (get_highest_layer(layer_state)) {
        case _NAV:
        case _MOUSE:
            set_auto_mouse_enable(false);
            trackball_scrolling = true;
            break;
        default:
            set_auto_mouse_enable(true);
            trackball_scrolling = false;
    }

    return layer_state;
}

#endif
