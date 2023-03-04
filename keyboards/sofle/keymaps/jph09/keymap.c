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
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST,
    _MOUSE,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_COLEMAK,
    KC_LOWER,
    KC_RAISE,
    KC_MOUSE,
    KC_PRVWD,
    KC_NXTWD,
    KC_LSTART,
    KC_LEND,
    KC_TOP,
    KC_BOTTOM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCtrl |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  | RCtrl|
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |  \   |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |  #   |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            | LGUI | LAlt |LOWER |Space | / Tab  /        \ BKSP \  |Enter |RAISE | RAlt | RGUI |
 *            |      |      |      |LShift|/      /          \      \ |Rshift|      |      |      |
 *             `---------------------------------'            '------''---------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5,                            KC_6, KC_7, KC_8, KC_9, KC_0,  KC_MINS, \
  KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T,                            KC_Y, KC_U, KC_I, KC_O, KC_P,  KC_QUOT, \
  KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G,                            KC_H, KC_J, KC_K, KC_L, KC_SCLN,  KC_RCTL, \
  KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE,          XXXXXXX, KC_N, KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_NUHS, \
    KC_LGUI, KC_LALT, KC_LOWER, LSFT_T(KC_SPC), KC_TAB,   KC_BSPC, RSFT_T(KC_ENT), KC_RAISE, KC_RALT, KC_RGUI \
),
/*
 * COLEMAK Mod-DH
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Y  |   ;  |  '   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LCtrl|   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  | RCtrl|
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * |  \   |   Z  |   X  |   C  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |  #   |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            | LGUI | LAlt |LOWER |Space | / Tab  /        \ BKSP \  |Enter |RAISE | RAlt | Del  |
 *            |      |      |      |LShift|/      /          \      \ |Rshift|      |      |      |
 *             `---------------------------------'            '------''---------------------------'
 */
