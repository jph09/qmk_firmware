#pragma once

// Work around a bug with my keyboard not detecting the master side correctly
#define SPLIT_WATCHDOG_ENABLE

// Support more layers with Via
#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// Tapping options
#undef TAPPING_TERM
#define TAPPING_TERM 200
#define QUICK_TAP_TERM 0 // Tap-then-hold does the hold action instead of auto-repeating the tap
#define PERMISSIVE_HOLD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

/* EE_HANDS needed for split pointing device */
#define EE_HANDS

/* trackball options */
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_ROTATION_90
#define POINTING_DEVICE_TASK_THROTTLE_MS 8
#define TRACKBALL_LED_TIMEOUT 3000 // time in milliseconds
// #define POINTING_DEVICE_AUTO_MOUSE_ENABLE

/* OLED options */
#define SPLIT_OLED_ENABLE
#define SPLIT_WPM_ENABLE

/* encoder settings */
#undef TAP_CODE_DELAY
#define TAP_CODE_DELAY 100
#define ENCODER_DIRECTION_FLIP

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64
