/*
Copyright 2020 Qurn

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x3060
#define DEVICE_VER 0x0001
#define MANUFACTURER   tshort
#define PRODUCT Dactyl Manuform r track
#define DESCRIPTION A ballin keyboard

/* key matrix size */
#define MATRIX_ROWS 12
#define MATRIX_COLS 6

/*
 * Keyboard Matrix Assignments
 */

//right
#define MATRIX_ROW_PINS { F7, F6, F5, F4, C6, D4 }
#define MATRIX_COL_PINS { D7, B4, B5, B6, B7, D6 }

//left
// #define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
// #define MATRIX_ROW_PINS { F6, F7, B1, B3, B2, B6 }
// #define MATRIX_ROW_PINS_RIGHT { F7, F6, F5, F4, C6, D4  }
// #define MATRIX_COL_PINS_RIGHT { D7, B4, B5, B6, B7, D6 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */

#define USE_I2C
#define SPLIT_USB_DETECT
#define MASTER_RIGHT
// #define COMBO_COUNT 38

// Bootmagic Settingst
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 6
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define POLLING true

/* Tap Hold Settings */
// Tapping_Term in MS
#define TAPPING_TERM 200

// Retro Tapping allows better usage of dual use keys
// #define RETRO_TAPPING





