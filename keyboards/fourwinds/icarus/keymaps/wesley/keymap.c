// #include "dtostrf.h"
// #include "tinyexpr.c"
#include "tinyexpr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "print.h"
#include "icarus.h"
#include "tapdance.h"

#define _main 0
#define _calc 1

/*
TO FIX or DO:

* ROOT
* FIX BSPC
* FIX LMAO
* REFACTOR TAPDANCES

*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_main] = LAYOUT_MACROPAD(
        KC_BSPC, KC_LMAO   , TO(_calc), KC_ENT,
        KC_3   , KC_6   , KC_9     , KC_DOT,
        KC_2   , KC_5   , KC_8     , KC_0,  // TD(TAP_EQL)
        KC_1   , KC_4   , KC_7     , KC_CIRC,
        RESET, KC_PLUS, KC_ASTR  , KC_MINS
    ),
    [_calc] = LAYOUT_MACROPAD(
        CALC_BSPACE, KC_TRNS, TO(_main), CALC_EQL,
        CALC_3, CALC_6, CALC_9, TD(CALC_DOTPR),
        CALC_2, CALC_5, CALC_8, CALC_0,
        CALC_1, CALC_4, CALC_7, TD(CALC_EXPMOD),
        TD(CALC_DWNPR), TD(CALC_MODE), TD(CALC_UPPER), TD(CALC_SUBCL)
    )
    // clang-format on
};
#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable=true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
}
#endif
