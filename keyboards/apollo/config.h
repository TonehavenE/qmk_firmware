// Copyright 2023 Eben Quenneville (@TonehavenE)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/*rdisable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
#define MATRIX_ROWS 8
#define MATRIX_COLS 6
#define SPLIT_HAND_PIN B8
#define USB_VBUS_PIN A15
#define SERIAL_USART_TX_PIN B6
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 0

#ifdef RGBLIGHT_ENABLE
// #    define WS2812_PWM_DRIVER PWMD3
// #    define WS2812_PWM_CHANNEL 1
// #    define WS2812_PWM_PAL_MODE 1
// #    define WS2812_DMA_STREAM STM32_DMA1_STREAM1
// #    define WS2812_DMA_CHANNEL 4
#    define RGBLIGHT_LIMIT_VAL 128
#    define RGBLIGHT_DEFAULT_VAL 128
#    define RGBLIGHT_SPLIT
#endif
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128
#    define RGB_MATRIX_LED_COUNT 39
#    define RGB_MATRIX_SPLIT \
        { 21, 18 }
#    define SPLIT_TRANSPORT_MIRROR
#    define WS2812_PWM_DRIVER PWMD3
#    define WS2812_PWM_CHANNEL 1
#    define WS2812_PWM_PAL_MODE 1
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM1
#    define WS2812_DMA_CHANNEL 4

#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#endif
