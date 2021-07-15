//#include "dtostrf.h"
#include "tinyexpr.h"
#include <stdlib.h>
#include <stdio.h>
#include "print.h"
#include "icarus.h"

#define _main 0
#define _calc 1
#define _func 2

/* WHY WONT THIS WORK */
#define EXPRESSIONS_BUFF_SIZE 64
int input_count = 0;
char expressions_buffer[EXPRESSIONS_BUFF_SIZE];
int decimal_point_precision = 3;
int print_size = 4;
double te_interp(const char *expression, int *error);
char *dtostrf (double val, signed char width, unsigned char prec, char *sout);

enum custom_keycodes {
    CALC_PRINT = SAFE_RANGE,
    CALC_1,
    CALC_2,
    CALC_3,
    CALC_4,
    CALC_5,
    CALC_6,
    CALC_7,
    CALC_8,
    CALC_9,
    CALC_0,
    CALC_ADD,
    CALC_SUB,
    CALC_MUL,
    CALC_DIV,
    CALC_EQL,
    CALC_EXP,
    CALC_MOD,

    CALC_PI,
    CALC_E,
    CALC_SIN,
    CALC_COS,
    CALC_TAN,
    CALC_SINH,
    CALC_COSH,
    CALC_TANH,
    CALC_ACOS,
    CALC_ASIN,
    CALC_ATAN,
    CALC_ATAN2,
    CALC_SQRT,
    CALC_LN,
    CALC_LOG,
    CALC_LPR,
    CALC_RPR,
    CALC_EXIT,
};
void write_char_to_buff(char c);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_main] = LAYOUT_MACROPAD(
        TG(_calc), KC_SLSH, KC_ASTR, KC_MINS,
        KC_7     , KC_8   , KC_9   , KC_PLUS,
        KC_4     , KC_5   , KC_6   , KC_EQL,
        KC_1     , KC_2   , KC_3   , RESET,
        KC_0     , KC_COMM, KC_DOT , KC_ENT
    ),
    [_calc] = LAYOUT_MACROPAD(
        TG(_calc), CALC_DIV  , CALC_MUL  , CALC_SUB,
        CALC_7 , CALC_8    , CALC_9    , CALC_ADD,
        CALC_4 , CALC_5    , CALC_6    , CALC_EXP,
        CALC_1 , CALC_2    , CALC_3    , CALC_MOD,
        CALC_0 , TG(_func) , CALC_PRINT, CALC_EQL
        //TG(_calc), TG(_func), KC_DOT, CALC_PRINT
        
    ),
    [_func] = LAYOUT_MACROPAD(
        RESET  , CALC_E  , CALC_LOG, CALC_LN ,
        CALC_PI, CALC_SIN, CALC_COS, CALC_TAN,
        CALC_SINH, CALC_COSH, CALC_TANH, CALC_SQRT,
        CALC_ATAN2, CALC_ASIN, CALC_ACOS, CALC_ATAN,
        CALC_LPR, TG(_func), CALC_RPR, KC_TRNS
    ),
    /*
    [_game] = LAYOUT_MACROPAD(
        KC_4, KC_R, KC_F, TG(_func),
        KC_3, KC_E, KC_D, KC_C,
        KC_2, KC_W, KC_S, KC_X,
        KC_1, KC_Q, KC_A, KC_Z,
        KC_ESC, KC_TAB, KC_LSFT, KC_LCTL
    ),*/
};
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _calc:
        break;
    case _func:
        break;
    default: //  for any other layers, or the default layer
        input_count = 0;
        // expressions_buffer[0] = '\0';
        oled_clear();
        break;
    }
  return state;
}
#ifdef OLED_DRIVER_ENABLE

void write_buffer(void) {
    oled_write_P(PSTR("\nIN:"), false);
    oled_write((expressions_buffer), false);
}

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR(" Main"), layer_state_is(_main));
    oled_write_P(PSTR(" Calc"), layer_state_is(_calc));
    oled_write_P(PSTR(" Func"), layer_state_is(_func));
    //oled_write_P(PSTR("Game"), layer_state_is(_game));
}
void oled_task_user(void) {
    render_layer_state();

}
#endif 


