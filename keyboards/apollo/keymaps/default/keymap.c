// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#define _COLEMAK 0
#define _NAVIGATION 1
#define _SYMBOL 3
#define _NUM 2
#define SYM MO(_SYMBOL)
#define NAV MO(_NAVIGATION)
#define NUM MO(_NUM)
// clang-format off
// Note: On the colemak layer, L_BOOT should become GESC, and R_BOOT = QUOT
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_split_3x6_3(
//    ┌─────────┬───┬───┬───┬─────┬─────┐                ┌─────┬─────┬───┬───┬─────────┐
//    │ QK_BOOT │ q │ w │ f │  p  │  g  │                │  j  │  l  │ u │ y │ QK_BOOT │
//    ├─────────┼───┼───┼───┼─────┼─────┤                ├─────┼─────┼───┼───┼─────────┤
//    │  lsft   │ a │ r │ s │  t  │  d  │                │  h  │  n  │ e │ i │    o    │
//    ├─────────┼───┼───┼───┼─────┼─────┤                ├─────┼─────┼───┼───┼─────────┤
//    │  lctl   │ z │ x │ c │  v  │  b  │                │  k  │  m  │ , │ . │    /    │
//    └─────────┴───┴───┴───┼─────┼─────┼─────┐   ┌──────┼─────┼─────┼───┴───┴─────────┘
//                          │ NAV │ spc │ tab │   │ bspc │ ent │ NUM │
//                          └─────┴─────┴─────┘   └──────┴─────┴─────┘
  QK_BOOT , KC_Q , KC_W , KC_F , KC_P , KC_G   ,                        KC_J   , KC_L , KC_U    , KC_Y   , QK_BOOT,
  KC_LSFT , KC_A , KC_R , KC_S , KC_T , KC_D   ,                        KC_H   , KC_N , KC_E    , KC_I   , KC_O   ,
  KC_LCTL , KC_Z , KC_X , KC_C , KC_V , KC_B   ,                        KC_K   , KC_M , KC_COMM , KC_DOT , KC_SLSH,
                                 NAV  , KC_SPC , KC_TAB ,     KC_BSPC , KC_ENT , NUM
),

[_NAVIGATION] = LAYOUT_split_3x6_3(
//    ┌─────┬──────┬──────┬──────┬──────┬──────┐               ┌─────┬──────┬──────┬──────┬──────┐
//    │     │      │ btn1 │ ms_u │ btn2 │      │               │     │ home │  up  │ end  │ del  │
//    ├─────┼──────┼──────┼──────┼──────┼──────┤               ├─────┼──────┼──────┼──────┼──────┤
//    │     │ lgui │ ms_l │ ms_d │ ms_r │ lalt │               │     │ left │ down │ rght │ bspc │
//    ├─────┼──────┼──────┼──────┼──────┼──────┤               ├─────┼──────┼──────┼──────┼──────┤
//    │     │      │      │      │      │      │               │     │      │      │      │      │
//    └─────┴──────┴──────┴──────┼──────┼──────┼─────┐   ┌─────┼─────┼──────┼──────┴──────┴──────┘
//                               │      │      │     │   │     │     │ SYM  │
//                               └──────┴──────┴─────┘   └─────┴─────┴──────┘
  _______ , _______ , KC_MS_BTN1 , KC_MS_U , KC_MS_BTN2 , _______ ,                         _______ , KC_HOME , KC_UP   , KC_END   , KC_DEL ,
  _______ , KC_LGUI , KC_MS_L    , KC_MS_D , KC_MS_R    , KC_LALT ,                         _______ , KC_LEFT , KC_DOWN , KC_RIGHT , KC_BSPC,
  _______ , _______ , _______    , _______ , _______    , _______ ,                         _______ , _______ , _______ , _______  , _______,
                                             _______    , _______ , _______ ,     _______ , _______ , SYM
),

[_NUM] = LAYOUT_split_3x6_3(
//    ┌─────┬───┬───┬───┬─────┬─────┐             ┌─────┬──────┬──────┬──────┬──────┐
//    │     │ * │ 7 │ 8 │  9  │  =  │             │     │      │      │  ;   │ bspc │
//    ├─────┼───┼───┼───┼─────┼─────┤             ├─────┼──────┼──────┼──────┼──────┤
//    │     │ / │ 4 │ 5 │  6  │  +  │             │     │ rsft │ rctl │ ralt │ rgui │
//    ├─────┼───┼───┼───┼─────┼─────┤             ├─────┼──────┼──────┼──────┼──────┤
//    │     │ ^ │ 1 │ 2 │  3  │  -  │             │     │      │      │      │      │
//    └─────┴───┴───┴───┼─────┼─────┼───┐   ┌─────┼─────┼──────┼──────┴──────┴──────┘
//                      │ SYM │ spc │ 0 │   │     │     │      │
//                      └─────┴─────┴───┘   └─────┴─────┴──────┘
  _______ , KC_ASTR , KC_7 , KC_8 , KC_9 , KC_EQL  ,                      _______ , _______ , _______ , KC_SCLN , KC_BSPC,
  _______ , KC_SLSH , KC_4 , KC_5 , KC_6 , KC_PLUS ,                      _______ , KC_RSFT , KC_RCTL , KC_RALT , KC_RGUI,
  _______ , KC_CIRC , KC_1 , KC_2 , KC_3 , KC_MINS ,                      _______ , _______ , _______ , _______ , _______,
                                    SYM  , KC_SPC  , KC_0 ,     _______ , _______ , _______
),

[_SYMBOL] = LAYOUT_split_3x6_3(
//    ┌─────┬──────┬────┬────┬─────┬─────┐                       ┌─────┬─────┬────┬────┬──────┐
//    │     │ '--' │ $  │ %  │  ^  │  *  │                       │  `  │  ~  │ _  │ ;  │ bspc │
//    ├─────┼──────┼────┼────┼─────┼─────┤                       ├─────┼─────┼────┼────┼──────┤
//    │     │  !   │ @  │ (  │  [  │  {  │                       │  }  │  ]  │ )  │ &  │  -   │
//    ├─────┼──────┼────┼────┼─────┼─────┤                       ├─────┼─────┼────┼────┼──────┤
//    │     │  f1  │ f2 │ f3 │ f4  │ f5  │                       │ f6  │ f7  │ f8 │ f9 │ f10  │
//    └─────┴──────┴────┴────┼─────┼─────┼─────────┐   ┌─────────┼─────┼─────┼────┴────┴──────┘
//                           │     │     │ QK_BOOT │   │ QK_BOOT │     │     │
//                           └─────┴─────┴─────────┘   └─────────┴─────┴─────┘
  _______ , KC_HASH , KC_DLR , KC_PERC , KC_CIRC , KC_ASTR ,                         KC_GRV  , KC_TILDE , KC_UNDS , KC_SCLN , KC_BSPC,
  _______ , KC_EXLM , KC_AT  , KC_LPRN , KC_LBRC , KC_LCBR ,                         KC_RCBR , KC_RBRC  , KC_RPRN , KC_AMPR , KC_MINS,
  _______ , KC_F1   , KC_F2  , KC_F3   , KC_F4   , KC_F5   ,                         KC_F6   , KC_F7    , KC_F8   , KC_F9   , KC_F10 ,
                                         _______ , _______ , QK_BOOT ,     QK_BOOT , _______ , _______
)
};

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;
}
