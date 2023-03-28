#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _GAME 1
#define _RAISE 2
#define _FUNC 3

#define RAISE MO(_RAISE)
#define LT_FUNC LT(_FUNC, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_ortho_5x12(
        KC_GESC, KC_1,    KC_2,    KC_3 ,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_EQL,
        KC_LALT, KC_Q,    KC_W,    KC_F ,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,   KC_SCLN,
        KC_LSFT, KC_A,    KC_R,    KC_S ,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,      KC_RSFT,
        KC_LCTL, KC_Z,    KC_X,    KC_C ,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_MINS,
                 KC_LPRN, KC_RPRN, RAISE,    KC_SPC,  KC_TAB,  KC_LGUI, LT_FUNC, KC_BSPC, KC_LBRC, KC_RBRC
    ),
    [_GAME] = LAYOUT_ortho_5x12(
        KC_ESC , KC_5,    KC_1,    KC_2,    KC_3,    KC_4,    KC_6,    KC_7,    KC_8,    KC_9,   KC_0   , KC_EQL,
        KC_TAB , KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_J,    KC_L,    KC_U,    KC_Y,   KC_QUOT, KC_SCLN,
        KC_LSFT, KC_G,    KC_A,    KC_S,    KC_D,    KC_F,    KC_H,    KC_N,    KC_E,    KC_I,   KC_O   , KC_RSFT,
        KC_LCTL, KC_B,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_K,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
                 KC_F3,   KC_F12,  KC_LALT, KC_SPC,  MO(_FUNC), _______, _______, _______, TG(_GAME), TG(_GAME)
    ),
    [_RAISE] = LAYOUT_ortho_5x12(
        KC_GRAVE, _______,    _______,  KC_0   ,  _______,  _______,        _______,  KC_DEL ,  _______,  _______  ,  _______  , _______,
        _______ , _______,    KC_7   ,  KC_8   ,  KC_9   ,  _______,        _______,  KC_HOME,  KC_UP  ,  KC_END   ,  _______  , _______,
        _______ , KC_0   ,    KC_4   ,  KC_5   ,  KC_6   ,  _______,        _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT ,  _______  , _______,
        _______ , _______,    KC_1   ,  KC_2   ,  KC_3   ,  _______,        _______,  _______,  _______,  _______  ,  _______  , _______,
                  _______,    _______,  _______,  _______,  _______,        KC_BSLS,  _______,  KC_DEL ,  TG(_GAME),  TG(_GAME)
    ),
    [_FUNC] = LAYOUT_ortho_5x12(
        _______ , _______,    KC_F10 ,  KC_F11 ,  KC_F12 ,  _______,        RGB_TOG,  RGB_MOD,  RGB_RMOD,  _______,  _______, RESET  ,
        _______ , _______,    KC_F7  ,  KC_F8  ,  KC_F9  ,  _______,        _______,  RGB_HUI,  RGB_HUD,  _______,  _______, _______,
        _______ , KC_LGUI,    KC_F4  ,  KC_F5  ,  KC_F6  ,  _______,        _______,  RGB_SAI,  RGB_SAD,  KC_RALT,  KC_LGUI, _______,
        _______ , _______,    KC_F1  ,  KC_F2  ,  KC_F3  ,  _______,        _______,  RGB_VAI,  RGB_VAD,  _______,  _______, _______,
                  _______,    _______,  _______,  _______,  _______,        _______,  _______,  _______,  TG(_GAME),  TG(_GAME)
    )
};
layer_state_t layer_state_set_user(layer_state_t state) {
	uint8_t value = rgb_matrix_get_val();
	switch (get_highest_layer(state)) {
		case _GAME:
			rgb_matrix_sethsv(23, 234, value); // peach
			break;
		case _RAISE:
			rgb_matrix_sethsv(189, 181, value); // sky
			break;
		case _FUNC:
			rgb_matrix_sethsv(232, 247, value); // lavendar
			break;
		default:
			rgb_matrix_sethsv(115, 137, value); // green 
		//	rgb_matrix_sethsv(85, 140, 121);
			break;
	}
	return state;
}
/*
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	HSV hsv = {0, 255, 255};

	if (layer_state_is(layer_state, 1)) {
				hsv = {130, 255, 255};
			} else {
				hsv = {30, 255, 255};
			}

	if (hsv.v > rgb_matrix_get_val()) {
		hsv.v = rgb_matrix_get_val();
	}
	RGB rgb = hsv_to_rgb(hsv);

	for (uint8_t i = led_min; i <= led_max; i++) {
		rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
	}
}
*/
