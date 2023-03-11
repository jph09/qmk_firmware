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
    TD_COLEMAKDH,
    TD_QWERTY,
    TD_TAP,
    TD_NAV,
    TD_MOUSE,
    TD_MEDIA,
    TD_NUM,
    TD_SYM,
    TD_FUN,
};

void tap_dance_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        reset_keyboard();
    }
};

void tap_dance_layer_colemakdh(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        // set_single_persistent_default_layer(_COLEMAKDH);
        default_layer_set((layer_state_t)1 << _COLEMAKDH);
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

void tap_dance_layer_nav(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << _NAV);
    }
};

void tap_dance_layer_mouse(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << _MOUSE);
    }
};

void tap_dance_layer_media(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << _MEDIA);
    }
};

void tap_dance_layer_num(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << _NUM);
    }
};

void tap_dance_layer_sym(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << _SYM);
    }
};

void tap_dance_layer_fun(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        default_layer_set((layer_state_t)1 << _FUN);
    }
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN (tap_dance_boot),
    [TD_COLEMAKDH] = ACTION_TAP_DANCE_FN (tap_dance_layer_colemakdh),
    [TD_QWERTY] = ACTION_TAP_DANCE_FN (tap_dance_layer_qwerty),
    [TD_TAP] = ACTION_TAP_DANCE_FN (tap_dance_layer_tap),
    [TD_NAV] = ACTION_TAP_DANCE_FN (tap_dance_layer_nav),
    [TD_MOUSE] = ACTION_TAP_DANCE_FN (tap_dance_layer_mouse),
    [TD_MEDIA] = ACTION_TAP_DANCE_FN (tap_dance_layer_media),
    [TD_NUM] = ACTION_TAP_DANCE_FN (tap_dance_layer_num),
    [TD_SYM] = ACTION_TAP_DANCE_FN (tap_dance_layer_sym),
    [TD_FUN] = ACTION_TAP_DANCE_FN (tap_dance_layer_fun),
};

/* MOD TAP defs for QWERTY */
#define MTG_A LGUI_T(KC_A)
#define MTA_S LALT_T(KC_S)
#define MTC_D LCTL_T(KC_D)
#define MTS_F LSFT_T(KC_F)
#define MTS_J RSFT_T(KC_J)
#define MTC_K RCTL_T(KC_K)
#define MTA_L LALT_T(KC_L)
#define MTA_DOT RALT_T(KC_DOT)
#define MTG_SC RGUI_T(KC_SEMICOLON)

/* MOD TAP defs for COLEMAK-DH */
// #define MTG_A LGUI_T(KC_A) // same as QWERTY
#define MTA_R LALT_T(KC_R)
#define MTC_S LCTL_T(KC_S)
#define MTS_T LSFT_T(KC_T)
#define MTS_N RSFT_T(KC_N)
#define MTC_E RCTL_T(KC_E)
#define MTA_I LALT_T(KC_I)
// #define MTA_DOT RALT(KC_DOT) // same as QWERTY
#define MTG_O RGUI_T(KC_O)

/* MOD TAP defs for thumb keys */
#define LT_SPC LT(_NAV, KC_SPACE)
#define LT_TAB LT(_MOUSE, KC_TAB)
#define LT_ESC LT(_MEDIA, KC_ESC)
#define LT_BSPC LT(_NUM, KC_BACKSPACE)
#define LT_ENT LT(_SYM, KC_ENTER)
#define LT_DEL LT(_FUN, KC_DELETE)
#define LT_Z LT(_BUTTON, KC_Z)
#define LT_SLSH LT(_BUTTON, KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK Mod-DH */
[_COLEMAKDH] = LAYOUT( \
  KC_GRV,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                     KC_6, KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_NUHS, KC_Q,  KC_W,  KC_F,  KC_P,  KC_B,                     KC_J, KC_L,  KC_U,    KC_Y,   KC_SCLN, KC_NUHS, \
  KC_MINS, MTG_A, MTA_R, MTC_S, MTS_T, KC_G,                     KC_M, MTS_N, MTC_E,   MTA_I,  MTG_O,   KC_QUOT, \
  KC_NUBS, LT_Z,  KC_X,  KC_C,  KC_D,  KC_V, KC_MUTE,   XXXXXXX, KC_K, KC_H,  KC_COMM, MTA_DOT, LT_SLSH, KC_EQL, \
            KC_LBRC, KC_LPRN, LT_ESC, LT_SPC, LT_TAB,   LT_ENT, LT_BSPC, LT_DEL, KC_RPRN, KC_RBRC \
),

