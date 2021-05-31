#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Tonehaven
#define PRODUCT         Tantalus
#define DESCRIPTION     A thirty percent with trackball

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 11

/* key matrix pins */
#define MATRIX_ROW_PINS { D6, D4, D5, D3 }
#define MATRIX_COL_PINS { C7, C6, B6, B5, B4, F0, F7, F6, F5, F4, F1 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// Bootmagic Settings
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* Tap Hold Settings */

// Default but important:
#define TAPPING_TERM 200 

// Prevent normal rollover on alphas from accidentally triggering mods
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat
#define TAPPING_FORCE_HOLD

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Nice feature 
#define FORCE_NKRO

/* Combo Settings */ 

#define COMBO_TERM 40 



