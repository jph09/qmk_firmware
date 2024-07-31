#include QMK_KEYBOARD_H


// OS detection
bool mac_mode;
void set_mac_mode(bool mode) {
    mac_mode = mode;
    keymap_config.swap_lctl_lgui = mode;
    keymap_config.swap_rctl_rgui = mode;
    rgblight_set_layer_state(1, mode);
}
bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            set_mac_mode(true);
            break;
        case OS_WINDOWS:
        case OS_LINUX:
            set_mac_mode(false);
            break;
        case OS_UNSURE:
        default:
            break;
    }
    return true;
}




// Lighting Layers
const rgblight_segment_t PROGMEM rgb_layer_default[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_RED}
);
const rgblight_segment_t PROGMEM rgb_layer_mac[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_CYAN}
);
const rgblight_segment_t PROGMEM rgb_layer_capslock[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_YELLOW}
);
const rgblight_segment_t PROGMEM rgb_layer_capsword[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM rgb_layer_osm_shift[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_ORANGE}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_layer_default,
    rgb_layer_mac,
    rgb_layer_capslock,
    rgb_layer_capsword,
    rgb_layer_osm_shift
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, true);

    // Check mac mode status
    mac_mode = keymap_config.swap_lctl_lgui;
    rgblight_set_layer_state(1, mac_mode);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(2, led_state.caps_lock);
    return true;
}

void caps_word_set_user(bool active) {
    rgblight_set_layer_state(3, active);
}

void oneshot_mods_changed_user(uint8_t mods) {
    rgblight_set_layer_state(4, mods & MOD_MASK_SHIFT);
}



// KEYMAP STARTS HERE

enum ferris_layers {
    _BASE = 0,
    _NUMR, // Number row layer
    _SYMB, // Symbols layer
    _NAVI, // Navigation layer
    _FUNC, // Function keys layer
    _NUMP, // Numpad layer
};

layer_state_t layer_state_set_user(layer_state_t state) {

    // Activate Function layer when Symbols and Navigation layers are active
    state = update_tri_layer_state(state, _SYMB, _NAVI, _FUNC);

    // Activate Numpad layer when Number and Navigation layers are active
    state = update_tri_layer_state(state, _NUMR, _NAVI, _NUMP);

    return state;
}

 enum custom_keycodes {
    LOCKSCR = SAFE_RANGE,
    LAYERLK,
 };

// Aliases for ISO UK keys
#define KC_GBP S(KC_3)      // Pound sign
#define KC_EUR RALT(KC_4)   // Euro sign
#define KC_NUDQ S(KC_2)     // Non-US double quote
#define KC_NUAT S(KC_QUOT)  // Non-US at sign
#define KC_NUPI S(KC_NUBS)  // Non-US pipe
#define KC_NUTI S(KC_NUHS)  // Non-US tilde
#define S_GRV S(KC_GRV)
#define A_GRV RALT(KC_GRV)

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
#define NAV_BSP LT(_NAVI,KC_BSPC)
#define SYM_ENT LT(_SYMB,KC_ENT)
#define NUM_SPC LT(_NUMR,KC_SPC)
//#define SYM_QUO LT(_SYMB,KC_QUOT)

