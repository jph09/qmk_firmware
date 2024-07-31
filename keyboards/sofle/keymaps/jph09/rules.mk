EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = no
KEY_OVERRIDE_ENABLE = yes

VIA_ENABLE = yes

MAGIC_ENABLE = yes
CAPS_WORD_ENABLE = yes
OS_DETECTION_ENABLE = no # not available in old QMK version

# Pro Micro RP2040 CE features
CONVERT_TO = rp2040_ce

# Sofle has no lighting
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no

# OLED features
OLED_ENABLE = yes
WPM_ENABLE = yes

# Encoder features
ENCODER_ENABLE = yes

# Trackball features
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball


#Debug options
VERBOSE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
