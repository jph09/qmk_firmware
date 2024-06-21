#pragma once

// Work around a bug with my keyboard not detecting the master side correctly
#define SPLIT_WATCHDOG_ENABLE

// Support more layer with Via
#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// Tapping options
#undef TAPPING_TERM
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// Pro Micro RP2040 onboard RGB LED
#define WS2812_DI_PIN 25U // Alias for GPIO25 not defined by promicro_rp2040 converter, hardware address is 25U.
#define RGBLIGHT_LED_COUNT 2
#define RGBLED_SPLIT { 1, 1 }
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_RETAIN_VAL
#define SPLIT_LAYER_STATE_ENABLE //needed for Lighting Layers on split kb
