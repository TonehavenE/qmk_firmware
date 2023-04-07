#pragma once
/* Tap Hold Settings */

// Default but important:
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// Prevent normal rollover on alphas from accidentally triggering mods
// #define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat
// #define TAPPING_FORCE_HOLD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4

// Nice feature
#define FORCE_NKRO

/* Combo Settings */
#define COMBO_TERM 40
