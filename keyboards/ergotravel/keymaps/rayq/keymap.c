#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _NUMSYM 2
#define _NAV    4
#define _MEDIA  8

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NUMSYM,
  NAV,
  MEDIA,
};

//#define CALTDEL  LCTL(LALT(KC_DEL))
#define TSKMGR   LCTL(LSFT(KC_ESC))
#define CTLHOME  LCTL(KC_HOME)
#define CTLEND   LCTL(KC_END)
#define CTLLEFT  LCTL(KC_LEFT)
#define CTLRGHT  LCTL(KC_RGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Unused:
KC_PSCR   PRINT SCREEN
KC_SLCK   SCROLL LOCK
KC_PAUSE  / BREAK
KC_INS    INSERT
KC_NLCK   NUMLOCK
ALL KC_KP_ KEYPADs
KC_F13 - F19
KC_RCTL  RIGHT CONTROL
KC_RALT  RIGHT ALT
KC_RGUI  MENU

DM_REC1 START RECORDING MACRO 1
DM_REC2 START RECORDING MACRO 2
DM_RSTP RECORDING STOP
DM_PLY1 REPLAY MACRO 1
DM_PLY2 REPLAY MACRO 2
*/

 [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,          KC_EQL, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,          KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC,           KC_SPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_LGUI, XXXXXXX, KC_LALT,     MO(_NUMSYM),  KC_SPC,           KC_SPC,  MO(_NAV), MO(_MEDIA),   XXXXXXX, KC_SLSH, KC_DEL
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  ),


 [_NUMSYM] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_CAPS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,             KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, _______, XXXXXXX,          _______, _______,          _______, XXXXXXX,          XXXXXXX, XXXXXXX, _______, _______
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  ),


[_NAV] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     XXXXXXX, XXXXXXX, KC_PGDN, KC_UP,   KC_PGUP, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     CTLHOME, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  CTLEND,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, CTLLEFT, XXXXXXX, CTLRGHT, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     _______, XXXXXXX, XXXXXXX, _______,          XXXXXXX, _______,          _______, _______,          XXXXXXX, XXXXXXX, XXXXXXX, _______
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  ),

[_MEDIA] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_MPLY, KC_MSTP, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_BRIU,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, KC_BRID,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_MRWD, KC_MFFD, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_MAIL, KC_CALC, KC_MYCM, XXXXXXX,          XXXXXXX, XXXXXXX,          TSKMGR,  XXXXXXX,          _______,  KC_WAKE, KC_PWR,  KC_SLEP
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  )

};