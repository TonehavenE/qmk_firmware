#include QMK_KEYBOARD_H
#include "combo.c"
#include "sensor.h"
#include "sensor.c"

#define _COLEMAK 0
#define _NAV 1
#define _FUNC 2
#define _NUM 3

#define LT_TAB LT(_NAV, KC_TAB)
#define LT_BSPC LT(_NUM, KC_BSPC)
//#define LT_SPC LT(_NAV, KC_SPC)
#define LT_ENT LT(_FUNC, KC_ENT)

#define SFT_Z LSFT_T(KC_Z)
#define CTL_X LCTL_T(KC_X)
#define GUI_C LGUI_T(KC_C)
#define ALT_V LALT_T(KC_V)
#define SFT_SLSH LSFT_T(KC_SLSH)
#define KC_CM KC_COMM

#define KC_RST RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
	[_COLEMAK] = LAYOUT(
		KC_Q , KC_W , KC_F, KC_P , KC_G,   KC_RBRC,    KC_J, KC_L, KC_U , KC_Y  , KC_QUOT ,
		KC_A , KC_R , KC_S, KC_T , KC_D,   KC_LBRC,    KC_H, KC_N, KC_E , KC_I  , KC_O    ,
		SFT_Z, CTL_X, KC_C, ALT_V, KC_B,   KC_LPRN,    KC_K, KC_M, KC_CM, KC_DOT, SFT_SLSH,
			    LT_TAB, KC_SPC, LT_ENT  ,   KC_RPRN,       LT_BSPC
	),
  [_NAV] = LAYOUT(
    _______, C(KC_HOME), C(KC_UP)  , C(KC_END)  , _______, KC_RST, _______, KC_HOME, KC_UP  , KC_END  , _______,
    KC_LGUI, C(KC_LEFT), C(KC_DOWN), C(KC_RIGHT), _______, KC_RST, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,
    _______, _______   , _______   , _______    , _______, KC_RST, _______, _______, _______, _______ , _______,
                                _______, _______, _______, KC_RST,          KC_DEL
    ),
  [_FUNC] = LAYOUT(
     KC_F12, KC_F7, KC_F8, KC_F9, _______, KC_RST, _______, _______, _______, _______, _______,
     KC_F11, KC_F4, KC_F5, KC_F6, _______, KC_RST, _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
     KC_F10, KC_F1, KC_F2, KC_F3, _______, KC_RST, _______, _______, _______, _______, _______,
                _______, _______, _______, KC_RST,          _______
    ),
  [_NUM] = LAYOUT(
    S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), _______, S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0),
    KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,
    _______, _______, _______, _______, _______, _______, KC_EQL , KC_EQL , KC_SLSH, S(KC_8), KC_MINS,
                      _______, _______, _______, _______,          _______
    )
    // clang-format on
};

#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    debug_matrix = true;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_Z:
            return TAPPING_TERM;
        case CTL_X:
            return TAPPING_TERM + 1000;
        case ALT_V:
            return TAPPING_TERM + 1000;
        default:
            return TAPPING_TERM;
    }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_X:
            return true;
        case ALT_V:
            return true;
        default:
            return false;
    }
}
