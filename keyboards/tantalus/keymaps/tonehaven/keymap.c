#include QMK_KEYBOARD_H
#include "combo.c"
#include "sensor.h"
#include "sensor.c"

#define _COLEMAK 0
#define _NAV 1
#define _MOUSE 2
#define _FUNC 3
#define _NSL 4
#define _NSSL 5

#define LT_Z LT(_FUNC, KC_Z)
#define LT_TAB LT(_NSSL, KC_TAB)
#define LT_BSPC LT(_NSL, KC_BSPC)
#define LT_SPC LT(_NAV, KC_SPC)
#define LT_ENT LT(_MOUSE, KC_ENT)
#define KC_RST RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
	[_COLEMAK] = LAYOUT(
		KC_Q, KC_W        , KC_F        , KC_P        , KC_G  ,   KC_RBRC,    KC_J, KC_L        , KC_U        , KC_Y        , KC_SCLN,
		KC_A, LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_D  ,   KC_LBRC,    KC_H, RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), KC_O   ,
		LT_Z, KC_X        , KC_C        , KC_V        , KC_B  ,   KC_LPRN,    KC_K, KC_M        , KC_COMM     , KC_DOT      , KC_SLSH,
				                LT_TAB      , LT_SPC      , LT_ENT,   KC_RPRN,       LT_BSPC
		),
  [_NAV] = LAYOUT(
    _______, _______, _______, _______, _______, KC_RST, KC_INSERT, C(KC_LEFT)  , KC_UP  , C(KC_RIGHT) , _______,
    KC_LGUI, KC_LALT, KC_LCTL, _______, _______, KC_RST, KC_PGUP  , KC_LEFT     , KC_DOWN, KC_RIGHT    , KC_RGHT,
    _______, _______, _______, _______, _______, KC_RST, KC_PGDN  , RCS(KC_LEFT), _______, RCS(KC_RGHT), _______,
                      _______, _______, _______, KC_RST,            KC_DEL
    ),
  [_MOUSE] = LAYOUT(
    _______, _______, _______, _______, _______, KC_RST, KC_CPI_UP  , KC_SCROLLMODE, KC_CURSORMODE, KC_CARRETMODE, KC_CPI_STD ,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, KC_RST, KC_CPI_DOWN, KC_BTN1, KC_BTN2, KC_BTN3, KC_CRT_UP  ,
    _______, _______, _______, _______, _______, KC_RST, KC_WH_L , KC_WH_U, KC_WH_D, KC_WH_R, KC_CRT_DOWN,
                      _______, _______, _______, KC_RST,          _______
    ),
  [_FUNC] = LAYOUT(
    _______, KC_F12, KC_F7, KC_F8, KC_F9, KC_RST, _______, _______, _______, _______, _______,
    _______, KC_F11, KC_F4, KC_F5, KC_F6, KC_RST, _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
    _______, KC_F10, KC_F1, KC_F2, KC_F3, KC_RST, _______, _______, _______, _______, _______,
               _______, _______, _______, KC_RST,          _______
    ),
  [_NSL] = LAYOUT(
    _______, KC_7, KC_8, KC_9, _______, KC_RST, _______, _______, _______, _______, _______,
    _______, KC_4, KC_5, KC_6, _______, KC_RST, _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
    _______, KC_1, KC_2, KC_3, _______, KC_RST, _______, _______, _______, _______, _______,
                _______, KC_0, _______, KC_RST,          _______
    ),
  [_NSSL] = LAYOUT(
    _______, S(KC_7), S(KC_8), S(KC_9), _______, KC_RST, _______, _______, _______, _______, _______,
    _______, S(KC_4), S(KC_5), S(KC_6), _______, KC_RST, _______, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
    _______, S(KC_1), S(KC_2), S(KC_3), _______, KC_RST, _______, _______, _______, _______, _______,
             _______, S(KC_0), _______,          KC_RST,          _______
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