/* QWERTY */
[_QWERTY] = LAYOUT( \
  KC_GRV,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                     KC_6, KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_NUHS, KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                     KC_Y, KC_U,  KC_I,    KC_O,   KC_P,    KC_NUHS, \
  KC_MINS, MTG_A, MTA_S, MTC_D, MTS_F, KC_G,                     KC_H, MTS_J, MTC_K,   MTA_L,  MTG_SC,  KC_QUOT, \
  KC_NUBS, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B, KC_MUTE,   XXXXXXX, KC_N, KC_M,  KC_COMM, MTA_DOT, KC_SLSH, KC_EQL, \
            KC_LBRC, KC_LPRN, LT_ESC, LT_SPC, LT_TAB,   LT_ENT, LT_BSPC, LT_DEL, KC_RPRN, KC_RBRC \
),

/* COLEMAK Mod-DH without Mod Taps */
[_TAP] = LAYOUT( \
  KC_GRV,         KC_1, KC_2, KC_3, KC_4, KC_5,                     KC_6, KC_7,  KC_8,    KC_9,   KC_0,    KC_MINS, \
  DF(_COLEMAKDH), KC_Q, KC_W, KC_F, KC_P, KC_B,                     KC_J, KC_L,  KC_U,    KC_Y,   KC_SCLN, KC_NUHS, \
  KC_MINS,        KC_A, KC_R, KC_S, KC_T, KC_G,                     KC_M, KC_N,  KC_E,    KC_I,   KC_O,    KC_QUOT, \
  KC_NUBS,        KC_Z, KC_X, KC_C, KC_D, KC_V, KC_MUTE,   XXXXXXX, KC_K, KC_H,  KC_COMM, KC_DOT, KC_SLSH, KC_EQL, \
            KC_LBRC, KC_LPRN, KC_ESC, KC_SPC, KC_TAB,         KC_ENT, KC_BSPC, KC_DEL, KC_RPRN, KC_RBRC \
),

[_NAV] = LAYOUT( \
  XXXXXXX, XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX,          XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, \
  XXXXXXX, TD(TD_BOOT), TD(TD_TAP), TD(TD_QWERTY), TD(TD_COLEMAKDH), CG_TOGG,                     KC_AGIN, KC_PSTE, KC_COPY, KC_CUT,   KC_UNDO, XXXXXXX, \
  XXXXXXX, KC_LGUI,     KC_LALT,    KC_LCTL,       KC_LSFT,          XXXXXXX,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, CW_TOGG, KC_CAPS, \
  XXXXXXX, MO(_BUTTON), XXXXXXX,    TD(TD_NUM),    TD(TD_NAV),       XXXXXXX, KC_MUTE,   XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_INS,  XXXXXXX, \
                                      XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,          KC_ENT, KC_BSPC, KC_DEL, XXXXXXX, XXXXXXX \
),

[_MOUSE] = LAYOUT( \
  XXXXXXX, XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX,          XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, TD(TD_BOOT), TD(TD_TAP), TD(TD_QWERTY), TD(TD_COLEMAKDH), CG_TOGG,                     KC_AGIN, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO, XXXXXXX, \
  XXXXXXX, KC_LGUI,     KC_LALT,    KC_LCTL,       KC_LSFT,          XXXXXXX,                     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX, \
  XXXXXXX, MO(_BUTTON), XXXXXXX,    TD(TD_SYM),    TD(TD_MOUSE),     XXXXXXX, KC_MUTE,   XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, XXXXXXX, \
                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX \
),

[_MEDIA] = LAYOUT( \
  XXXXXXX, XXXXXXX,     XXXXXXX,    XXXXXXX,       XXXXXXX,          XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, TD(TD_BOOT), TD(TD_TAP), TD(TD_QWERTY), TD(TD_COLEMAKDH), CG_TOGG,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_LGUI,     KC_LALT,    KC_LCTL,       KC_LSFT,          XXXXXXX,                     KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX, \
  XXXXXXX, MO(_BUTTON), XXXXXXX,    TD(TD_FUN),    TD(TD_MEDIA),     XXXXXXX, KC_MUTE,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                      XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX,          KC_MSTP, KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX \
),

