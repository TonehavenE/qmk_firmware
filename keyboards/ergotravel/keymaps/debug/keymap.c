#include QMK_KEYBOARD_H
#include "mousekey.h"
#include "print.h"

#define KC_NP KC_NO // key is not present
#define KC_NA KC_NO // present but not available for use
#define KC_NU KC_NO // available but not used
#define XXX KC_NO // Blank

// non-KC_ keycodes
#define KC_RST RESET

#define _BASE 0
#define _NAVR 1
#define _MOUR 2
#define _FUNL 3
#define _NSL 4
#define _NSSL 5

enum custom_keycodes {
  BASE,
  NAVR,
  MOUR,
  FUNL,
  NSL,
  NSSL,
};

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
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
  [_BASE] = LAYOUT(
  //,------+----------------+------------------+--------------+--------------+--------+----------------.        ,------------------------------------------------------+--------+--------+--------+--------+--------+--------.
     XXX,  KC_Q          , KC_W        ,  KC_F        ,     KC_P        ,  KC_G,    KC_LPRN,                                KC_RPRN,  KC_J, KC_L        , KC_U        , KC_Y          , KC_QUOT,    XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  KC_A          , LALT_T(KC_R),  LCTL_T(KC_S),     LSFT_T(KC_T),  KC_D,    KC_LBRC,                                KC_RBRC,  KC_H, RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I)  , KC_O   ,    XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  LT(FUNL, KC_Z), ALGR_T(KC_X),  KC_C        ,     KC_V        ,  KC_B,    LT(MOUR, KC_SPC),           XXX,        KC_K   ,  KC_M        , KC_COMM     , ALGR_T(KC_DOT), KC_SLSH,    XXX,
  //|------+-----+----------+------------------+--------------------------------------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  XXX,  XXX,                         LT(NSSL, KC_TAB), LT(NAVR, KC_ENT),   LT(MOUR, KC_SPC),           XXX,      LT(NSL, KC_BSPC),            XXX,  XXX,  XXX,  XXX
  //`--------+--------+--------+--------+--------+--------+-------------------------------------------/          \--------+-----------------------------------------------------+--------+--------+--------+--------+--------'
  ),

  [_NAVR] = LAYOUT(
  //,------+----------------+------------------+--------------+--------------+--------+----------------.        ,------------------------------------------------------+--------+--------+--------+--------+--------+--------.
     XXX,  KC_RST,          KC_NA,             KC_NA,         KC_NA,         KC_NA,    XXX,                       XXX,        KC_AGIN,     KC_UNDO,          KC_UP,          KC_COPY,        KC_PASTE,       XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  KC_LGUI,         KC_LALT,           KC_LCTL,       KC_LSFT,          KC_NA,    XXX,                    XXX,        KC_CAPS,    KC_LEFT,           KC_DOWN,         KC_RIGHT,       KC_NA,       XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  KC_NA,           KC_ALGR,           KC_NA,         KC_NA,         KC_NA,    KC_NA,                     KC_ENT,     KC_INS,     KC_HOME,           KC_PGDN,         KC_PGUP,        KC_END,         XXX,
  //|------+-----+----------+------------------+--------------------------------------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  XXX,  XXX,       KC_NA,                            KC_NA,                   KC_NA,                     KC_ENT,     KC_BSPC,    KC_DEL,            XXX,            XXX,             XXX
  //`--------+--------+--------+--------+--------+--------+-------------------------------------------/          \--------+-----------------------------------------------------+--------+--------+--------+--------+--------'
  ),

  [_MOUR] = LAYOUT(
 
  //,------+----------------+------------------+--------------+--------------+--------+----------------.        ,------------------------------------------------------+--------+--------+--------+--------+--------+--------.
     XXX,  KC_RST,          KC_NA,             KC_NA,         KC_NA,         KC_NA,    XXX,                       XXX,         KC_NU,     KC_NU,           KC_MS_U,        KC_NU,        KC_NU,          XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  KC_A,            LALT_T(KC_R),      LCTL_T(KC_S),  LSFT_T(KC_T),          KC_NA,    XXX,                       XXX,      KC_NU,     KC_MS_L,         KC_MS_D,        KC_MS_R,      XXX,        XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+-------+--------+--------+--------|
     XXX,  KC_NA,           KC_ALGR,           KC_NA,         KC_NA,         KC_NA,    KC_NA,                     KC_BTN1,     KC_NU,     KC_WH_L,         KC_WH_D,        KC_WH_U,      KC_WH_R,         XXX,
  //|------+-----+----------+------------------+--------------------------------------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  XXX,  XXX,       KC_NA,                            KC_NA,                   KC_NA,                     KC_BTN1,     KC_BTN3,   KC_BTN2,         XXX,            XXX,          XXX
  //`--------+--------+--------+--------+--------+--------+-------------------------------------------/          \--------+-----------------------------------------------------+--------+--------+--------+--------+--------'
  ),


  [_FUNL] = LAYOUT(
 
  //,------+----------------+------------------+--------------+--------------+--------+----------------.        ,------------------------------------------------------+--------+--------+--------+--------+--------+--------.
     XXX,  KC_F12,            KC_F7,           KC_F8,         KC_F9,         KC_PSCR,    XXX,                       XXX,       KC_NA,     KC_NA,           KC_NA,          KC_NA,          KC_RST,           XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  KC_F11,            KC_F4,           KC_F5,         KC_F6,         KC_SLCK,    XXX,                       XXX,       KC_NA,     KC_LSFT,         KC_RCTL,        KC_RALT,        KC_RGUI,         XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  KC_NA,            KC_F1,           KC_F2,         KC_F3,         KC_PAUS,    KC_TAB,                    KC_NA,     KC_NA,     KC_NA,           KC_NA,          KC_ALGR,        KC_NA,           XXX,
  //|------+-----+----------+------------------+--------------------------------------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  XXX,  XXX,       KC_APP,                        KC_SPC,                       KC_TAB,                    KC_NA,     KC_NA,     KC_NA,           XXX,            XXX,             XXX
  //`--------+--------+--------+--------+--------+--------+-------------------------------------------/          \--------+-----------------------------------------------------+--------+--------+--------+--------+--------'
  ),

 [_NSL] = LAYOUT(
 
  //,------+----------------+------------------+--------------+--------------+--------+----------------.        ,------------------------------------------------------+--------+--------+--------+--------+--------+--------.
     XXX,  KC_LBRC,            KC_7,           KC_8,         KC_9,         KC_RBRC,    XXX,                       XXX,       KC_NA,     KC_NA,           KC_NA,          KC_NA,          KC_RST,           XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  KC_SCLN,            KC_4,           KC_5,         KC_6,         KC_EQL,    XXX,                       XXX,       KC_NA,     KC_LSFT,         KC_RCTL,        KC_RALT,        KC_RGUI,         XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  KC_GRV,             KC_1,           KC_2,         KC_3,         KC_BSLS,    KC_MINS,                    KC_NA,     KC_NA,     KC_NA,           KC_NA,          KC_ALGR,        KC_NA,           XXX,
  //|------+-----+----------+------------------+--------------------------------------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  XXX,  XXX,          KC_DOT,                       KC_0,                     KC_MINS,                    KC_NA,     KC_NA,     KC_NA,           XXX,            XXX,             XXX
  //`--------+--------+--------+--------+--------+--------+-------------------------------------------/          \--------+-----------------------------------------------------+--------+--------+--------+--------+--------'
  ),

 [_NSSL] = LAYOUT(
 
  //,------+----------------+------------------+--------------+--------------+--------+----------------.        ,------------------------------------------------------+--------+--------+--------+--------+--------+--------.
     XXX,  KC_LCBR,    KC_AMPR,          KC_ASTR,      KC_LPRN,          KC_RCBR,    XXX,                       XXX,       KC_NA,     KC_NA,           KC_NA,          KC_NA,          KC_RST,           XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  KC_COLN,     KC_DLR,          KC_PERC,       KC_CIRC,         KC_PLUS,    XXX,                       XXX,       KC_NA,     KC_LSFT,         KC_LCTL,        KC_LALT,        KC_LGUI,         XXX,
  //|------+----------------+------------------+--------------+--------------+--------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  KC_TILD,     KC_EXLM,         KC_AT,         KC_PIPE,         KC_PIPE,    KC_UNDS,                    KC_NA,     KC_NA,     KC_NA,           KC_NA,          KC_ALGR,        KC_NA,           XXX,
  //|------+-----+----------+------------------+--------------------------------------+----------------|        |------------------------------------------------------+--------+--------+--------+--------+--------+--------|
     XXX,  XXX,  XXX,   KC_GT,           KC_RPRN,                                    KC_UNDS,                    KC_NA,     KC_NA,     KC_NA,           XXX,            XXX,             XXX
  //`--------+--------+--------+--------+--------+--------+-------------------------------------------/          \--------+-----------------------------------------------------+--------+--------+--------+--------+--------'
  )
};
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
   #ifdef CONSOLE_ENABLE
      uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
   #endif 
  return true;
}