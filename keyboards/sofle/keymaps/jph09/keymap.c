#include QMK_KEYBOARD_H
#include <string.h>
#include "lib/lib8tion/lib8tion.h"


// OS detection
bool mac_mode;
void set_mac_mode(bool mode) {
    mac_mode = mode;
    keymap_config.swap_lctl_lgui = mode;
    keymap_config.swap_rctl_rgui = mode;
}
#ifdef OS_DETECTION_ENABLE
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
#endif // OS_DETECTION_ENABLE


enum sofle_layers {
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
    SCROLL,
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

#ifdef TAP_DANCE_ENABLE
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
#else // TAP_DANCE_ENABLE
#define TD_BOOT KC_NO
#endif // TAP_DANCE_ENABLE


#ifdef POINTING_DEVICE_ENABLE
static bool trackball_scrolling = false;
#endif // POINTING_DEVICE_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        #ifdef POINTING_DEVICE_ENABLE
        case SCROLL:
            if (record->event.pressed) {
                trackball_scrolling = ! trackball_scrolling ;
            }
            return false;
            break;
        #endif // POINTING_DEVICE_ENABLE

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
            break;
    }
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
#endif // ENCODER_ENABLE

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
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
    if (! is_keyboard_master()) {
        render_anim();
        oled_set_cursor(1,12);
        oled_write_P(PSTR("WPM"), false);
        oled_set_cursor(1,13);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);
        return false;
    }

    // Layer indicator
    switch (get_highest_layer(layer_state)) {
        case _NAVI:
            oled_write_ln_P(PSTR("NAVI"), true);
            break;
        case _SYMB:
            oled_write_ln_P(PSTR("SYMB"), true);
            break;
        case _FUNC:
            oled_write_ln_P(PSTR("FUNC"), true);
            break;
        case _NUMR:
            oled_write_ln_P(PSTR("NUMR"), true);
            break;
        case _NUMP:
            oled_write_ln_P(PSTR("NUMP"), true);
            break;
        default:
            oled_write_ln_P(PSTR("BASE"), true);
    }
    oled_write_ln_P(PSTR(""), false);

    // Mods state
    uint8_t mod_state = get_mods() | get_oneshot_mods();
    oled_write_P(PSTR("G"), mod_state & MOD_MASK_GUI);
    oled_write_P(PSTR("A"), mod_state & MOD_MASK_ALT);
    oled_write_P(PSTR("C"), mod_state & MOD_MASK_CTRL);
    oled_write_ln_P(PSTR("S"), mod_state & MOD_MASK_SHIFT);
    oled_write_ln_P(PSTR(""), false);

    // Capsword state
    oled_write_ln_P(PSTR("C_W"), is_caps_word_on());
    oled_write_ln_P(PSTR(""), false);

    // Capslock indicator
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR("A"), led_usb_state.caps_lock);
    oled_write_P(PSTR("1"), led_usb_state.num_lock);
    oled_write_ln_P(PSTR("v"), led_usb_state.scroll_lock);
    oled_write_ln_P(PSTR(""), false);

    // PC or Mac mode
    if (mac_mode) {
        oled_write_ln_P(PSTR("mac"), false);
    } else {
        oled_write_ln_P(PSTR("PC"), false);
    }
    oled_write_ln_P(PSTR(""), false);

    // Mousing or scrolling
    if (trackball_scrolling) {
        oled_write_ln_P(PSTR("SCRL"), true);
    } else {
        oled_write_ln_P(PSTR(""), false);
    }

    return false;
}
#endif // OLED_ENABLE

#ifdef POINTING_DEVICE_ENABLE

static uint32_t       last_mouse_activity = 0;
static report_mouse_t last_mouse_report   = {0};

report_mouse_t smooth_mouse_movement(report_mouse_t mouse_report) {

    mouse_report.x = ease8InOutApprox(lerp8by8(last_mouse_report.x, mouse_report.x, 0.5));
    mouse_report.y = ease8InOutApprox(lerp8by8(last_mouse_report.y, mouse_report.y, 0.5));

    return mouse_report;
}

// void pointing_device_init_user(void) {
//     set_auto_mouse_layer(_MOU); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
//     set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
// }

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

#endif // POINTING_DEVICE_ENABLE


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // COLEMAK Mod-DH base layer
    [_BASE] = LAYOUT(                                                                                                             \
    KC_GRV,  KC_APP,  KC_LCBR, KC_LBRC, KC_LPRN, KC_LABK,                   KC_RABK, KC_RPRN, KC_RBRC, KC_RCBR, KC_MINS, KC_EQL,  \
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y,    KC_MINS, KC_DEL,  \
    KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    SCROLL,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_MUTE, XXXXXXX, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_QUOT, KC_RSFT, \
                      KC_LCTL, KC_LGUI, KC_LALT, NAV_BSP, OSMLSFT, NUM_SPC, SYM_ENT, KC_RALT, KC_RGUI, KC_RCTL                    \
    ),

    // Number row layer
    [_NUMR] = LAYOUT(                                                                                                             \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, KC_GRV,  KC_DLR,  KC_GBP,  KC_EUR,  KC_UNDS,                   KC_ASTR, KC_SLSH, KC_EQL,  KC_PLUS, _______, _______, \
    _______, KC_7,    KC_5,    KC_3,    KC_1,    KC_9,                      KC_8,    KC_0,    KC_2,    KC_4,    KC_6,    _______, \
    _______, KC_AMPR, KC_PERC, KC_NUHS, KC_LPRN, KC_RPRN, _______, _______, KC_LABK, KC_RABK, _______, _______, KC_CIRC, _______, \
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______                    \
    ),

    // Symbols layer
    [_SYMB] = LAYOUT(                                                                                                             \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, KC_GRV,  S_GRV,   A_GRV,   KC_SCLN, KC_COLN,                   LAYERLK, XXXXXXX, XXXXXXX, C(KC_S), LOCKSCR, _______, \
    _______, KC_QUES, KC_EXLM, KC_NUAT, KC_LBRC, KC_RBRC,                   KC_CAPS, OSMRSFT, OSMRCTL, OSMRALT, OSMRGUI, _______, \
    _______, KC_NUBS, KC_NUPI, KC_NUTI, KC_LCBR, KC_RCBR, _______, _______, KC_AGIN, KC_PSTE, KC_COPY, KC_CUT,  KC_UNDO, _______, \
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______                    \
    ),

    // Navigation layer
    [_NAVI] = LAYOUT(                                                                                                             \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, LOCKSCR, C(KC_S), C(KC_F), KC_APP,  LAYERLK,                   KC_ESC,  KC_BSPC, KC_DEL,  KC_INS,  KC_SPC,  _______, \
    _______, OSMLGUI, OSMLALT, OSMLCTL, OSMLSFT, KC_CAPS,                   KC_TAB,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, \
    _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE, KC_AGIN, _______, _______, KC_ENT,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, \
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______                    \
    ),

    // Function keys layer
    // Active with Symbols and Navigation
    [_FUNC] = LAYOUT(                                                                                                             \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, TD_BOOT, CG_TOGG, RGB_VAD, RGB_VAI, KC_PSCR,                   _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, \
    _______, _______, _______, _______, _______, KC_SCRL,                   _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, \
    _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_PAUS, _______, _______, _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______                    \
    ),

    // Numpad layer
    // Active with Numbers and Navigation
    [_NUMP] = LAYOUT(                                                                                                             \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______                    \
    ),
/*
    // Blank layer
    [] = LAYOUT(                                                                                                                  \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______                    \
    ),
 */
};
