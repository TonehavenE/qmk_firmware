#pragma once
#include "quantum.h"

/*******************
 *     Combos      *
 *******************/
enum combo_events {
    QA_ONE,
    WR_TWO,
    FS_THREE,
    PT_FOUR,
    GD_FIVE,
    JH_SIX,
    LN_SEVEN,
    UE_EIGHT,
    YI_NINE,
    QUOTEO_ZERO,
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
    RS_MOUSE,
    ST_MOUSE,
    RT_MOUSE,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

// Combos
const uint16_t PROGMEM qa_combo[] = {KC_Q, KC_A, COMBO_END};
const uint16_t PROGMEM wr_combo[] = {KC_W, LALT_T(KC_R), COMBO_END};
const uint16_t PROGMEM fs_combo[] = {KC_F, LCTL_T(KC_S), COMBO_END};
const uint16_t PROGMEM pt_combo[] = {KC_P, LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM gd_combo[] = {KC_G, KC_D, COMBO_END};
const uint16_t PROGMEM jh_combo[] = {KC_J, KC_H, COMBO_END};
const uint16_t PROGMEM ln_combo[] = {KC_L, RSFT_T(KC_N), COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_U, RCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM yi_combo[] = {KC_Y, RALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM quoto_combo[] = {KC_QUOT, KC_O, COMBO_END};
const uint16_t PROGMEM ar_combo[] = {KC_A, LALT_T(KC_R), COMBO_END};
const uint16_t PROGMEM eio_combo[] = {RALT_T(KC_I), RCTL_T(KC_E), KC_O, COMBO_END};
const uint16_t PROGMEM ei_combo[] = {RALT_T(KC_I), RCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM hn_combo[] = {KC_H, RSFT_T(KC_N), COMBO_END};
const uint16_t PROGMEM td_combo[] = {LSFT_T(KC_T), KC_D, COMBO_END};
const uint16_t PROGMEM std_combo[] = {LCTL_T(KC_S), LSFT_T(KC_T), KC_D, COMBO_END};
const uint16_t PROGMEM hne_combo[] = {KC_H, RSFT_T(KC_N), RCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM ho_combo[] = {KC_H, KC_O, COMBO_END};
const uint16_t PROGMEM ad_combo[] = {KC_A, KC_D, COMBO_END};
const uint16_t PROGMEM yquote_combo[] = {KC_Y, KC_QUOT, COMBO_END}; 
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM rsm_combo[] = {LALT_T(KC_R), LCTL_T(KC_S), COMBO_END};
const uint16_t PROGMEM stm_combo[] = {LCTL_T(KC_S), LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM rtm_combo[] = {LALT_T(KC_R), LSFT_T(KC_T), COMBO_END};


combo_t key_combos[] = {
    [QA_ONE] = COMBO(qa_combo, KC_1),
    [WR_TWO] = COMBO(wr_combo, KC_2),
    [FS_THREE] = COMBO(fs_combo, KC_3),
    [PT_FOUR] = COMBO(pt_combo, KC_4),
    [GD_FIVE] = COMBO(gd_combo, KC_5),
    [JH_SIX] = COMBO(jh_combo, KC_6),
    [LN_SEVEN] = COMBO(ln_combo, KC_7),
    [UE_EIGHT] = COMBO(ue_combo, KC_8),
    [YI_NINE] = COMBO(yi_combo, KC_9),
    [QUOTEO_ZERO] = COMBO(quoto_combo, KC_0),
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
    [RS_MOUSE] = COMBO(rsm_combo, KC_BTN2),
    [ST_MOUSE] = COMBO(stm_combo, KC_BTN1),
    [RT_MOUSE] = COMBO(rtm_combo, KC_BTN3),
};
