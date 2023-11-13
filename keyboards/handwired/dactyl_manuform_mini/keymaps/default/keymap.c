#include "keycode.h"
#include QMK_KEYBOARD_H
#include "print.h"
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6(
        KC_GESC, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0   , KC_EQUAL,
        KC_LALT, KC_Q  , KC_W  , KC_F  , KC_P  , KC_G  ,                         KC_J  , KC_L  , KC_U  , KC_Y  , KC_QUOT, KC_SCLN,
        KC_LSFT, KC_A  , KC_R  , KC_S  , KC_T  , KC_D  ,                         KC_H  , KC_N  , KC_E  , KC_I  , KC_O   , KC_BSLASH,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_K  , KC_M  ,KC_COMM,KC_DOT , KC_SLSH, LGUI_T(KC_MINUS),
                         KC_LPRN,KC_RPRN,                                                       KC_LBRC, KC_RBRC,
                                         LOWER,                                         KC_BSPC,
                                         KC_TAB, KC_SPC,                        KC_ENT,  RAISE,
                                         KC_LGUI, KC_TAB,                        KC_DEL,KC_LGUI
    ),

    [_LOWER] = LAYOUT_5x6(
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
        _______,KC_MS_WH_UP,KC_MS_BTN1, KC_MS_U, KC_MS_BTN2,KC_LBRC,                        KC_RBRC, KC_HOME , KC_UP , KC_END ,_______,KC_PLUS,
        _______,KC_MS_WH_DOWN,KC_MS_L, KC_MS_D, KC_MS_R ,KC_LPRN,                        KC_RPRN, KC_LEFT , KC_DOWN , KC_RIGHT ,KC_MINS,KC_PIPE,
        _______,_______,KC_1, KC_2, KC_3,_______,                        _______, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                        KC_0, KC_0,                                                        _______, KC_P0,
                                                _______,                            _______,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______

    ),

    [_RAISE] = LAYOUT_5x6(
          KC_F12 , KC_F1 ,KC_F10 , KC_F11 , KC_F12 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
          _______,_______,KC_F7,KC_F8,KC_F9,KC_LBRC,                        KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,KC_MUTE,
          _______,KC_LEFT,KC_F4  ,KC_F5,KC_F6,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
          _______,_______,KC_F1,KC_F2,KC_F3,_______,                        _______,_______,_______,_______,_______,KC_VOLD,
                                                  _______,                              _______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            _______,_______
    )
};
