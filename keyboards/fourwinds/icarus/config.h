#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6F75 // OU
#define MANUFACTURER    Tonehaven
#define PRODUCT         Sweet16

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

#define MATRIX_COL_PINS { }
#define MATRIX_ROW_PINS { }

#define DIODE_DIRECTION COL2ROW
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
#define DEBOUNCE 5
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0