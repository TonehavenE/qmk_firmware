// Copyright 2023 Eben Quenneville (@TonehavenE)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/*rdisable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

#define SERIAL_USART_TX_PIN B6
/*
#define DIRECT_PINS {\
    {B10, B11, C9, C12, D2, B5},\
    {B0, B2, C8, C11, B3, B7},\
    {C4, C5, C7, C10, B4, B9},\
    {NO_PIN, NO_PIN, NO_PIN, C13, C14, C15}\
}
#define DIRECT_PINS_RIGHT {\
    {NO_PIN, C15, C3, A2, B2, B12},\
    {NO_PIN, C14, C2, A1, B10, B13},\
    {NO_PIN, C13, C1, A0, B11, B14},\
    {C11, C12, D2, NO_PIN, NO_PIN, NO_PIN}\
}
*/
