#include QMK_KEYBOARD_H
#include "keymap.h"
#include "action_tapping.h" // necessary for action_tapping_process


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
