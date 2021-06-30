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
#define _ADJUST 1
#define _LOWER 2
#define _RAISE 3
#define _MATH 4
#define _UNICODE 5
#define _FUNCTION 6

#define ADJUST MO(_ADJUST)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define MATH MO(_MATH)
#define UNICODE MO(_UNICODE)
#define FUNCTION MO(_FUNCTION)


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
uint8_t	carret_threshold = 60;		 // higher means slower
uint16_t carret_threshold_inte = 340; // in integration mode higher threshold

#define regular_smoothscroll_factor 8
bool smooth_scroll = true;
uint8_t	scroll_threshold = 8 / regular_smoothscroll_factor;	// divide if started smooth
uint16_t scroll_threshold_inte = 1200 / regular_smoothscroll_factor;

uint16_t cursor_multiplier = 160;	// adjust cursor speed
uint16_t cursor_multiplier_inte = 20;
#define CPI_STEP 10

int16_t cur_factor;


/***************************
 * Unicode Defines
 **************************/
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

enum combo_events {
    /* Backspace steno-lite combos */
    // These let me type common words and n-grams
    // more quickly, in one single stroke.
    BSPCEV_EVERY,
    BSPCU_YOU,
    BSPCA_AND,
    BSPCN_NOT,
    BSPCW_WITH,
    BSPCF_FOR,
    BSPCH_HERE,
    BSPCT_THE,
    BSPCM_MENT,
    BSPCG_ING,
    BSPCO_OUGH,
    BSPCI_ION,
    BSPCIS_IONS,
    BSPCTA_THAT,
    BSPCQ_QUE,
    // I use the word "key" much more frequently than the common folk
    // and if you're reading this, you probably do too
    BSPCK_KEY,

    /* Other steno-lite combos */
    // Additional steno-lite combos for common words and n-grams
    // that do not involve the backspace thumb key because these
    // combinations of keys do not generate too many conflicts
    // in normal typing.
    JU_JUST,
    HV_HAVE,
    DELT_THIS,
    YCOLON_RPRN,
    UY_LPRN,

    RS_MOUSE,
    ST_MOUSE,
    RT_MOUSE,
    EQUALMINUS_RECONE,
    ZEROCOLON_RECTWO,
    ZEROEQUAL_PLAYONE,
    MINUSCOLON_PLAYTWO,
    EQUALCOLON_STOP
};

