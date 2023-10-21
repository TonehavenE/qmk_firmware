// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "print.h"
#define _COLEMAK 0
#define _NAVIGATION 1
#define _SYMBOL 2
#define _NUM 3
#define SYM MO(_SYMBOL)
#define NAV MO(_NAVIGATION)
#define NUM MO(_NUM)
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_split_3x6_3(
//    ┌─────────┬───────────┬───┬───┬─────┬─────┐               ┌─────────┬─────┬───┬───┬───────────┐
//    │ QK_GESC │     q     │ w │ f │  p  │  g  │               │    j    │  l  │ u │ y │     '     │
//    ├─────────┼───────────┼───┼───┼─────┼─────┤               ├─────────┼─────┼───┼───┼───────────┤
//    │  lsft   │     a     │ r │ s │  t  │  d  │               │    h    │  n  │ e │ i │     o     │
//    ├─────────┼───────────┼───┼───┼─────┼─────┤               ├─────────┼─────┼───┼───┼───────────┤
//    │  lctl   │ LALT_T(z) │ x │ c │  v  │  b  │               │    k    │  m  │ , │ . │ LGUI_T(;) │
//    └─────────┴───────────┴───┴───┼─────┼─────┼─────┐   ┌─────┼─────────┼─────┼───┴───┴───────────┘
//                                  │ NAV │ spc │ tab │   │ ent │ QK_LEAD │ SYM │
//                                  └─────┴─────┴─────┘   └─────┴─────────┴─────┘
  QK_GESC , KC_Q         , KC_W , KC_F , KC_P , KC_G   ,                       KC_J    , KC_L , KC_U    , KC_Y   , KC_QUOT        ,
  KC_LSFT , KC_A         , KC_R , KC_S , KC_T , KC_D   ,                       KC_H    , KC_N , KC_E    , KC_I   , KC_O           ,
  KC_LCTL , LALT_T(KC_Z) , KC_X , KC_C , KC_V , KC_B   ,                       KC_K    , KC_M , KC_COMM , KC_DOT , LGUI_T(KC_SCLN),
                                         NAV  , KC_SPC , KC_TAB ,     KC_ENT , QK_LEAD , SYM
),

[_NAVIGATION] = LAYOUT_split_3x6_3(
//    ┌─────┬─────────┬──────┬──────┬───────┬──────┐               ┌──────┬──────┬──────┬──────┬──────┐
//    │  `  │  mute   │ btn1 │ ms_u │ btn2  │ mply │               │ pgup │ home │  up  │ end  │ del  │
//    ├─────┼─────────┼──────┼──────┼───────┼──────┤               ├──────┼──────┼──────┼──────┼──────┤
//    │     │ QK_LEAD │ ms_l │ ms_d │ ms_r  │ volu │               │ pgdn │ left │ down │ rght │ bspc │
//    ├─────┼─────────┼──────┼──────┼───────┼──────┤               ├──────┼──────┼──────┼──────┼──────┤
//    │     │         │ cut  │ copy │ paste │      │               │ pscr │ ins  │      │      │      │
//    └─────┴─────────┴──────┴──────┼───────┼──────┼─────┐   ┌─────┼──────┼──────┼──────┴──────┴──────┘
//                                  │       │      │     │   │     │      │      │
//                                  └───────┴──────┴─────┘   └─────┴──────┴──────┘
  KC_GRAVE , KC_MUTE , KC_MS_BTN1 , KC_MS_U , KC_MS_BTN2 , KC_MPLY ,                         KC_PGUP , KC_HOME   , KC_UP   , KC_END   , KC_DEL ,
  _______  , QK_LEAD , KC_MS_L    , KC_MS_D , KC_MS_R    , KC_VOLU ,                         KC_PGDN , KC_LEFT   , KC_DOWN , KC_RIGHT , KC_BSPC,
  _______  , _______ , KC_CUT     , KC_COPY , KC_PASTE   , _______ ,                         KC_PSCR , KC_INSERT , _______ , _______  , _______,
                                              _______    , _______ , _______ ,     _______ , _______ , _______
),

