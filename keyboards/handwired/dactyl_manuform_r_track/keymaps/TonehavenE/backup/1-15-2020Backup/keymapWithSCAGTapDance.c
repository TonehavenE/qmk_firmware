/* Copyright 2020 Qurn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>.
 */

/***************************
 * Usual defines
 **************************/

#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _QWERTY 1
#define _MOUSE 2
#define _NAVIGATION 3
#define _MATH 4
#define _FNKeys 5
#define _UNICODE 6

enum custom_keycodes {
  COLEMAK,
  QWERTY,
  MOUSE,
  NAVIGATION,
  MATH,
  FNKeys,
  UNICODE,
  KC_CURSORMODE,
  KC_SCROLLMODE,
  KC_CARRETMODE,
  KC_CPI_DOWN,
  KC_CPI_STD,
  KC_CPI_UP,
  KC_SMO_SC,
};

// Defining the names for Unicode
enum unicode_names {
	PlusMinus,
	SQRT,
	Divide,
	Dash,
	CubeRoot,
	FourthRoot,
	Infinity,
	Delta,
	Theta,
	Pi,
	Alpha,
	Beta,
	NotEqual,
	Farenheit,
	Degree,
	Angle,
	mesAngle,
	ApproxEqual,
	FirstPower,
	Squared,
	Cubed,
	FourthPower,
	FifthPower,
	SixthPower,
	SeventhPower,
	EigthPower,
	NinethPower,
	Integral
};

// Defining the unicode symbols
const uint32_t PROGMEM unicode_map[] = {
	[PlusMinus] = 0x00B1,     // ±
	[SQRT]      = 0x221A,     // √
	[Divide]    = 0x00F7,     // ÷
	[Dash]      = 0x2014,     // —
	[CubeRoot]  = 0x221B,     //∛
	[FourthRoot]= 0x221C,     //∜
	[Infinity]  = 0x221E,     // not programmed, oops. 
	[Theta]     = 0x0398,     //Θ
	[Pi]        = 0x03C0,     //π
	[Alpha]     = 0x03B1,     //α
	[Beta]      = 0x03B2,     //β
	[Delta]     = 0x0394,     //Δ
	[NotEqual]  = 0x2260,     //≠
	[Farenheit] = 0x2109,     //℉
	[Degree]    = 0x00B0,     //°
	[Angle]     = 0x2220,     //∠
	[mesAngle]  = 0x2221,     //∡
	[ApproxEqual] = 0x2245,   //≅
	[FirstPower]  = 0x00B9,   //
	[Squared]     = 0x00B2,   //²
	[Cubed]       = 0x00B3,   //³
  [FourthPower] = 0x2074,   //⁴
  [FifthPower]  = 0x2075,   //⁵
  [SixthPower]  = 0x2076,   //⁶
  [SeventhPower] =0x2077,   //
  [EigthPower]  = 0x2078,   //
  [NinethPower] = 0x2079,   //
  [Integral]    = 0x222B    //
};

/***************************
 * Trackball related defines
 **************************/

#include "pointing_device.h"
#include "../../pmw3360/pmw3360.h"

uint8_t track_mode = 0; // 0 Mousecursor; 1 arrowkeys/carret; 2 scrollwheel; 3 sound/brightness
#define cursor_mode 0
#define carret_mode 1
#define scroll_mode 2
#define sound_brightness_mode 3
uint8_t prev_track_mode = 0;
bool integration_mode = false;
int16_t cum_x = 0;
int16_t cum_y = 0;
int16_t sensor_x = 0;
int16_t sensor_y = 0;

// Thresholds help to move only horizontal or vertical. When accumulated distance reaches threshold, only move one discrete value in direction with bigger delta.
uint8_t	carret_threshold = 24;		 // higher means slower
uint16_t carret_threshold_inte = 340; // in integration mode higher threshold

#define regular_smoothscroll_factor 8
bool smooth_scroll = true;
uint8_t	scroll_threshold = 8 / regular_smoothscroll_factor;	// divide if started smooth
uint16_t scroll_threshold_inte = 1200 / regular_smoothscroll_factor;

