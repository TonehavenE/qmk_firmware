// Copyright 2022 Eben Quennevile (@TonehavenE)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RGB_DI_PIN B15
#ifdef RGBLIGHT_ENABLE
#    define DRIVER_LED_TOTAL 58
#    define RGBLED_NUM 58
#    define RGBLIGHT_DEFAULT_HUE 100
#    define RGBLIGHT_DEFAULT_VAL 100
#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT 70
#endif

#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 0
#    define MOUSEKEY_INTERVAL 16
#    define MOUSEKEY_MAX_SPEED 6
#    define MOUSEKEY_TIME_TO_MAX 64
#endif