[_SYMBOL] = LAYOUT_split_3x6_3(
//    ┌─────┬───────────────┬───────────────┬───┬─────┬─────┐                ┌─────┬─────┬───┬───┬──────┐
//    │     │       !       │       @       │ # │  $  │  %  │                │  ^  │  &  │ * │ = │ bspc │
//    ├─────┼───────────────┼───────────────┼───┼─────┼─────┤                ├─────┼─────┼───┼───┼──────┤
//    │     │       `       │       ~       │ ( │  [  │  {  │                │  }  │  ]  │ ) │ _ │  -   │
//    ├─────┼───────────────┼───────────────┼───┼─────┼─────┤                ├─────┼─────┼───┼───┼──────┤
//    │     │ OSM(MOD_LALT) │ OSM(MOD_LGUI) │ + │  /  │  ?  │                │  |  │  \  │ < │ > │  :   │
//    └─────┴───────────────┴───────────────┴───┼─────┼─────┼──────┐   ┌─────┼─────┼─────┼───┴───┴──────┘
//                                              │     │     │ bspc │   │ del │     │     │
//                                              └─────┴─────┴──────┘   └─────┴─────┴─────┘
  _______ , KC_EXLM       , KC_AT         , KC_HASH , KC_DLR  , KC_PERC ,                        KC_CIRC , KC_AMPR , KC_ASTR , KC_EQL  , KC_BSPC ,
  _______ , KC_GRV        , KC_TILDE      , KC_LPRN , KC_LBRC , KC_LCBR ,                        KC_RCBR , KC_RBRC , KC_RPRN , KC_UNDS , KC_MINS ,
  _______ , OSM(MOD_LALT) , OSM(MOD_LGUI) , KC_PLUS , KC_SLSH , KC_QUES ,                        KC_PIPE , KC_BSLS , KC_LT   , KC_GT   , KC_COLON,
                                                      _______ , _______ , KC_BSPC ,     KC_DEL , _______ , _______
),

[_NUM] = LAYOUT_split_3x6_3(
//    ┌─────┬─────┬───┬───┬─────┬─────┐                       ┌─────┬─────┬────┬────┬──────┐
//    │     │ spc │ 7 │ 8 │  9  │ f12 │                       │ f6  │ f7  │ f8 │ f9 │ bspc │
//    ├─────┼─────┼───┼───┼─────┼─────┤                       ├─────┼─────┼────┼────┼──────┤
//    │     │  0  │ 4 │ 5 │  6  │ f11 │                       │ f1  │ f2  │ f3 │ f4 │  f5  │
//    ├─────┼─────┼───┼───┼─────┼─────┤                       ├─────┼─────┼────┼────┼──────┤
//    │     │  +  │ 1 │ 2 │  3  │ f10 │                       │ f12 │  =  │ ,  │ .  │  -   │
//    └─────┴─────┴───┴───┼─────┼─────┼─────────┐   ┌─────────┼─────┼─────┼────┴────┴──────┘
//                        │     │ spc │ QK_BOOT │   │ QK_BOOT │     │     │
//                        └─────┴─────┴─────────┘   └─────────┴─────┴─────┘
  _______ , KC_SPC  , KC_7 , KC_8 , KC_9    , KC_F12 ,                         KC_F6   , KC_F7   , KC_F8   , KC_F9  , KC_BSPC,
  _______ , KC_0    , KC_4 , KC_5 , KC_6    , KC_F11 ,                         KC_F1   , KC_F2   , KC_F3   , KC_F4  , KC_F5  ,
  _______ , KC_PLUS , KC_1 , KC_2 , KC_3    , KC_F10 ,                         KC_F12  , KC_EQL  , KC_COMM , KC_DOT , KC_MINS,
                                    _______ , KC_SPC , QK_BOOT ,     QK_BOOT , _______ , _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _NAVIGATION, _SYMBOL, _NUM);
}
void keyboard_post_init_user(void) {
    // debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif
  return true;
}

