// Copyright 2022 Eben Quennevile (@TonehavenE)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */
#define RGB_DI_PIN B15
#define DRIVER_LED_TOTAL 58
#define RGBLED_NUM 58
#define RGBLIGHT_DEFAULT_HUE 100
#define RGBLIGHT_DEFAULT_VAL 100
#define RGBLIGHT_LAYERS
#define RGBLIGHT_SLEEP
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
// #define RGB_MATRIX_LED_FLUSH_LIMIT 16
// #define RGB_MATRIX_STARTUP_HUE 23
// #define RGB_MATRIX_STARTUP_SAT 240
// #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define RGB_MATRIX_KEYPRESSES

// Animations:
// #define ENABLE_RGB_MATRIX_PIXEL_RAIN
// #define ENABLE_RGB_MATRIX_SOLID_COLOR
// #define ENABLE_RGB_MATRIX_BREATHING
// #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #define ENABLE_RGB_MATRIX_BAND_SAT
// #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
// #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
// #define ENABLE_RGB_MATRIX_CYCLE_ALL
// #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT

// #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
// #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
// #define ENABLE_RGB_MATRIX_DUAL_BEACON
// #define ENABLE_RGB_MATRIX_RAINDROPS
// #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
// #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
// 		#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
// #endif
// #if defined(RGB_MATRIX_KEYPRESSES)
//    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
//    #define ENABLE_RGB_MATRIX_SPLASH
//    #define ENABLE_RGB_MATRIX_MULTISPLASH
//    #define ENABLE_RGB_MATRIX_SOLID_SPLASH
//    #define ENABLE_RGB_MATRIX_MULTISPLASH
// #endif

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
// #define RGBLIGHT_ENABLE
// #define RGBLIGHT_EFFECT_BREATHING
// #define RGBLIGHT_EFFECT_SNAKE
