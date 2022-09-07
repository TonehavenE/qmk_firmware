// Copyright 2022 Eben Quennevile (@TonehavenE)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */
#define RGB_DI_PIN B15
// #define RGBLED_NUM 58
#define DRIVER_LED_TOTAL 58
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_DIGITAL_RAIN

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