uint16_t cursor_multiplier = 250;	// adjust cursor speed
uint16_t cursor_multiplier_inte = 20;
#define CPI_STEP 20

int16_t cur_factor;

/***************************
 * Sticky key related defines
 **************************/

//identify keycombinations
bool is_alt_active = false;
bool is_sft_active = false;
bool is_ctl_active = false;
bool is_gui_active = false;

bool activate_alt = false;
bool activate_sft = false;
bool activate_ctl = false;
bool activate_gui = false;

bool sticky_key = false;
uint32_t sticky_timer = 0;
#define STICKY_TERM 500

/***************************
 * Tap dance 1 of 2
 **************************/

// tapdance keycodes
enum td_keycodes {
	ALT_TM,
	SFT_TM,
	CTL_TM,
	GUI_TM,
};

// define a type containing as many tapdance states as you need
typedef enum {
	SINGLE_TAP,
	SINGLE_HOLD
} td_state_t;

// create a global instance of the tapdance state type
static td_state_t td_state;

// function to determine the current tapdance state
int cur_dance (qk_tap_dance_state_t *state);

//// `finished` and `reset` functions for each tapdance keycode
void alttm_finished (qk_tap_dance_state_t *state, void *user_data);
void alttm_reset (qk_tap_dance_state_t *state, void *user_data);
void sfttm_finished (qk_tap_dance_state_t *state, void *user_data);
void sfttm_reset (qk_tap_dance_state_t *state, void *user_data);
void ctltm_finished (qk_tap_dance_state_t *state, void *user_data);
void ctltm_reset (qk_tap_dance_state_t *state, void *user_data);
void guitm_finished (qk_tap_dance_state_t *state, void *user_data);
void guitm_reset (qk_tap_dance_state_t *state, void *user_data);

/***************************
 * Mouse pressed
 **************************/

void on_mouse_button(uint8_t mouse_button, bool pressed) {
	report_mouse_t report = pointing_device_get_report();

	if(pressed)
		report.buttons |= mouse_button;
	else
		report.buttons &= ~mouse_button;
	pointing_device_set_report(report);
	pointing_device_send();
}

/***************************
 * Combos
 **************************/

enum combos_events {
	RS_MOUSE,
	ST_MOUSE,
	RT_MOUSE
};

