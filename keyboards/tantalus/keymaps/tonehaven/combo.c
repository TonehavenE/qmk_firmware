#pragma once
#include "quantum.h"

/*******************
 *     Combos      *
 *******************/
// clang-format off
enum combo_events {
    LUY_SCLN,
    MCOMDOT_DASH,
    YQUOTE_EQUAL,
    QW_ESC,
    WF_MOUSE,
    FP_MOUSE,
    WP_MOUSE,
    COMBO_LENGTH
};
// clang-format on
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

// Combos
const uint16_t PROGMEM luy_combo[]     = {KC_L, KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM mcomdot_combo[] = {KC_M, KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM yquote_combo[]  = {KC_Y, KC_QUOT, COMBO_END};
const uint16_t PROGMEM qw_combo[]      = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM wfm_combo[]     = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM fpm_combo[]     = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM wpm_combo[]     = {KC_W, KC_P, COMBO_END};

combo_t key_combos[] = {
    [LUY_SCLN]     = COMBO(luy_combo, KC_SCLN),     //\n
    [MCOMDOT_DASH] = COMBO(mcomdot_combo, KC_BSLS), //\n
    [YQUOTE_EQUAL] = COMBO(yquote_combo, KC_EQUAL), //\n
    [QW_ESC]       = COMBO(qw_combo, KC_ESC),       //\n
    [WF_MOUSE]     = COMBO(wfm_combo, KC_BTN2),     //\n
    [FP_MOUSE]     = COMBO(fpm_combo, KC_BTN1),     //\n
    [WP_MOUSE]     = COMBO(wpm_combo, KC_BTN3),     //\n
};
