// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#define _COLEMAK 0
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_split_3x6_3(
//        ┌──────┬───┬───┬───┬──────┬──────┐               ┌─────┬──────┬───┬───┬───┐
//        │ esc  │ q │ w │ f │  p   │  g   │               │  j  │  l   │ u │ y │ ; │
//        ├──────┼───┼───┼───┼──────┼──────┤               ├─────┼──────┼───┼───┼───┤
//        │ lsft │ a │ r │ s │  t   │  d   │               │  h  │  n   │ e │ i │ o │
//        ├──────┼───┼───┼───┼──────┼──────┤               ├─────┼──────┼───┼───┼───┤
//        │ lctl │ z │ x │ c │  v   │  b   │               │  k  │  m   │ , │ . │ / │
//        └──────┴───┴───┴───┼──────┼──────┼─────┐   ┌─────┼─────┼──────┼───┴───┴───┘
//                           │ lgui │ bspc │ spc │   │ spc │ ent │ ralt │
//                           └──────┴──────┴─────┘   └─────┴─────┴──────┘
      KC_ESC  , KC_Q , KC_W , KC_F , KC_P    , KC_G    ,                       KC_J   , KC_L    , KC_U    , KC_Y   , KC_SCLN    ,
      KC_LSFT , KC_A , KC_R , KC_S , KC_T    , KC_D    ,                       KC_H   , KC_N    , KC_E    , KC_I   , KC_O       ,
      KC_LCTL , KC_Z , KC_X , KC_C , KC_V    , KC_B    ,                       KC_K   , KC_M    , KC_COMM , KC_DOT , KC_SLSH    ,
                                     KC_LGUI , KC_BSPC , KC_SPC ,     KC_SPC , KC_ENT , KC_RALT
)
};
