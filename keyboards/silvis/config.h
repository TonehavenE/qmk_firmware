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
    #define USB_MAX_POWER_CONSUMPTION 500
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128
    #define RGB_MATRIX_LED_COUNT 58
    #define RGB_MATRIX_LED_PROCESS_LIMIT  10 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
    #define RGB_MATRIX_LED_FLUSH_LIMIT 8
    #define WS2812_PWM_DRIVER PWMD1  // default: PWMD2
    #define WS2812_PWM_CHANNEL 3  // default: 2
    #define WS2812_PWM_PAL_MODE 1  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
    #define WS2812_PWM_COMPLEMENTARY_OUTPUT
    #define WS2812_DMA_STREAM STM32_DMA2_STREAM5  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
    #define WS2812_DMA_CHANNEL 6  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
    // #define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM2_UP // DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.
    #define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#endif

#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 0
#    define MOUSEKEY_INTERVAL 16
#    define MOUSEKEY_MAX_SPEED 6
#    define MOUSEKEY_TIME_TO_MAX 64
#endif