[_NUM] = LAYOUT( \
  KC_GRV,  KC_1,  KC_2,  KC_3,  KC_4, KC_5,                        KC_6,    KC_7,             KC_8,          KC_9,       KC_0,        KC_MINS, \
  KC_GRV,  KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC,                     CG_TOGG, TD(TD_COLEMAKDH), TD(TD_QWERTY), TD(TD_TAP), TD(TD_BOOT), XXXXXXX, \
  KC_GRV,  KC_SCLN, KC_4, KC_5, KC_6, KC_EQL,                      XXXXXXX, KC_RSFT,          KC_RCTL,       KC_LALT,    KC_RGUI,     XXXXXXX, \
  KC_GRV,  KC_NUHS, KC_1, KC_2, KC_3, KC_NUBS, KC_MUTE,   XXXXXXX, XXXXXXX, TD(TD_NUM),       TD(TD_NAV),    KC_RALT,    MO(_BUTTON), XXXXXXX, \
            XXXXXXX, XXXXXXX, KC_DOT, KC_0, KC_MINS,          XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX \
),

[_SYM] = LAYOUT( \
  XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX,          XXXXXXX,       XXXXXXX,    XXXXXXX,     XXXXXXX, \
  XXXXXXX,   S(KC_LBRC), S(KC_7), S(KC_8), S(KC_9), S(KC_RBRC),                     CG_TOGG, TD(TD_COLEMAKDH), TD(TD_QWERTY), TD(TD_TAP), TD(TD_BOOT), XXXXXXX, \
  S(KC_GRV), S(KC_SCLN), S(KC_4), S(KC_5), S(KC_6), S(KC_EQL),                      XXXXXXX, KC_RSFT,          KC_RCTL,       KC_LALT,    KC_RGUI,     XXXXXXX, \
  XXXXXXX,   S(KC_NUHS), S(KC_1), S(KC_2), S(KC_3), S(KC_NUBS), KC_MUTE,   XXXXXXX, XXXXXXX, TD(TD_SYM),       TD(TD_MOUSE),  KC_RALT,  MO(_BUTTON),   XXXXXXX, \
                  XXXXXXX, XXXXXXX, S(KC_DOT), S(KC_0), S(KC_MINS),          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
),

[_FUN] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX,          XXXXXXX,       XXXXXXX,    XXXXXXX,     XXXXXXX, \
  XXXXXXX, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR,                     CG_TOGG, TD(TD_COLEMAKDH), TD(TD_QWERTY), TD(TD_TAP), TD(TD_BOOT), XXXXXXX, \
  KC_CAPS, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,                     XXXXXXX, KC_RSFT,          KC_RCTL,       KC_LALT,    KC_RGUI,     XXXXXXX, \
  XXXXXXX, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, KC_MUTE,   XXXXXXX, XXXXXXX, TD(TD_FUN),       TD(TD_MEDIA),  KC_RALT,    MO(_BUTTON), XXXXXXX, \
                  XXXXXXX, XXXXXXX, KC_APP, KC_SPC, KC_TAB,          XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX \
),

[_BUTTON] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_AGIN,                       KC_AGIN, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO,  XXXXXXX, \
  XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                       XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX, \
  XXXXXXX, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_AGIN, KC_MUTE,     XXXXXXX, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO,  XXXXXXX, \
              XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN1, KC_BTN2,             KC_BTN2, KC_BTN1, KC_BTN3, XXXXXXX, XXXXXXX \
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
        case _COLEMAKDH:
            oled_write_P(PSTR("COLEMAK-DH "), false);
            break;
        case _TAP:
            oled_write_P(PSTR("TAP COLEMAK-DH "), true);
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
        case _COLEMAKDH:
        case _QWERTY:
        case _TAP:
            oled_write_P(PSTR("   "), false);
            break;
        case _NAV:
            oled_write_P(PSTR("NAV"), true);
            break;
        case _MOUSE:
            oled_write_P(PSTR("MOU"), true);
            break;
        case _MEDIA:
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
        case _BUTTON:
            oled_write_P(PSTR("BTN"), true);
            break;
        default:
            oled_write_P(PSTR("???"), true);
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
        case KC_CUT:
            if (record->event.pressed) {
                // cmd on macOS but CW_TOGG swaps this
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
        case _NAV:
            trackball_scrolling = true;
            break;
        default:
            trackball_scrolling = false;
    }

    return layer_state;
}

#endif
