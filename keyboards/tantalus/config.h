#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x5448   // TH
#define PRODUCT_ID 0x5453  // TS
#define DEVICE_VER 0x0001
#define MANUFACTURER Tonehaven
#define PRODUCT Tantalus
#define DESCRIPTION A thirty percent with trackball

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 11

/* key matrix pins */
#define MATRIX_ROW_PINS \
    { D6, D4, D5, D3 }
#define MATRIX_COL_PINS \
    { C7, C6, B6, B5, B4, F0, F7, F6, F5, F4, F1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define POLLING true

// Bootmagic Settings
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