const uint16_t PROGMEM rsm_combo[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM stm_combo[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM rtm_combo[] = {KC_R, KC_T, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
	[RS_MOUSE] = COMBO_ACTION(rsm_combo),
	[ST_MOUSE] = COMBO_ACTION(stm_combo),
	[RT_MOUSE] = COMBO_ACTION(rtm_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
	switch(combo_index) {
	case RS_MOUSE:
		on_mouse_button(MOUSE_BTN2, pressed);
		break;
	case ST_MOUSE:
		on_mouse_button(MOUSE_BTN1, pressed);
		break;
	case RT_MOUSE:
		on_mouse_button(MOUSE_BTN3, pressed);
		break;
	}
}

//Matrix Logging in Debug Mode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
  return true;
}


// non-KC_ keycodes
#define KC_RST RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[COLEMAK] = LAYOUT_5x6(
KC_ESC   , KC_1 ,   KC_2 , KC_3    , KC_4         , KC_5   ,               KC_6    ,    KC_7 , KC_8      , KC_9      , KC_0        , KC_EQUAL     ,
KC_LALT  , KC_Q ,   KC_W , KC_F    , KC_P         , KC_G   ,               KC_J    ,    KC_L , KC_U      , KC_Y      , KC_SCOLON   , KC_MINUS     ,
KC_LSFT  , KC_A ,   KC_R , KC_S    , KC_T         , KC_D   ,               KC_H    ,    KC_N , KC_E      , KC_I      , KC_O        , OSM(MOD_RSFT),
KC_LCTL  , KC_Z ,   KC_X , KC_C    , KC_V         , KC_B   ,               KC_K    ,    KC_M , KC_COMM   , KC_DOT    , KC_SLASH    , KC_QUOTE     ,
                           KC_LBRACKET, KC_RBRACKET,                                      TG(QWERTY), TG(MOUSE),
                                  LT(UNICODE, KC_TAB), LT(NAVIGATION, KC_SPACE),           _______  , LT(FNKeys, KC_BSPC),
                                  LT(MATH, KC_EQUAL) , KC_END                  ,           _______  , KC_ENTER,
                                  KC_BSLASH          , X(Dash)                 ,           KC_DELETE, KC_HOME
),

[QWERTY] = LAYOUT_5x6(
KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                              KC_6  , KC_7  , KC_8  , KC_9   , KC_0  ,KC_DELETE,
KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                              KC_Y  , KC_U  , KC_I  , KC_O   , KC_P  ,KC_MINUS,
KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                              KC_H  , KC_J  , KC_K  , KC_L   ,KC_SCLN,KC_QUOTE,
KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                              KC_N  , KC_M  , KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                      KC_LBRC,KC_RBRC,                                                _______, KC_EQL,
                                  LT(UNICODE, KC_TAB), LT(NAVIGATION, KC_SPACE),           _______  , KC_BSPC,
                                  LT(MATH, KC_EQUAL) , KC_END                  ,           _______  , KC_ENTER,
                                  KC_LALT            , X(Dash)                 ,           KC_DELETE, KC_HOME
),

[MOUSE] = LAYOUT_5x6(
_______, _______, _______, _______, _______, _______,                        KC_CPI_DOWN, KC_CPI_STD   , KC_CPI_UP    , KC_SMO_SC    , _______, _______,
_______, _______, _______, _______, _______, _______,                        KC_WH_U    , KC_SCROLLMODE, KC_CURSORMODE, KC_CARRETMODE, _______, _______,
_______, _______, _______, _______, _______, _______,                        KC_WH_D    , KC_BTN1      , KC_BTN3      , KC_BTN2      , _______, _______,
_______, _______, _______, _______, _______, _______,                        _______    , KC_BTN4      , KC_BTN5      , _______      , _______, _______,
                          _______, _______,                                          _______, _______,
                                            _______, _______,               _______, _______,
                                            _______, _______,               _______, _______,
                                            _______, _______,               _______, _______
    ),

[NAVIGATION] = LAYOUT_5x6(
KC_RST , _______ , _______ , _______ , _______ , _______,                 _______, KC_DELETE, _______ ,KC_PGUP, _______, _______,
_______, _______ , _______ , _______ , _______ , _______,                 _______, KC_INSERT, KC_UP   ,KC_PGDN, _______, _______,
_______, KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______,                 _______, KC_LEFT  , KC_DOWN ,KC_RIGHT, _______, _______,
_______, _______ , KC_ALGR , _______ , _______ , _______,                 _______, _______, _______ ,_______, _______, _______,
                             _______,_______,                                KC_HOME,KC_END,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______
),

[MATH] = LAYOUT_5x6(
KC_RST , _______ , _______ , _______ , _______ , _______,                 X(SQRT)     , X(Divide), KC_ASTR, KC_MINUS, KC_PLUS , KC_Z    ,
_______, _______ , _______ , _______ , _______ , _______,                 X(Squared)  , KC_7     , KC_8   , KC_9    , KC_EQUAL, KC_Y    ,
_______, KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______,                 X(PlusMinus), KC_4     , KC_5   , KC_6    , KC_DOT  , KC_X    ,
_______, _______ , KC_ALGR , _______ , _______ , _______,                 KC_CIRC     , KC_1     , KC_2   , KC_3    , KC_COMM , KC_ENTER,
                             _______,_______,                                KC_LPRN,KC_RPRN,
                                        _______,_______,             _______,KC_0   ,
                                        _______,_______,             _______,X(Pi)  ,
                                        _______,_______,             _______,_______
),


[FNKeys] = LAYOUT_5x6(
_______, _______ , KC_F10, KC_F11, KC_F12, _______,                 _______, _______  , _______ ,_______, _______, KC_RST ,
_______, _______ , KC_F7 , KC_F8 , KC_F9 , _______,                 _______, _______  , _______ ,_______, _______, _______,
_______, KC_LGUI , KC_F4 , KC_F5 , KC_F6 , _______,                 _______, KC_RSHIFT, KC_RCTRL,KC_RALT, KC_LGUI, _______,
_______, _______ , KC_F1 , KC_F2 , KC_F3 , _______,                 _______, _______  , _______ ,KC_ALGR, _______, _______,
                             _______,_______,                                _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______
),

[UNICODE] = LAYOUT_5x6(

KC_RST , _______ , _______ , _______ , _______ , _______,                 X(Alpha), X(SQRT)        , X(CubeRoot) , X(FourthRoot)  , X(Angle)      , X(Integral),
_______, _______ , _______ , _______ , _______ , _______,                 X(Beta) , X(SeventhPower), X(EigthPower), X(NinethPower), X(mesAngle)   , X(Farenheit),
_______, KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______,                 X(Delta), X(FourthPower) , X(FifthPower), X(SixthPower) , X(NotEqual)   , X(Degree),
_______, _______ , KC_ALGR , _______ , _______ , _______,                 X(Theta), X(FirstPower)  , X(Squared)   ,X(Cubed)       , X(ApproxEqual), X(Infinity),
                             _______,_______,                                _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______
),

};