[_COLEMAK] = LAYOUT( \
  KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5,                            KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_ESC,  KC_Q, KC_W, KC_F, KC_P, KC_B,                            KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, KC_QUOT, \
  KC_LCTL, KC_A, KC_R, KC_S, KC_T, KC_G,                            KC_M, KC_N, KC_E,    KC_I,   KC_O,    KC_RCTL, \
  KC_NUBS, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_MUTE,          XXXXXXX, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NUHS, \
    KC_LGUI, KC_LALT, KC_LOWER, LSFT_T(KC_SPC), KC_TAB,   KC_BSPC, RSFT_T(KC_ENT), KC_RAISE, KC_RALT, KC_RGUI \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   "  |   £  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | MOUSE|   -  |   +  |   =  |   {  |   }  |-------|    |-------|   [  |   ]  |   ~  |   .  |   /  |   #  |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            |      |      |      |      | /      /        \      \  |      |ADJUST|      |      |
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *             `---------------------------------'            '------''---------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
  _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, \
  KC_MOUSE, KC_MINS, KC_PLUS, KC_EQL,  KC_LCBR, KC_RCBR, _______,    _______, KC_LBRC, KC_RBRC, S(KC_NUHS), KC_DOT, KC_SLSH, KC_NUHS, \
                   _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Menu | Del  | PScr | Ins  |      |                    | CLeft| PgDn | PgUp |CRight| CBksp| CDel |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| Left | Down |  Up  | Right| BkSp | Del  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | Undo |  Cut | Copy | Paste|      |-------|    |-------| Home | Top  |Bottom| End  |      |      |
 * `-----------------------------------------/      /      \      \-----------------------------------------'
 *            |      |      |ADJUST|      | /      /        \      \  |      |      |      |      |
 *            |      |      |      |      |/      /          \      \ |      |      |      |      |
 *             `---------------------------------'            '------''---------------------------'
 */
[_RAISE] = LAYOUT( \
   KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                          KC_F7,     KC_F8,   KC_F9,   KC_F10,   KC_F11,     KC_F12, \
  _______, KC_APP,  _______, KC_PSCR, KC_INS,  _______,                        KC_PRVWD,  KC_PGDN, KC_PGUP, KC_NXTWD, C(KC_BSPC), C(KC_DEL), \
  _______, _______, _______, _______, _______, _______,                        KC_LEFT,   KC_DOWN, KC_UP,   KC_RGHT,  KC_BSPC,    KC_DEL, \
  _______, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, _______,  _______,     _______, KC_LSTART, KC_TOP, KC_BOTTOM, KC_LEND, _______,    _______, \
                  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______ \
),
/* ADJUST
 * ,------------------------------------------.                    ,-----------------------------------------.
 * |       |      |      |       |      |      |                   |      |      |      |      |      |      |
 * |-------+------+------+-------+------+------|                   |------+------+------+------+------+------|
 * |QK_BOOT|      |QWERTY|COLEMAK|      |      |                   |      |      |      |      |      |      |
 * |-------+------+------+-------+------+------|                   |------+------+------+------+------+------|
 * |       |      |MACWIN|       | CAPS | CAPWD|-------.   ,-------|      | VOLDO| MUTE | VOLUP|      |      |
 * |-------+------+------+-------+------+------|  MUTE |   |       |------+------+------+------+------+------|
 * |       |      |      |       |      |      |-------|   |-------|      | PREV | PLAY | NEXT |      |      |
 * `------------------------------------------/       /     \      \-----------------------------------------'
 *             |      |      |      |      | /       /       \      \  |      |      |      |      |
 *             |      |      |      |      |/       /         \      \ |      |      |      |      |
 *              `----------------------------------'           '------''---------------------------'
 */
  [_ADJUST] = LAYOUT( \
  _______, _______, _______,   _______,    _______, _______,                     _______, _______, _______, _______, _______, _______, \
  QK_BOOT, _______, KC_QWERTY, KC_COLEMAK, _______, NK_TOGG,                     _______, _______, _______, _______, _______, _______, \
  _______, _______, CG_TOGG,   _______,    KC_CAPS, CW_TOGG,                     _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, \
  _______, _______, _______,   _______,    _______, _______, _______,   _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, \
                   _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______ \

  ),
/* MOUSE
 * ,------------------------------------------.                    ,-----------------------------------------.
 * |       |      |      |       |      |      |                   |      |      |      |      |      |      |
 * |-------+------+------+-------+------+------|                   |------+------+------+------+------+------|
 * |       |      |      |       |      |      |                   |      |      |      |      |      |      |
 * |-------+------+------+-------+------+------|                   |------+------+------+------+------+------|
 * |       |      |      |       |      |      |-------.   ,-------|MS_BT1|MS_BT2|      |      |      |      |
 * |-------+------+------+-------+------+------|  MUTE |   |       |------+------+------+------+------+------|
 * |       |      |      |       |      |      |-------|   |-------|      |      |      |      |      |      |
 * `------------------------------------------/       /     \      \-----------------------------------------'
 *             |      |      |      |      | /       /       \      \  |      |      |      |      |
 *             |      |      |      |      |/       /         \      \ |      |      |      |      |
 *              `----------------------------------'           '------''---------------------------'
 */
  [_MOUSE] = LAYOUT( \
  _______, _______, _______,  _______, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,  _______, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,  _______, _______, _______,                     KC_MS_BTN1, KC_MS_BTN2, _______, _______, _______, _______, \
  _______, _______, _______,  _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, \
               _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______ \
  ),
};

#ifdef OLED_ENABLE

static void print_status_wide(void) {

    oled_write_ln_P(PSTR(""), false);

    // Print current mode
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWERTY "), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR("Colemak-DH "), false);
            break;
        default:
            oled_write_P(PSTR("OTHER "), false);
    }

    if (keymap_config.swap_lctl_lgui) {
        oled_write_P(PSTR("(Mac) "), false);
    } else {
        oled_write_P(PSTR("(Win) "), false);
    }

    oled_write_P(PSTR("\n\n"), false);

    // Current layer indicator
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
        case _QWERTY:
            oled_write_P(PSTR("   "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR(" ^ "), true);
            break;
        case _LOWER:
            oled_write_P(PSTR(" v "), true);
            break;
        case _ADJUST:
            oled_write_P(PSTR(" X "), true);
            break;
        default:
            oled_write_P(PSTR(" ? "), true);
    }

    // Capslock indicator
    led_t led_usb_state = host_keyboard_led_state();
    if (led_usb_state.caps_lock) {
        oled_write_P(PSTR(" CAPS "), true);
    } else {
        oled_write_P(PSTR("      "), false);
    }

}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_left()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_270;
    }
}


/* Animation bit by j-inc https://github.com/qmk/qmk_firmware/tree/master/keyboards/kyria/keymaps/j-inc */
// WPM-responsive animation stuff here
#define IDLE_FRAMES 1
#define IDLE_SPEED 40 // below this wpm value your animation will idle

// #define PREP_FRAMES 1 // uncomment if >1

#define TAP_FRAMES 2
#define TAP_SPEED 60 // above this wpm value typing animation to triggere

#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
// #define SLEEP_TIMER 60000 // should sleep after this period of 0 wpm, needs fixing
#define ANIM_SIZE 320 // number of bytes in array, minimize for adequate firmware size, max is 1024

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t current_idle_frame = 0;
// uint8_t current_prep_frame = 0; // uncomment if PREP_FRAMES >1
uint8_t current_tap_frame = 0;

// Implementation credit j-inc(/James Incandenza), pixelbenny, and obosob.
// Bongo cat images changed and adapted for sofle keyboard oled size.
// Original gif can be found here: https://www.pixilart.com/art/bongo-cat-bd2a8e9323aa705
static void render_anim(void) {
    static const char PROGMEM idle[IDLE_FRAMES][ANIM_SIZE] = {
        {
        0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0x03, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00,
        0xe1, 0x1e, 0x00, 0xc0, 0xbc, 0x83, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x3c, 0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xe0, 0x1f,
        0x01, 0xc0, 0x3c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x31, 0x05, 0x41, 0x12, 0x04,
        0x00, 0x00, 0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0, 0x3f, 0x03, 0x80,
        0x78, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x03, 0x05,
        0x00, 0x00, 0xf0, 0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80, 0x78, 0x07,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xe0, 0x1e, 0x01, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x07, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0xf0, 0x0f, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x18, 0x60, 0x80, 0x00, 0x00, 0xe1, 0x1e, 0x01, 0xf0, 0x8f, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
        0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19,
        0x19, 0x41, 0x0a, 0x22, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18,
        0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
        0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x70, 0x80,
        0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02, 0x01,
        }
    };
    static const char PROGMEM tap[TAP_FRAMES][ANIM_SIZE] = {
        {
        0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0xff, 0xff, 0xff, 0x7c, 0x70, 0x40, 0x40,
        0x61, 0x5e, 0x80, 0xc0, 0xbc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x3c, 0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0f, 0x3f, 0xf8, 0xf0, 0xf0, 0x20,
        0x40, 0x80, 0x80, 0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0, 0x3f, 0x03, 0x80,
        0x78, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04,
        0x00, 0x00, 0xf0, 0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80, 0x78, 0x07,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xe0, 0x1e, 0x01, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x07, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0x00, 0xf0, 0x0f, 0x80, 0x78, 0x07, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x18, 0x60, 0x80, 0x00, 0x00, 0xe1, 0x1e, 0x01, 0xf0, 0x8f, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
        0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x19,
        0x19, 0x41, 0x0a, 0x22, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18,
        0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
        0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x70, 0x80,
        0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02, 0x01,
        },
        {
        0x00, 0xc0, 0x3e, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xfc, 0x03, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00,
        0xe1, 0x1e, 0x00, 0xc0, 0xbc, 0x83, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x3c, 0x03, 0x00, 0x00, 0x00, 0x80, 0x78, 0x87, 0x00, 0x03, 0x0c, 0x30, 0xc0, 0x00, 0xe0, 0x1f,
        0x01, 0xc0, 0x3c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x31, 0x05, 0x41, 0x12, 0x04,
        0x00, 0x00, 0x00, 0x00, 0xf8, 0x87, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0xc0, 0x3f, 0x03, 0x80,
        0x78, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x03, 0x05,
        0x00, 0x00, 0xf0, 0xcf, 0x00, 0x01, 0x06, 0x18, 0x60, 0x80, 0x80, 0x79, 0x07, 0x80, 0x78, 0x07,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xe0, 0xfe, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 0x00, 0xf9, 0x07, 0x80, 0x78, 0x07, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0xc0, 0x2c, 0x32, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x07, 0x03, 0x0f, 0x3f, 0xff, 0x03, 0x01, 0x03, 0x07, 0x18, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x18, 0x60, 0x80, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3c, 0x00, 0x00, 0x00, 0x00,
        0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x08, 0x09, 0x0e, 0x0e, 0x01, 0xf3, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x18,
        0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x09, 0x70, 0x80,
        0x00, 0x00, 0xf0, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x02, 0x01
        },
    };

    //assumes 1 frame prep stage
    void animation_phase(void) {
        if(get_current_wpm() <=IDLE_SPEED){
            oled_write_raw_P(idle[0], ANIM_SIZE);
         }
         if(get_current_wpm() >=TAP_SPEED){
             current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
             oled_write_raw_P(tap[abs((TAP_FRAMES-1)-current_tap_frame)], ANIM_SIZE);
         }
    }
    if(get_current_wpm() != 000) {
        oled_on(); // not essential but turns on animation OLED with any alpha keypress
        if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            // oled_off(); // causes flicker because the oled state is synced from the master half
        } else {
            if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        print_status_wide();
    } else {
        render_anim();
        oled_set_cursor(1,12);
        oled_write_P(PSTR("WPM"), false);
        oled_set_cursor(1,13);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_MOUSE:
            if (record->event.pressed) {
                layer_on(_MOUSE);
            } else {
                layer_off(_MOUSE);
            }
            return false;
        case KC_PRVWD:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_LEFT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                }
            }
            break;
        case KC_NXTWD:
             if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LALT));
                    register_code(KC_RIGHT);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LALT));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                }
            }
            break;
        case KC_LSTART:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                     //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_LEFT);
                } else {
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_LEND:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    //CMD-arrow on Mac, but we have CTL and GUI swapped
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_RIGHT);
                } else {
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_RIGHT);
                } else {
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_TOP:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_UP);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_HOME);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_LEFT);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_HOME);
                }
            }
            break;
        case KC_BOTTOM:
            if (record->event.pressed) {
                if (keymap_config.swap_lctl_lgui) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_DOWN);
                } else {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_END);
                }
            } else {
                if (keymap_config.swap_lctl_lgui) {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_DOWN);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_END);
                }
            }
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
            break;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
            break;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
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
    }

    return mouse_report;
}

layer_state_t layer_state_set_user(layer_state_t layer_state) {

    switch (get_highest_layer(layer_state)) {
        case _LOWER:
        case _RAISE:
        case _ADJUST:
            trackball_scrolling = true;
            break;
        default:
            trackball_scrolling = false;
    }

    return layer_state;
}

#endif