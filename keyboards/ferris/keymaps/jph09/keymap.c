#include QMK_KEYBOARD_H

// Abbreviations for one-shots
#define OSMLGUI OSM(MOD_LGUI)
#define OSMLALT OSM(MOD_LALT)
#define OSMLCTL OSM(MOD_LCTL)
#define OSMLSFT OSM(MOD_LSFT)
#define OSMRSFT OSM(MOD_RSFT)
#define OSMRCTL OSM(MOD_RCTL)
#define OSMRALT OSM(MOD_RALT)
#define OSMRGUI OSM(MOD_RGUI)

// Abbreviations for layer-taps
#define LT2BSP LT(2,KC_BSPC)
#define LT1ENT LT(1,KC_ENT)

// Extra aliases for ISO UK keys
#define KC_GBP S(KC_3)      // Pound sign
#define KC_EUR RALT(KC_4)   // Euro sign
#define KC_NUDQ S(KC_2)     // Non-US Double Quote
#define KC_NUAT S(KC_QUOT)  // Non-US At sign

/* Override shifted keys */
const key_override_t ko_scln = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t ko_cln = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
const key_override_t ko_non_us_dquo = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_NUDQ);
const key_override_t ko_non_us_at = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_NUAT);
const key_override_t ko_labk = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_LABK);
const key_override_t ko_rabk = ko_make_basic(MOD_MASK_SHIFT, KC_RPRN, KC_RABK);
const key_override_t **key_overrides = (const key_override_t *[]){
    &ko_scln,
    &ko_cln,
    &ko_non_us_dquo,
    &ko_non_us_at,
    &ko_labk,
    &ko_rabk,
    NULL
};

/* Safety Tap Dance on QK_BOOT */
enum { 
    _TD_BOOT = 0, 
};
void tap_dance_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        reset_keyboard();
    }
};
tap_dance_action_t tap_dance_actions[] = {
    [_TD_BOOT] = ACTION_TAP_DANCE_FN (tap_dance_boot),
};
#define TD_BOOT TD(_TD_BOOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* COLEMAK Mod-DH base layer */
    [0] = LAYOUT(                                                                             \
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_MINS, \
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    \
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_QUOT, \
                               LT2BSP,  OSMLSFT, KC_SPC,  LT1ENT                              \
    ),

    /* Numbers and symbols layer
    Missing: KC_PERC, KC_CIRC, KC_AMPR, S(KC_NUBS), S(KC_NUHS), S(KC_GRV), RALT(KC_GRV), KC_LCBR, KC_RCBR, KC_LABK, KC_RABK 
    */
    [1] = LAYOUT(                                                                             \
    KC_EUR,  KC_DLR,  KC_GBP,  KC_EXLM, KC_QUES, KC_EQL,  KC_ASTR, KC_SLSH, KC_PLUS, _______, \
    KC_7,    KC_5,    KC_3,    KC_1,    KC_9,    KC_8,    KC_0,    KC_2,    KC_4,    KC_6,    \
    KC_NUBS, KC_NUHS, KC_NUAT, KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, _______, _______, KC_GRV,  \
                               _______, _______, _______, _______                             \
    ), 

    /* Navigation layer */
    [2] = LAYOUT(                                                                             \
    G(KC_L), C(KC_S), C(KC_F), KC_APP,  KC_ESC,  KC_DEL,  KC_SCRL, KC_PSCR, KC_PAUS, KC_INS,  \
    OSMLGUI, OSMLALT, OSMLCTL, OSMLSFT, KC_TAB,  KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,\
    KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_AGIN, KC_ENT,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  \
                               _______, _______, _______, _______                             \
    ),

    /* Function layer */
    [3] = LAYOUT(                                                                             \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  \
    OSMLGUI, OSMLALT, OSMLCTL, OSMLSFT, KC_F11,  KC_F12,  OSMRSFT, OSMRCTL, OSMRALT, OSMRGUI, \
    CG_TOGG, RGB_VAD, RGB_VAI, KC_CAPS, TD_BOOT, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, \
                               _______, _______, _______, _______                             \
    ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, 1, 2, 3);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CUT:
            if (keymap_config.swap_lctl_lgui) {
                // macOS mode
                // need to send Cmd+X, but Ctrl/Cmd are swapped
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_X);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_X);
                }
            } else {
                // Windows & Linux mode
                // Use Shift+Del to work anywhere (e.g. Linux terminal)
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LSFT));
                    register_code(KC_DEL);
                } else {
                    unregister_mods(mod_config(MOD_LSFT));
                    unregister_code(KC_DEL);
                }
            }
            return false;
            break;
        case KC_COPY:
            if (keymap_config.swap_lctl_lgui) {
                // macOS mode
                // need to send Cmd+C, but Ctrl/Cmd are swapped
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_C);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_C);
                }
            } else {
                // Windows & Linux mode
                // use Ctrl+Ins to work anywhere (e.g. Linux terminal)
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_INS);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_INS);
                }
            } 
            return false;
            break;
        case KC_PASTE:
            if (keymap_config.swap_lctl_lgui) {
                // macOS mode
                // need to send Cmd+V, but Ctrl/Cmd are swapped
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LCTL));
                    register_code(KC_V);
                } else {
                    unregister_mods(mod_config(MOD_LCTL));
                    unregister_code(KC_V);
                }
            } else {
                // Windows & Linux mode
                // use Shift+Ins to work anywhere (e.g. Linux terminal)
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LSFT));
                    register_code(KC_INS);
                } else {
                    unregister_mods(mod_config(MOD_LSFT));
                    unregister_code(KC_INS);
                }
            } 
            return false;
            break;
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
                    // cmd on macOS but CW_TOGG swaps this
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
