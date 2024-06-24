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

#pragma once

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

// Tapping options
#undef TAPPING_TERM
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// Saving space
// #define NO_ACTION_TAPPING
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