/***************************
 * Tap dance 2 of 2
 **************************/

// determine the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
if (state->count == 1) {
//if (state->interrupted || !state->pressed) { return SINGLE_TAP; } //interrupted sends SINGLE_TAP
if (!state->pressed) { return SINGLE_TAP; } //interrupted sends SINGLE_HOLD
else { return SINGLE_HOLD; }
}
else { return 2; } // any number higher than the maximum state value you return above
}

void unstick_keys(void) {
	if (MOD_BIT(KC_LALT)) {
		unregister_mods(MOD_BIT(KC_LALT));
		is_alt_active = false;
	}
	if (MOD_BIT(KC_LSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT));
		is_sft_active = false;
	}
	if (MOD_BIT(KC_LCTL)) {
		unregister_mods(MOD_BIT(KC_LCTL));
		is_ctl_active = false;
	}
	if (MOD_BIT(KC_LGUI)) {
		unregister_mods(MOD_BIT(KC_LGUI));
		is_gui_active = false;
	}
}

void activate_stkeys(void) {
	if (activate_alt) {
		register_mods(MOD_BIT(KC_LALT));
		activate_alt = false;
		is_alt_active = true;
	}
	if (activate_sft) {
		register_mods(MOD_BIT(KC_LSFT));
		activate_sft = false;
		is_sft_active = true;
	}
	if (activate_ctl) {
		register_mods(MOD_BIT(KC_LCTL));
		activate_ctl = false;
		is_ctl_active = true;
	}
	if (activate_gui) {
		register_mods(MOD_BIT(KC_LGUI));
		activate_gui = false;
		is_gui_active = true;
	}
}