void write_char_to_buff (char c) {
    if (input_count + 1 < EXPRESSIONS_BUFF_SIZE)
    {
        expressions_buffer[input_count] = c;
        expressions_buffer[input_count + 1] = '\0';
        input_count++;
        #ifdef OLED_DRIVER_ENABLE
        write_buffer();
        #endif
    }
}
char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
  char fmt[20];
  sprintf(fmt, "%%%d.%df", width, prec);
  sprintf(sout, fmt, val);
  return sout;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
    /*
    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif
    return true;*/
  switch (keycode) {
    case CALC_1:
        if (record->event.pressed) {
            write_char_to_buff('1');
        }
        
        break;
    case CALC_2:
        if (record->event.pressed) {
            write_char_to_buff('2');
        }
        
        break;
    case CALC_3:
        if (record->event.pressed) {
            write_char_to_buff('3');
        }
        
        break;
    case CALC_4:
        if (record->event.pressed) {
            write_char_to_buff('4');
        }
        
        break;
    case CALC_5:
        if (record->event.pressed) {
            write_char_to_buff('5');
        }
        
        break;
    case CALC_6:
        if (record->event.pressed) {
            write_char_to_buff('6');
        }
        
        break;
    case CALC_7:
        if (record->event.pressed) {
            write_char_to_buff('7');
        }
        
        break;
    case CALC_8:
        if (record->event.pressed) {
            write_char_to_buff('8');
        }
        
        break;
    case CALC_9:
        if (record->event.pressed) {
            write_char_to_buff('9');
        }
        
        break;
    case CALC_0:
        if (record->event.pressed) {
            write_char_to_buff('0');
        }
        
        break;
    case CALC_ADD:
        if (record->event.pressed) {
            write_char_to_buff('+');
        }
        
        break;
    case CALC_SUB:
        if (record->event.pressed) {
            write_char_to_buff('-');
        }
        
        break;
    case CALC_DIV:
        if (record->event.pressed) {
            write_char_to_buff('/');
        }
        
        break;
    case CALC_MUL:
        if (record->event.pressed) {
            write_char_to_buff('*');
        }
        
        break;
    case CALC_EXP:
        if (record->event.pressed) {
            write_char_to_buff('^');
        }
        
        break;
    case CALC_MOD:
        if (record->event.pressed) {
            write_char_to_buff('%');
        }
        
        break;
    
    case CALC_SIN:
        if (record->event.pressed) {
           write_char_to_buff('s');
           write_char_to_buff('i');
           write_char_to_buff('n');
        }
        
        break;
    case CALC_COS:
        if (record->event.pressed) {
           write_char_to_buff('c');
           write_char_to_buff('o');
           write_char_to_buff('s');
        }
        
        break;
    case CALC_TAN:
        if (record->event.pressed) {
           write_char_to_buff('t');
           write_char_to_buff('a');
           write_char_to_buff('n');
        }
        
        break;
    case CALC_PI:
        if (record->event.pressed) {
           write_char_to_buff('p');
           write_char_to_buff('i');
        }
        
        break;
    case CALC_E:
        if (record->event.pressed) {
           write_char_to_buff('e');
        }
        
        break;
    case CALC_SINH:
        if (record->event.pressed) {
           write_char_to_buff('s');
           write_char_to_buff('i');
           write_char_to_buff('n');
           write_char_to_buff('h');
        }
        
        break;
    case CALC_COSH:
        if (record->event.pressed) {
           write_char_to_buff('c');
           write_char_to_buff('o');
           write_char_to_buff('s');
           write_char_to_buff('h');
        }
        
        break;
    case CALC_TANH:
        if (record->event.pressed) {
           write_char_to_buff('t');
           write_char_to_buff('a');
           write_char_to_buff('n');
           write_char_to_buff('h');
        }
        
        break;
    case CALC_ASIN:
        if (record->event.pressed) {
           write_char_to_buff('a');
           write_char_to_buff('s');
           write_char_to_buff('i');
           write_char_to_buff('n');
        }
        
        break;
    case CALC_ACOS:
        if (record->event.pressed) {
           write_char_to_buff('a');
           write_char_to_buff('c');
           write_char_to_buff('o');
           write_char_to_buff('s');
        }
        
        break;
    case CALC_ATAN:
        if (record->event.pressed) {
           write_char_to_buff('a');
           write_char_to_buff('t');
           write_char_to_buff('a');
           write_char_to_buff('n');
        }
        break;
    case CALC_ATAN2:
        if (record->event.pressed) {
           write_char_to_buff('a');
           write_char_to_buff('t');
           write_char_to_buff('a');
           write_char_to_buff('n');
           write_char_to_buff('2');

        }
        break;
    case CALC_SQRT:
        if (record->event.pressed) {
           write_char_to_buff('s');
           write_char_to_buff('q');
           write_char_to_buff('r');
           write_char_to_buff('t');
        }
        break;
    case CALC_LOG:
        if (record->event.pressed) {
           write_char_to_buff('l');
           write_char_to_buff('o');
           write_char_to_buff('g');
        }
        break;
    case CALC_LN:
        if (record->event.pressed) {
           write_char_to_buff('l');
           write_char_to_buff('n');
        }
        break;
    case CALC_LPR:
        if (record->event.pressed) {
           write_char_to_buff('(');
        }
        break;
    case CALC_RPR:
        if (record->event.pressed) {
           write_char_to_buff(')');
        }
        break;
    case CALC_EXIT:
        if (record->event.pressed) {
           printf("EXIT");
           //input_count = 0;
           //expressions_buffer[0] = '\0';
           layer_off(_calc);
        }
        break;
    case CALC_PRINT:
        if (record->event.pressed) {
            if (input_count > 0){
            printf("\nCALC_PRINT");
            send_string(expressions_buffer);
            }
        }
        break;
    case CALC_EQL:
        if (record->event.pressed) {
            dprint("\nEquals:");
            dprintf("\n value of expressions buffer: %.64s\n", expressions_buffer);
            send_string(expressions_buffer);
            double result;
            result = te_interp(expressions_buffer, 0);
            dprintf("Result: %.64f\n", result);
            char output_string[EXPRESSIONS_BUFF_SIZE];
            dtostrf(result, print_size, decimal_point_precision, output_string);
            dprintf("\nOutput String: %s", output_string);
            send_string(output_string);
            input_count = 0;
            expressions_buffer[0] = '\0';
            #ifdef OLED_DRIVER_ENABLE
            oled_clear();
            #endif
        }
        return false;
        break;

    default:
        return true;
  }
  return true;
}