const uint16_t PROGMEM BSPC_E_V_COMBO[] = {KC_BSPC,  KC_E,  KC_V,    COMBO_END};
const uint16_t PROGMEM BSPC_U_COMBO[]   = {KC_BSPC,  KC_U,    COMBO_END};
const uint16_t PROGMEM BSPC_A_COMBO[]   = {KC_BSPC,  KC_A,  COMBO_END};
const uint16_t PROGMEM BSPC_N_COMBO[]   = {KC_BSPC,  KC_N,  COMBO_END};
const uint16_t PROGMEM BSPC_W_COMBO[]   = {KC_BSPC,  KC_W,    COMBO_END};
const uint16_t PROGMEM BSPC_F_COMBO[]   = {KC_BSPC,  KC_F,    COMBO_END};
const uint16_t PROGMEM BSPC_H_COMBO[]   = {KC_BSPC,  KC_H,    COMBO_END};
const uint16_t PROGMEM BSPC_T_COMBO[]   = {KC_BSPC,  KC_T,  COMBO_END};
const uint16_t PROGMEM BSPC_M_COMBO[]   = {KC_BSPC,  KC_M,    COMBO_END};
const uint16_t PROGMEM BSPC_G_COMBO[]   = {KC_BSPC,  KC_G,    COMBO_END};
const uint16_t PROGMEM BSPC_O_COMBO[]   = {KC_BSPC,  KC_O,  COMBO_END};
const uint16_t PROGMEM BSPC_I_COMBO[]   = {KC_BSPC,  KC_I,  COMBO_END};
const uint16_t PROGMEM BSPC_I_S_COMBO[] = {KC_BSPC,  KC_I,  KC_S,  COMBO_END};
const uint16_t PROGMEM BSPC_Q_COMBO[]   = {KC_BSPC,  KC_Q,    COMBO_END};
const uint16_t PROGMEM BSPC_K_COMBO[]   = {KC_BSPC,  KC_K,    COMBO_END};
const uint16_t PROGMEM BSPC_T_A_COMBO[] = {KC_BSPC,  KC_T,  KC_A,  COMBO_END};
const uint16_t PROGMEM DEL_T_COMBO[]    = {KC_DEL,   KC_T,  COMBO_END};
const uint16_t PROGMEM J_U_COMBO[]      = {KC_J,     KC_U,    COMBO_END};
const uint16_t PROGMEM H_V_COMBO[]      = {KC_H,     KC_V,    COMBO_END};
const uint16_t PROGMEM U_Y_COMBO[]      = {KC_U,     KC_Y,    COMBO_END};
const uint16_t PROGMEM Y_SCOLON_COMBO[] = {KC_Y,     KC_SCLN, COMBO_END};
const uint16_t PROGMEM rsm_combo[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM stm_combo[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM rtm_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM equalminusrec_combo[] = {KC_EQUAL, KC_MINUS, COMBO_END};
const uint16_t PROGMEM zerocolonrec_combo[] = {KC_0, KC_SCOLON, COMBO_END};
const uint16_t PROGMEM zeroequalplay_combo[] = {KC_0, KC_EQUAL, COMBO_END};
const uint16_t PROGMEM minuscolonplay_combo[] = {KC_MINUS, KC_SCOLON, COMBO_END};
const uint16_t PROGMEM equalcolonplay_combo[] = {KC_EQUAL, KC_SCOLON, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [BSPCEV_EVERY] = COMBO_ACTION(BSPC_E_V_COMBO),
    [BSPCU_YOU]    = COMBO_ACTION(BSPC_U_COMBO),
    [BSPCA_AND]    = COMBO_ACTION(BSPC_A_COMBO),
    [BSPCN_NOT]    = COMBO_ACTION(BSPC_N_COMBO),
    [BSPCW_WITH]   = COMBO_ACTION(BSPC_W_COMBO),
    [BSPCF_FOR]    = COMBO_ACTION(BSPC_F_COMBO),
    [BSPCH_HERE]   = COMBO_ACTION(BSPC_H_COMBO),
    [BSPCT_THE]    = COMBO_ACTION(BSPC_T_COMBO),
    [BSPCM_MENT]   = COMBO_ACTION(BSPC_M_COMBO),
    [BSPCG_ING]    = COMBO_ACTION(BSPC_G_COMBO),
    [BSPCO_OUGH]   = COMBO_ACTION(BSPC_O_COMBO),
    [BSPCI_ION]    = COMBO_ACTION(BSPC_I_COMBO),
    [BSPCIS_IONS]  = COMBO_ACTION(BSPC_I_S_COMBO),
    [BSPCTA_THAT]  = COMBO_ACTION(BSPC_T_A_COMBO),
    [BSPCQ_QUE]    = COMBO_ACTION(BSPC_Q_COMBO),
    [BSPCK_KEY]    = COMBO_ACTION(BSPC_K_COMBO),
    [DELT_THIS]    = COMBO_ACTION(DEL_T_COMBO),
    [JU_JUST]      = COMBO_ACTION(J_U_COMBO),
    [HV_HAVE]      = COMBO_ACTION(H_V_COMBO),
    [UY_LPRN]      = COMBO(U_Y_COMBO, KC_LPRN),
    [YCOLON_RPRN]  = COMBO(Y_SCOLON_COMBO, KC_RPRN),
    [RS_MOUSE] = COMBO_ACTION(rsm_combo),
    [ST_MOUSE] = COMBO_ACTION(stm_combo),
    [RT_MOUSE] = COMBO_ACTION(rtm_combo),
    [EQUALMINUS_RECONE] = COMBO_ACTION(equalminusrec_combo),
    [ZEROCOLON_RECTWO] = COMBO_ACTION(zerocolonrec_combo),
    [ZEROEQUAL_PLAYONE] = COMBO_ACTION(zeroequalplay_combo),
    [MINUSCOLON_PLAYTWO] = COMBO_ACTION(minuscolonplay_combo),
    [EQUALCOLON_STOP] = COMBO_ACTION(equalcolonplay_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    // Process mod-taps before the combo is fired,
    // this helps making modifier-aware combos,
    // like UY_PRN or BSPCN_NOT, more fluid
    // when I use them with home row mods.
    action_tapping_process((keyrecord_t){});
    switch(combo_index) {

        case JU_JUST:
            if (pressed) {
                    send_string("just");
                }
        break;

        case HV_HAVE:
            if (pressed) {
                    send_string("have");
                }
        break;

        case BSPCEV_EVERY:
            if (pressed) {
                    send_string("every");
        }
        break;

        case BSPCU_YOU:
            if (pressed) {
                    send_string("you");
                
        }
        break;

        case BSPCA_AND:
            if (pressed) {
            
                    send_string("and");
                
        }
        break;

        case BSPCN_NOT:
            if (pressed) {
                    send_string("not");
        }
        break;

        case BSPCW_WITH:
            if (pressed) {
                
                    send_string("with");
            
        }
        break;

        case BSPCF_FOR:
            if (pressed) {
                    send_string("for");
                
        }
        break;

        case BSPCH_HERE:
            if (pressed) {
        
                    send_string("here");
                
        }
        break;

        case BSPCT_THE:
            if (pressed) {
                    send_string("the");
        }
        break;

        case BSPCM_MENT:
            if (pressed) {
                    send_string("ment");
        }
        break;

        case BSPCG_ING:
            if (pressed) {
                    send_string("ing");
        }
        break;

        case BSPCO_OUGH:
            if (pressed) {
                    send_string("ough");
        }
        break;

        case BSPCI_ION:
            if (pressed) {
                    send_string("ion");
        }
        break;

        case BSPCIS_IONS:
            if (pressed) {
                    send_string("ions");
        }
        break;

        case BSPCTA_THAT:
            if (pressed) {
                    send_string("that");
        }
        break;

        case BSPCQ_QUE:
            if (pressed) {
                
                    send_string("que");
                
        }
        break;

        case BSPCK_KEY:
            if (pressed) {
               
                    send_string("key");
                
        }
        break;


        case DELT_THIS:
            if (pressed) {
                    send_string("this");
        }
        break;

        case RS_MOUSE:
        on_mouse_button(MOUSE_BTN2, pressed);
        break;
    case ST_MOUSE:
        on_mouse_button(MOUSE_BTN1, pressed);
        break;
    case RT_MOUSE:
        on_mouse_button(MOUSE_BTN3, pressed);
        break;

    case EQUALMINUS_RECONE:
        if (pressed) {
        tap_code16(DM_REC1);
      }
        break;

    case ZEROCOLON_RECTWO:
        if (pressed) {
        tap_code16(DM_REC2);
      }
        break;

    case ZEROEQUAL_PLAYONE:
        if (pressed) {
        tap_code16(DM_PLY1);
      }
        break;

    case MINUSCOLON_PLAYTWO:
        if (pressed) {
        tap_code16(DM_PLY2);
      }
        break;

    case EQUALCOLON_STOP:
        if (pressed) {
        tap_code16(DM_RSTP);
      }
        break;

    }
};


/***************************
 * Custom Keycodes and Layers
 **************************/

enum custom_keycodes {
	KC_INTE = SAFE_RANGE,
	KC_ADJUST,
	KC_RAISE,
	KC_LOWER,
	KC_MATH,
	KC_UNICODE,
	KC_FUNCTION,
	KC_SCLN_INV,
	KC_QUOT_MY, //not US Int style
	KC_TILD_MY, //not US Int style
	KC_BSPC_LCTL,
	KC_CPI_DOWN,
	KC_CPI_STD,
	KC_CPI_UP,
	KC_SMO_SC,
	KC_CURSORMODE,
    KC_SCROLLMODE,
    KC_CARRETMODE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//[_COLEMAK] = LAYOUT_5x6(
//DM_REC1,    DM_REC1, DM_PLY1, DM_REC2 , DM_PLY2 , DM_RSTP,               KC_CPI_DOWN, KC_CPI_STD , KC_CPI_UP , KC_SMO_SC , KC_0        ,KC_QUOT_MY,
//KC_TAB,     KC_Q ,   KC_W   , KC_F    , KC_P    , KC_G   ,               KC_J    ,    KC_L       , KC_U      , KC_Y      , KC_SCLN_INV ,KC_QUOT_MY,
//KC_ESC,     KC_A ,   KC_R   , KC_S    , KC_T    , KC_D   ,               KC_H    ,    KC_N       , KC_E      , KC_I      , KC_O        ,KC_MINS,
//KC_TILD_MY, KC_Z ,   KC_X   , KC_C    , KC_V    , KC_B   ,               KC_K    ,    KC_M       , KC_COMM   , KC_DOT    , KC_SLSH     ,KC_BSLASH,
//                           _______, _______,                                         _______, KC_LGUI,
//                                       TD(SFT_TM),    TD(RAI_TM),          _______, KC_SPC,
//                                       TD(CTL_TM),    TD(GUI_TM),          _______, KC_ENT,
//                                       TD(ALT_TM),    TD(LOW_TM),          KC_BSPC, KC_DEL
//),
[_COLEMAK] = LAYOUT_5x6(
KC_ESC   , KC_1 ,   KC_2 , KC_3    , KC_4         , KC_5   ,               KC_6    ,    KC_7 , KC_8      , KC_9      , KC_0        , KC_EQUAL     ,
KC_LALT  , KC_Q ,   KC_W , KC_F    , KC_P         , KC_G   ,               KC_J    ,    KC_L , KC_U      , KC_Y      , KC_SCOLON   , KC_MINUS     ,
KC_LSFT  , KC_A ,   KC_R , KC_S    , KC_T         , KC_D   ,               KC_H    ,    KC_N , KC_E      , KC_I      , KC_O        , OSM(MOD_RSFT),
KC_LCTL  , KC_Z ,   KC_X , KC_C    , KC_V         , KC_B   ,               KC_K    ,    KC_M , KC_COMM   , KC_DOT    , KC_SLASH    , KC_QUOTE     ,
                           KC_LBRC,KC_RBRC,                                         TG(_ADJUST), TG(_LOWER),
                                       LT(_UNICODE, KC_TAB), LT(_RAISE, KC_SPACE),  _______, KC_BSPC,
                                       LT(_MATH, KC_EQUAL) , KC_END    ,            _______, LT(_FUNCTION, KC_ENT),
                                       KC_BSLASH           , X(Dash)   ,            KC_DEL, KC_HOME
),

[_ADJUST] = LAYOUT_5x6(
KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                              KC_6  , KC_7  , KC_8  , KC_9   , KC_0  ,KC_DELETE,
KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                              KC_Y  , KC_U  , KC_I  , KC_O   , KC_P  ,KC_MINUS,
KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                              KC_H  , KC_J  , KC_K  , KC_L   ,KC_SCLN,KC_QUOTE,
KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                              KC_N  , KC_M  , KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                      KC_LBRC,KC_RBRC,                                                _______, KC_EQL,
                                  LT(_UNICODE, KC_TAB), LT(_RAISE, KC_SPACE),           _______  , LT(_LOWER, KC_BSPC),
                                  LT(_MATH, KC_EQUAL) , KC_END              ,           _______  , KC_ENTER,
                                  KC_LALT             , X(Dash)             ,           KC_DELETE, KC_HOME
),

[_LOWER] = LAYOUT_5x6(

KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                        KC_CPI_DOWN, KC_CPI_STD   , KC_CPI_UP    , KC_SMO_SC    , _______, _______,
KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_WH_U    , KC_SCROLLMODE, KC_CURSORMODE, KC_CARRETMODE, _______, _______,
KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                          KC_WH_D    , KC_BTN1      , KC_BTN3      , KC_BTN2      , _______, _______,
KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                       _______    , KC_BTN4      , KC_BTN5      , _______      , _______, _______,
                          _______, _______,                                          _______, _______,
                                            KC_LALT, KC_SPACE,               _______, _______,
                                            _______, _______,               _______, _______,
                                            _______, _______,               _______, _______
),

[_RAISE] = LAYOUT_5x6(
KC_GRAVE, _______ , _______ , _______ , _______ , RESET  ,                 RESET  , KC_DELETE, _______ ,KC_PGUP, DM_REC1, DM_REC2,
_______ , _______ , _______ , _______ , _______ , _______,                 _______, KC_INSERT, KC_UP   ,KC_PGDN, DM_PLY1, DM_PLY2,
_______ , KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______,                 _______, KC_LEFT  , KC_DOWN ,KC_RIGHT, DM_RSTP, DM_RSTP,
_______ , _______ , KC_ALGR , _______ , _______ , _______,                 _______, _______, _______ ,_______, _______, _______,
                             _______,_______,                                KC_HOME,KC_END,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______
),


[_MATH] = LAYOUT_5x6(
RESET  , _______ , _______ , _______ , _______ , _______,                 X(SQRT)     , X(Divide), KC_ASTR, KC_MINUS, KC_PLUS , KC_Z    ,
_______, _______ , _______ , _______ , _______ , _______,                 X(Squared)  , KC_7     , KC_8   , KC_9    , KC_EQUAL, KC_Y    ,
_______, KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______,                 X(PlusMinus), KC_4     , KC_5   , KC_6    , KC_DOT  , KC_X    ,
_______, _______ , KC_ALGR , _______ , _______ , _______,                 KC_CIRC     , KC_1     , KC_2   , KC_3    , KC_COMM , KC_ENTER,
                             _______,_______,                                KC_LPRN,KC_RPRN,
                                        _______,_______,             _______,KC_0   ,
                                        _______,_______,             _______,X(Pi)  ,
                                        _______,_______,             _______,_______
),

[_UNICODE] = LAYOUT_5x6(
RESET  , _______ , _______ , _______ , _______ , _______,                 X(Alpha), X(SQRT)        , X(CubeRoot) , X(FourthRoot)  , X(Angle)      , X(Integral),
_______, _______ , _______ , _______ , _______ , _______,                 X(Beta) , X(SeventhPower), X(EigthPower),X(NinethPower), X(mesAngle)   , X(Farenheit),
_______, KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , _______,                 X(Delta), X(FourthPower) , X(FifthPower),X(SixthPower) , X(NotEqual)   , X(Degree),
_______, _______ , KC_ALGR , _______ , _______ , _______,                 X(Theta), X(FirstPower)  , X(Squared)   ,X(Cubed)       , X(ApproxEqual), X(Infinity),
                             _______,_______,                                _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______
),

[_FUNCTION] = LAYOUT_5x6(
_______, _______ , KC_F10, KC_F11, KC_F12, _______,                 _______, _______  , _______ ,_______, _______, RESET  ,
_______, _______ , KC_F7 , KC_F8 , KC_F9 , _______,                 _______, _______  , _______ ,_______, _______, _______,
_______, KC_LGUI , KC_F4 , KC_F5 , KC_F6 , _______,                 _______, KC_RSHIFT, KC_RCTRL,KC_RALT, KC_LGUI, _______,
_______, _______ , KC_F1 , KC_F2 , KC_F3 , _______,                 _______, _______  , _______ ,KC_ALGR, _______, _______,
                             _______,_______,                                _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______,
                                        _______,_______,             _______,_______
),


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


		case KC_TILD_MY:
			if (record->event.pressed) {
				tap_code16(KC_TILD);
				tap_code(KC_SPC);
			}
			return false;

		case KC_QUOT_MY:
			if (record->event.pressed) {
				tap_code(KC_QUOT);
				tap_code(KC_SPC);
			}
			return false;

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
			cursor_multiplier = 160;
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

// debug
//		char snum[5];
//		itoa(variable, snum, 10);
//		SEND_STRING(" ");
//		send_string(snum);
