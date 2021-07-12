#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6F75 // OU
#define PRODUCT_ID 		0x3060
#define DEVICE_VER 0x0001
#define MANUFACTURER    Tonehaven
#define PRODUCT         Icarus
#define DESCRIPTION 4x5 Macropad and Calculator

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

#define MATRIX_COL_PINS { B0, A7, A6, A5 }
#define MATRIX_ROW_PINS { A4, A3, A2, A1, A0}

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#ifndef STM32_HSECLK
	#define STM32_HSECLK 16000000U
#endif  // STM32_HSECLK