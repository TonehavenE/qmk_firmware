#include QMK_KEYBOARD_H
#include "print.h"

#define _COLEMAK 	0
#define _NAV 		1
#define _NUM 		2
#define _FUNCTION 	3
#define _TRACK 		4
#define _GAME 		5

#define NAV 	 MO(_NAV)
#define NUM 	 MO(_NUM)
#define FUNCTION MO(_FUNCTION)
#define TRACK 	 MO(_TRACK)
#define GAME 	 MO(_GAME)

/***************************
 * Trackball related defines
 **************************/

#include "pointing_device.h"
#include "../../qurn/pmw3360.h"

uint8_t track_mode = 0; // 0 Mousecursor; 1 arrowkeys/carret; 2 scrollwheel; 3 sound/brightness
#define cursor_mode 0
#define carret_mode 1
#define scroll_mode 2
#define sound_brightness_mode 3
uint8_t prev_track_mode = 0;
int16_t cum_x = 0;
int16_t cum_y = 0;
int16_t sensor_x = 0;
int16_t sensor_y = 0;

// Thresholds help to move only horizontal or vertical. When accumulated distance reaches threshold, only move one discrete value in direction with bigger delta.
uint8_t	carret_threshold = 60;		 // higher means slower
#define CRT_STEP 5

#define regular_smoothscroll_factor 8
bool smooth_scroll = true;
uint8_t	scroll_threshold = 8 / regular_smoothscroll_factor;	// divide if started smooth

uint16_t cursor_multiplier = 130;	// adjust cursor speed
#define CPI_STEP 10

int16_t cur_factor;

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

/*******************
 * Custom Keycodes *
*******************/

enum custom_keycodes {
	KC_INTE = SAFE_RANGE,
	CPI_DOWN					 ,
	CPI_STD 					 ,
	CPI_UP 					 	 ,
	SMO_SC 					 	 ,
	CURS_MD 					 ,
    SCRL_MD 					 ,
    CART_MD 					 ,
    L_TAB = LT(_NAV, KC_TAB)	 ,
    L_SPC = LT(_NUM, KC_SPC)	 ,
    L_ENT = LT(_FUNCTION, KC_ENT),
    L_Z = LT(_TRACK, KC_Z)		 ,
    COMMA = KC_COMM				 ,
    CRT_UP 						 , 
    CRT_DOWN 					 ,
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

// Mouse Combos
const uint16_t PROGMEM rsm_combo[] = {LALT_T(KC_R), LCTL_T(KC_S), COMBO_END};
const uint16_t PROGMEM stm_combo[] = {LCTL_T(KC_S), LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM rtm_combo[] = {LALT_T(KC_R), LSFT_T(KC_T), COMBO_END};
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
};
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_COLEMAK] = LAYOUT(
		KC_Q, KC_W        , KC_F        , KC_P        , KC_G , KC_RBRC, KC_J, KC_L        , KC_U        , KC_Y        , KC_SCLN, 
		KC_A, LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_D , KC_LBRC, KC_H, RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), KC_O   , 
		L_Z , KC_X        , KC_C        , KC_V        , KC_B , KC_LPRN, KC_K, KC_M        , COMMA       , KC_DOT      , KC_SLSH, 
				          L_TAB,          L_SPC,        L_ENT, KC_RPRN,       KC_BSPC
		),

	[_NAV] = LAYOUT(
		KC_TRNS, RESET  , KC_TRNS, KC_TRNS, KC_TRNS, GAME, KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_TRNS, 
		KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, GAME, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, GAME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS,                   GAME,          KC_DEL
		),

	[_NUM] = LAYOUT(
		KC_TRNS, KC_AMPR, KC_ASTR, KC_CIRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS, 
		KC_TRNS, KC_DLR , KC_PERC, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_TRNS, 
		KC_TRNS, KC_EXLM, KC_AT  , KC_HASH, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,          KC_0
		),

	[_FUNCTION] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F10, KC_F7, KC_F8, KC_F9, KC_TRNS, 
		KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, KC_TRNS, KC_F11, KC_F4, KC_F5, KC_F6, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12, KC_F1, KC_F2, KC_F3, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,         KC_TRNS
		),

	[_TRACK] = LAYOUT(
		RESET  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, CPI_UP , CPI_DOWN, CRT_UP , CRT_DOWN, 
		KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, CART_MD, CURS_MD , SCRL_MD, KC_TRNS , 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, KC_TRNS , 
		KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, 		   KC_TRNS
		),

	[_GAME] = LAYOUT(
		KC_Q, KC_W, KC_E, KC_R, KC_T, GAME, KC_Y, KC_U, KC_I , KC_O  , KC_P   , 
		KC_A, KC_S, KC_D, KC_F, KC_G, GAME, KC_H, KC_J, KC_K , KC_L  , KC_SCLN, 
		KC_Z, KC_X, KC_C, KC_V, KC_B, GAME, KC_N, KC_M, COMMA, KC_DOT, KC_SLSH, 
				L_TAB, L_SPC,  L_ENT, GAME,       KC_BSPC
		)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
	print("The Tantalus Keyboard has been intalized. Scanning for keypresses");
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
  return true;
}

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
		cur_factor = cursor_multiplier;
		mouse_report.x = CLAMP_HID( sensor_x * cur_factor / 100);
		mouse_report.y = CLAMP_HID(-sensor_y * cur_factor / 100);
	} else {
		// accumulate movement until threshold reached
		cum_x += sensor_x;
		cum_y += sensor_y;
		if (track_mode == carret_mode) {
			cur_factor = carret_threshold;
			tap_tb(KC_RIGHT, KC_LEFT, KC_UP, KC_DOWN);

		} else if(track_mode == scroll_mode) {
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
	sensor_x = pmw_report.x;
	sensor_y = pmw_report.y;
}

void pointing_device_task(void) {
#ifndef POLLING
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
/********************
 * Custom Keycodes *
********************/

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	if(!process_record_user(keycode, record)) {
		return false;
	}

	switch (keycode) {

		case SCRL_MD:
            if (record->event.pressed) {
                track_mode = scroll_mode;
                } else {
                }
            return false;

        case CURS_MD:
            if (record->event.pressed) {
                track_mode = cursor_mode;
                } else {
                }
            return false;

        case CART_MD:
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

		case CPI_DOWN:
			if (cursor_multiplier > CPI_STEP)
				cursor_multiplier = cursor_multiplier - CPI_STEP;
			return false;

		case CPI_STD:
			cursor_multiplier = 160;
			return false;

		case CPI_UP:
			cursor_multiplier = cursor_multiplier + CPI_STEP;
			return false;

		case CRT_DOWN:
		if (carret_threshold > CRT_STEP)
				carret_threshold = carret_threshold - CRT_STEP;
			return false;
		
		case CRT_UP:
			carret_threshold = carret_threshold + CRT_STEP;
			return false;

		default:
			return true;	
	}
}