void alttm_finished (qk_tap_dance_state_t *state, void *user_data) {
	td_state = cur_dance(state);
	sticky_timer = timer_read32();
	activate_alt = true;
	sticky_key = true;
	switch (td_state) {
	case SINGLE_TAP:
		track_mode = scroll_mode;
		break;
	case SINGLE_HOLD:
		activate_stkeys();
		sticky_key = false;
	}
}
void alttm_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (td_state) {
	case SINGLE_TAP:
		break;
	case SINGLE_HOLD:
		unstick_keys();
	}
}
void sfttm_finished (qk_tap_dance_state_t *state, void *user_data) {
	td_state = cur_dance(state);
	sticky_timer = timer_read32();
	activate_sft = true;
	sticky_key = true;
	switch (td_state) {
		case SINGLE_TAP:
			track_mode = carret_mode;
			break;
		case SINGLE_HOLD:
			activate_stkeys();
			sticky_key = false;
	}
}
void sfttm_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (td_state) {
	case SINGLE_TAP:
		break;
	case SINGLE_HOLD:
		unstick_keys();
	}
}
void ctltm_finished (qk_tap_dance_state_t *state, void *user_data) {
	td_state = cur_dance(state);
	sticky_timer = timer_read32();
	activate_ctl = true;
	sticky_key = true;
	switch (td_state) {
	case SINGLE_TAP:
		track_mode = cursor_mode;
		break;
	case SINGLE_HOLD:
		activate_stkeys();
		sticky_key = false;
	}
}
void ctltm_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (td_state) {
	case SINGLE_TAP:
		break;
	case SINGLE_HOLD:
		unstick_keys();
	}
}
void guitm_finished (qk_tap_dance_state_t *state, void *user_data) {
	td_state = cur_dance(state);
	sticky_timer = timer_read32();
	activate_gui = true;
	sticky_key = true;
	switch (td_state) {
	case SINGLE_TAP:
		break;
	case SINGLE_HOLD:
		activate_stkeys();
		sticky_key = false;
	}
}
void guitm_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (td_state) {
	case SINGLE_TAP:
		break;
	case SINGLE_HOLD:
		unstick_keys();
	}
}


// define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
	[ALT_TM]	 = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alttm_finished , alttm_reset),
	[SFT_TM]	 = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sfttm_finished , sfttm_reset),
	[CTL_TM]	 = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctltm_finished , ctltm_reset),
	[GUI_TM]	 = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guitm_finished , guitm_reset),
};

/***************************
 * Trackball handling
 **************************/

void pointing_device_init(void){
	if(!is_keyboard_master())
		return;
	pmw_init();
}

int max(int num1, int num2) { return (num1 > num2 ) ? num1 : num2; }
int min(int num1, int num2) { return (num1 > num2 ) ? num2 : num1; }

int8_t sign(int x) { return (x > 0) - (x < 0); }
int8_t CLAMP_HID(int value) { return value < -127 ? -127 : value > 127 ? 127 : value; }

void tap_code_fast(uint8_t code) {
	register_code(code);
	// Dont do this:
	// if (code == KC_CAPS) {
	//	 wait_ms(TAP_HOLD_CAPS_DELAY);
	// } else {
	//	 wait_ms(TAP_CODE_DELAY);
	// }
	unregister_code(code);
}

void tap_tb(uint8_t keycode0, uint8_t keycode1, uint8_t keycode2, uint8_t keycode3) {
	if(abs(cum_x) + abs(cum_y) >= cur_factor){
		if(abs(cum_x) > abs(cum_y)) {
			if(cum_x > 0) {
				for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
					tap_code_fast(keycode0);
					cum_x = max(cum_x - cur_factor, 0);
				}
				cum_y = 0;
			} else {
				for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
					tap_code_fast(keycode1);
					cum_x = min(cum_x + cur_factor, 0);
				}
				cum_y = 0;
			}
		} else {
			if(cum_y > 0) {
				for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
					tap_code_fast(keycode2);
					cum_y = max(cum_y - cur_factor, 0);
					}
				cum_x = 0;
			} else {
				for (int8_t i = 0; i <= (abs(cum_x) + abs(cum_y)) / cur_factor; i++) {
					tap_code_fast(keycode3);
					cum_y = min(cum_y + cur_factor, 0);
				}
				cum_x = 0;
			}
		}
	}
}