void leader_end_user(void) {
    // Text editing
    if (leader_sequence_one_key(KC_ESC)) {
        ; // nothing on esc!
    }
    else if (leader_sequence_two_keys(KC_D, KC_W)) {
        // delete word
        SEND_STRING(SS_LCTL(SS_TAP(X_BSPC)));
    }
    else if (leader_sequence_two_keys(KC_D, KC_N)) {
        // delete next
        SEND_STRING(SS_LCTL(SS_TAP(X_DEL)));
    }
    else if (leader_sequence_two_keys(KC_G, KC_H)) {
        // go home
        SEND_STRING(SS_LCTL(SS_TAP(X_HOME)));
    }
    else if (leader_sequence_two_keys(KC_G, KC_E)) {
        // go end
        SEND_STRING(SS_LCTL(SS_TAP(X_END)));
    }
    else if (leader_sequence_two_keys(KC_S, KC_A)) {
        // select all
        SEND_STRING(SS_LCTL(SS_LSFT("a")));
    }
    else if (leader_sequence_two_keys(KC_S, KC_N)) {
        // select next
        SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT))));
    }
    else if (leader_sequence_two_keys(KC_S, KC_P)) {
        // select previous
        SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_LEFT))));
    }
    // Tabs
    else if (leader_sequence_two_keys(KC_C, KC_T)) {
        SEND_STRING(SS_LCTL(SS_LSFT("t")));
    }
    else if (leader_sequence_two_keys(KC_O, KC_T)) {
        SEND_STRING(SS_LCTL("t"));
    }
    // Media controls
    else if (leader_sequence_two_keys(KC_M, KC_S)) {
        tap_code16(KC_MPLY);
    }
    else if (leader_sequence_two_keys(KC_M, KC_U)) {
        tap_code16(KC_VOLU);
    }
    else if (leader_sequence_two_keys(KC_M, KC_D)) {
        tap_code16(KC_VOLD);
    }
    else if (leader_sequence_two_keys(KC_M, KC_N)) {
        tap_code16(KC_MNXT);
    }
    else if (leader_sequence_two_keys(KC_M, KC_P)) {
        tap_code16(KC_MPRV);
    }
    // Lighting / RGB controls
    else if (leader_sequence_two_keys(KC_R, KC_T)) {
        rgb_matrix_toggle();
    }
    else if (leader_sequence_two_keys(KC_R, KC_N)) {
        rgb_matrix_step();
    }
    else if (leader_sequence_two_keys(KC_R, KC_P)) {
        rgb_matrix_step_reverse();
    }
    else if (leader_sequence_two_keys(KC_R, KC_U)) {
        rgb_matrix_increase_val();
    }
    else if (leader_sequence_two_keys(KC_R, KC_D)) {
        rgb_matrix_decrease_val();
    }
    // Open Applications
    else if (leader_sequence_two_keys(KC_O, KC_C)) {
        tap_code16(KC_CALC);
    }
    // Email and Phone
    // Email/Student
    else if (leader_sequence_two_keys(KC_E, KC_S)) {
        SEND_STRING("student.equenneville@gmail.com");
    }
    // Email/Personal
    else if (leader_sequence_two_keys(KC_E, KC_P)) {
        SEND_STRING("tonehaven@outlook.com");
    }
    // Email/College
    else if (leader_sequence_two_keys(KC_E, KC_C)) {
        SEND_STRING("EQuenneville066@students.ccsnh.edu");
    }
    // Phone/Personal
    else if (leader_sequence_two_keys(KC_P, KC_P)) {
        SEND_STRING("(603) 484-0402");
    }
    // Phone/Home
    else if (leader_sequence_two_keys(KC_P, KC_H)) {
        SEND_STRING("(603) 262-5730");
    }

    // Markdown Shortcuts

    // Markdown/Template
    else if (leader_sequence_two_keys(KC_M, KC_T)) {
        SEND_STRING(SS_LALT("e"));
    }
    // Markdown/YAML Frontmatter
    else if (leader_sequence_two_keys(KC_M, KC_Y)) {
        SEND_STRING("---" SS_TAP(X_ENTER) "tags: " SS_TAP(X_ENTER) "---" SS_TAP(X_UP) SS_TAP(X_END));
    }

    // LaTeX

    // LaTeX/Symbols

    // Pi
    else if (leader_sequence_three_keys(KC_L, KC_S, KC_P)) {
        SEND_STRING("\\pi");
    }
    // Delta
    else if (leader_sequence_three_keys(KC_L, KC_S, KC_D)) {
        SEND_STRING("\\Delta");
    }
    // Sigma
    else if (leader_sequence_three_keys(KC_L, KC_S, KC_S)) {
        SEND_STRING("\\Sigma");
    }

    // Latex/Fraction
    else if (leader_sequence_two_keys(KC_L, KC_F)) {
        SEND_STRING("\\frac{}{}" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) );
    }
    // Latex/Times
    else if (leader_sequence_two_keys(KC_L, KC_T)) {
        SEND_STRING("\\times ");
    }

    // Latex/Units/Meter
    else if (leader_sequence_three_keys(KC_L, KC_U, KC_M)) {
        SEND_STRING("\\text{ m}");
    }
    // Latex/Units/Meter/Second
    else if (leader_sequence_four_keys(KC_L, KC_U, KC_M, KC_S)) {
        SEND_STRING("\\text{ m/s}");
    }
    // Latex/Units/Second
    else if (leader_sequence_three_keys(KC_L, KC_U, KC_S)) {
        SEND_STRING("\\text{ s}");
    }
    // Latex/Units/kg
    else if (leader_sequence_three_keys(KC_L, KC_U, KC_K)) {
        SEND_STRING("\\text{ kg}");
    }

    // Latex/Integral
    else if (leader_sequence_two_keys(KC_L, KC_I)) {
        SEND_STRING("\\int_{}^{}{ d}");
    }

    // Latex/Tex/T
    else if (leader_sequence_two_keys(KC_T, KC_T)) {
        SEND_STRING("\\text{}" SS_TAP(X_LEFT));
    }

    // Latex/Hat/I
    else if (leader_sequence_three_keys(KC_L, KC_H, KC_I)) {
        SEND_STRING("\\hat{\\textbf{i}}");
    }
    // Latex/Hat/J
    else if (leader_sequence_three_keys(KC_L, KC_H, KC_J)) {
        SEND_STRING("\\hat{\\textbf{j}}");
    }
    // Latex/Hat/K
    else if (leader_sequence_three_keys(KC_L, KC_H, KC_K)) {
        SEND_STRING("\\hat{\\textbf{K}}");
    }

    // Latex/Trig/Sin
    else if (leader_sequence_three_keys(KC_L, KC_T, KC_S)) {
        SEND_STRING("\\sin{}" SS_TAP(X_LEFT));
    }
    // Latex/Trig/Cos
    else if (leader_sequence_three_keys(KC_L, KC_T, KC_C)) {
        SEND_STRING("\\cos{}" SS_TAP(X_LEFT));
    }
    // Latex/Trig/Tan
    else if (leader_sequence_three_keys(KC_L, KC_T, KC_T)) {
        SEND_STRING("\\tan{}" SS_TAP(X_LEFT));
    }
    // Latex/Trig/Se/Cant
    else if (leader_sequence_four_keys(KC_L, KC_T, KC_S, KC_C)) {
        SEND_STRING("\\sec{}" SS_TAP(X_LEFT));
    }
    // Latex/Trig/Arc/Sin
    else if (leader_sequence_four_keys(KC_L, KC_T, KC_A, KC_S)) {
        SEND_STRING("\\arcsin{}" SS_TAP(X_LEFT));
    }
    // Latex/Trig/Arc/Cos
    else if (leader_sequence_four_keys(KC_L, KC_T, KC_A, KC_C)) {
        SEND_STRING("\\arccos{}" SS_TAP(X_LEFT));
    }
    // Latex/Trig/Arc/Tan
    else if (leader_sequence_four_keys(KC_L, KC_T, KC_A, KC_T)) {
        SEND_STRING("\\arctan{}" SS_TAP(X_LEFT));
    }
}
