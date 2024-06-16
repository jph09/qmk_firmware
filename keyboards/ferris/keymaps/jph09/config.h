#pragma once

// Tapping options
#undef TAPPING_TERM
#define TAPPING_TERM 200
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// Pro Micro RB2040 RGB LED
#define WS2812_DI_PIN 25U
#define RGBLIGHT_LED_COUNT 2
#define RGBLED_SPLIT { 1, 1 }
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_RETAIN_VAL
#define SPLIT_LAYER_STATE_ENABLE //needed for Lighting Layers on split kb