void handle_pointing_device_modes(void){
	report_mouse_t mouse_report = pointing_device_get_report();

	if (track_mode == cursor_mode) {
		if (integration_mode)
			cur_factor = cursor_multiplier_inte;
		else
			cur_factor = cursor_multiplier;
		mouse_report.x = CLAMP_HID( sensor_x * cur_factor / 100);
		mouse_report.y = CLAMP_HID(-sensor_y * cur_factor / 100);
	} else {
		// accumulate movement until threshold reached
		cum_x += sensor_x;
		cum_y += sensor_y;
		if (track_mode == carret_mode) {
			if (integration_mode)
				cur_factor = carret_threshold_inte;
			else
				cur_factor = carret_threshold;
			tap_tb(KC_RIGHT, KC_LEFT, KC_UP, KC_DOWN);

		} else if(track_mode == scroll_mode) {
				if (integration_mode)
					cur_factor = scroll_threshold_inte;
				else
					cur_factor = scroll_threshold;
				if(abs(cum_x) + abs(cum_y) >= cur_factor) {
					if(abs(cum_x) > abs(cum_y)) {
						mouse_report.h = sign(cum_x) * (abs(cum_x) + abs(cum_y)) / cur_factor;
					} else {
						mouse_report.v = sign(cum_y) * (abs(cum_x) + abs(cum_y)) / cur_factor;
					}
					cum_x = 0;
					cum_y = 0;
				}
		} else { // sound vol/brightness (3)
			cur_factor = carret_threshold;
			tap_tb(KC_BRIGHTNESS_UP, KC_BRIGHTNESS_DOWN, KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN);
		}
	}
	pointing_device_set_report(mouse_report);
	pointing_device_send();
}

void get_sensor_data(void) {
	if(!is_keyboard_master())
		return;
	report_pmw_t pmw_report = pmw_get_report();

	if (integration_mode) {
		sensor_x += pmw_report.x;
		sensor_y += pmw_report.y;
	} else {
		sensor_x = pmw_report.x;
		sensor_y = pmw_report.y;
	}
}

void pointing_device_task(void) {
#ifndef POLLING
	if ( is_keyboard_master() && integration_mode )
		handle_pointing_device_modes();
#else
	get_sensor_data();
	handle_pointing_device_modes();
#endif
	}

#ifndef POLLING
	ISR(INT2_vect) {
		get_sensor_data();
		handle_pointing_device_modes();
	}
#endif


/***************************
 * process_record_kb
 **************************/

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	if(!process_record_user(keycode, record)) {
		return false;
	}

	switch (keycode) {

		case KC_SCROLLMODE:
            if (record->event.pressed) {
                track_mode = scroll_mode;
                } else {
                }
            return false;

        case KC_CURSORMODE:
            if (record->event.pressed) {
                track_mode = cursor_mode;
                } else {
                }
            return false;

        case KC_CARRETMODE:
            if (record->event.pressed) {
                track_mode = carret_mode;
                } else {
                }
            return false;

		// handle mouse
		case KC_BTN1:
			on_mouse_button(MOUSE_BTN1, record->event.pressed);
			return false;

		case KC_BTN2:
			on_mouse_button(MOUSE_BTN2, record->event.pressed);
			return false;

		case KC_BTN3:
			on_mouse_button(MOUSE_BTN3, record->event.pressed);
			return false;

		case KC_BTN4:
			on_mouse_button(MOUSE_BTN4, record->event.pressed);
			return false;

		case KC_BTN5:
			on_mouse_button(MOUSE_BTN5, record->event.pressed);
			return false;

		case KC_CPI_DOWN:
			if (cursor_multiplier > CPI_STEP)
				cursor_multiplier = cursor_multiplier - CPI_STEP;
			return false;

		case KC_CPI_STD:
			cursor_multiplier = 250;
			return false;

		case KC_CPI_UP:
			cursor_multiplier = cursor_multiplier + CPI_STEP;
			return false;

		case KC_SMO_SC:
			if (record->event.pressed) {
				if (smooth_scroll) {
				scroll_threshold = scroll_threshold * regular_smoothscroll_factor;
				scroll_threshold_inte = scroll_threshold_inte * regular_smoothscroll_factor;
				smooth_scroll = false;
				} else {
				scroll_threshold = scroll_threshold / regular_smoothscroll_factor;
				scroll_threshold_inte = scroll_threshold_inte / regular_smoothscroll_factor;
				smooth_scroll = true;
				}
			}
		


		default:
			return true;
	}

}


// KC_CURSORMODE
// KC_SCROLLMODE
// KC_CARRETMODE