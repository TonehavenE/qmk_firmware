#pragma once
#include "quantum.h"

/*******************
 *     Combos      *
 *******************/
// clang-format off
enum combo_events {
    AR_SEMICOLON,
    EIO_BSLASH,
    EI_DASH,
    HN_RPRN,
    TD_LPRN,
    STD_LBRC,
    AD_HOME,
    HO_END,
    HNE_RBRC,
    YQUOTE_EQUAL,
    QW_ESC,
    WF_MOUSE,
    FP_MOUSE,
    WP_MOUSE,
    COMBO_LENGTH
};
// clang-format on
uint16_t COMBO_LEN = COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

// Combos
const uint16_t PROGMEM ar_combo[]     = {KC_A, LALT_T(KC_R), COMBO_END};
const uint16_t PROGMEM eio_combo[]    = {RALT_T(KC_I), RCTL_T(KC_E), KC_O, COMBO_END};
const uint16_t PROGMEM ei_combo[]     = {RALT_T(KC_I), RCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM hn_combo[]     = {KC_H, RSFT_T(KC_N), COMBO_END};
const uint16_t PROGMEM td_combo[]     = {LSFT_T(KC_T), KC_D, COMBO_END};
const uint16_t PROGMEM std_combo[]    = {LCTL_T(KC_S), LSFT_T(KC_T), KC_D, COMBO_END};
const uint16_t PROGMEM hne_combo[]    = {KC_H, RSFT_T(KC_N), RCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM ho_combo[]     = {KC_H, KC_O, COMBO_END};
const uint16_t PROGMEM ad_combo[]     = {KC_A, KC_D, COMBO_END};
const uint16_t PROGMEM yquote_combo[] = {KC_Y, KC_QUOT, COMBO_END};
const uint16_t PROGMEM qw_combo[]     = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM wfm_combo[]    = {LALT_T(KC_W), LCTL_T(KC_F), COMBO_END};
const uint16_t PROGMEM fpm_combo[]    = {LCTL_T(KC_F), LSFT_T(KC_P), COMBO_END};
const uint16_t PROGMEM wpm_combo[]    = {LALT_T(KC_W), LSFT_T(KC_P), COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [AR_SEMICOLON] = COMBO(ar_combo, KC_SCOLON),
    [EIO_BSLASH] = COMBO(eio_combo, KC_BSLASH),
    [EI_DASH] = COMBO(ei_combo, KC_MINS),
    [HN_RPRN] = COMBO(hn_combo, KC_RPRN),
    [TD_LPRN] = COMBO(td_combo, KC_LPRN),
    [STD_LBRC] = COMBO(std_combo, KC_LBRC),
    [HNE_RBRC] = COMBO(hne_combo, KC_RBRC),
    [HO_END] = COMBO(ho_combo, KC_END),
    [AD_HOME] = COMBO(ad_combo, KC_HOME),
    [YQUOTE_EQUAL] = COMBO(yquote_combo, KC_EQUAL),
    [QW_ESC] = COMBO(qw_combo, KC_ESC),
    [WF_MOUSE] = COMBO(wfm_combo, KC_BTN2),
    [FP_MOUSE] = COMBO(fpm_combo, KC_BTN1),
    [WP_MOUSE] = COMBO(wpm_combo, KC_BTN3),
};
// clang-format on