/* Override shifted keys */
const key_override_t ko_scln = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t ko_cln = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
const key_override_t ko_non_us_dquo = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, KC_NUDQ); // See case for SYM_QUO in process_record_user()
// const key_override_t ko_non_us_at = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_NUAT);
const key_override_t **key_overrides = (const key_override_t *[]){
    &ko_scln,
    &ko_cln,
    &ko_non_us_dquo,
    // &ko_non_us_at,
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CUT:
            if (mac_mode) {
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
            if (mac_mode) {
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
            if (mac_mode) {
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
            // No mac_mode switch because the same keycodes are needed for both modes
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
            if (mac_mode) {
                // macOS mode
                if (record->event.pressed) {
                    // cmd on macOS but CW_TOGG swaps this
                    register_mods(mod_config(MOD_LCTL | MOD_LSFT));
                    register_code(KC_Z);
                } else {
                    unregister_mods(mod_config(MOD_LCTL | MOD_LSFT));
                    unregister_code(KC_Z);
                }
            } else {
                // Windows & Linux mode
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
        case OSMLSFT:
            if (record->event.pressed && record->tap.count) {
                // If Caps Word is on, turn it off
                // and don't activate one-shot shift.
                if (is_caps_word_on()) {
                    caps_word_off();
                    return false;
                }
            }
            return true;
            break;
        // case SYM_QUO:
        //     if (record->event.pressed && record->tap.count) {
        //         // If shift is active and SYM_QUO is tapped
        //         // then type double-quote instead of quote
        //         if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
        //             tap_code16(KC_NUDQ);
        //             return false;
        //         }
        //     }
        //     break;
        case LOCKSCR:
            if (mac_mode) {
                // macOS mode
                // Send Cmd+Ctrl+Q (ie. C(G(KC_Q)))
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LCTL | MOD_LGUI));
                    register_code(KC_Q);
                } else {
                    unregister_mods(mod_config(MOD_LCTL | MOD_LGUI));
                    unregister_code(KC_Q);
                }
            } else {
                // Windows & Linux mode
                // Send Win+L (ie. G(KC_L))
                if (record->event.pressed) {
                    register_mods(mod_config(MOD_LGUI));
                    register_code(KC_L);
                } else {
                    unregister_mods(mod_config(MOD_LGUI));
                    unregister_code(KC_L);
                }
            }
    }
    return true;
}

// Use post_process_record_user to get state after flag is flipped...
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CG_TOGG:
            mac_mode = keymap_config.swap_lctl_lgui;
            rgblight_set_layer_state(1, mac_mode);
            break;
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // COLEMAK Mod-DH base layer
    [_BASE] = LAYOUT(                                                                         \
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_MINS, \
    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    \
    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_QUOT, \
                               NAV_BSP, OSMLSFT, NUM_SPC, SYM_ENT                             \
    ),

    // Number row layer
    // Missing: 
    [_NUMR] = LAYOUT(                                                                         \
    KC_GRV,  KC_DLR,  KC_GBP,  KC_EUR,  KC_UNDS, KC_ASTR, KC_SLSH, KC_EQL,  KC_PLUS, _______, \
    KC_7,    KC_5,    KC_3,    KC_1,    KC_9,    KC_8,    KC_0,    KC_2,    KC_4,    KC_6,    \
    KC_AMPR, KC_PERC, KC_NUHS, KC_LPRN, KC_RPRN, KC_LABK, KC_RABK, _______, _______, KC_CIRC, \
                               _______, _______, _______, _______                             \
    ),

    // Symbols layer
    [_SYMB] = LAYOUT(                                                                         \
    KC_GRV,  S_GRV,   A_GRV,   KC_SCLN, KC_COLN, LAYERLK, XXXXXXX, XXXXXXX, C(KC_S), LOCKSCR, \
    KC_QUES, KC_EXLM, KC_NUAT, KC_LBRC, KC_RBRC, KC_CAPS, OSMRSFT, OSMRCTL, OSMRALT, OSMRGUI, \
    KC_NUBS, KC_NUPI, KC_NUTI, KC_LCBR, KC_RCBR, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO, \
                               _______, _______, _______, _______                             \
    ),

    // Navigation layer
    [_NAVI] = LAYOUT(                                                                         \
    LOCKSCR, C(KC_S), C(KC_F), KC_APP,  LAYERLK, KC_ESC,  KC_BSPC, KC_DEL,  KC_INS,  KC_SPC,  \
    OSMLGUI, OSMLALT, OSMLCTL, OSMLSFT, KC_CAPS, KC_TAB,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,\
    KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_AGIN, KC_ENT,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  \
                               _______, _______, _______, _______                             \
    ),

    // Function keys layer
    // Active with Symbols and Navigation
    [_FUNC] = LAYOUT(
    TD_BOOT, CG_TOGG, RGB_VAD, RGB_VAI, KC_PSCR, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   \
    _______, _______, _______, _______, KC_SCRL, _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   \
    KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_PAUS, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
                               _______, _______, _______, _______                             \
    ),

    // Numpad layer
    // Active with Numbers and Navigation
    [_NUMP] = LAYOUT(                                                                         \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                               _______, _______, _______, _______                             \
    ),
/* 
    // Blank layer
    [] = LAYOUT(                                                                              \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                               _______, _______, _______, _______                             \
    ),
 */
};



