#include "print.h"
#include QMK_KEYBOARD_H
#include "tinyexpr.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define _BASE  0
#define _CALC  1
#define _EXTRA 2

#define EXPRESSIONS_BUFF_SIZE 64
int input_count = 0;
char expressions_buffer[EXPRESSIONS_BUFF_SIZE];
int decimal_point_precision = 3;

void write_char_to_buff (char c) {
    if (input_count + 1 < EXPRESSIONS_BUFF_SIZE)
    {
        expressions_buffer[input_count] = c;
        expressions_buffer[input_count + 1] = '\0';
        input_count++;
        /*
        #ifdef OLED_DRIVER_ENABLE
        void oled_task_user(void) {
            oled_write_P(PSTR(expressions_buffer), false);
        }
        #endif
        */
    }
}
/*
void print_result (const char *expressions_buffer)
{
  double result = te_interp (expressions_buffer, 0);
  char output_string[EXPRESSIONS_BUFF_SIZE];
  dtostrf(result, 1, decimal_point_precision, output_string);
  printf ("%s", result);
}
*/
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
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = ortho_4x5(
        RESET, KC_SLSH, KC_ASTR, KC_MINS,
        KC_7 , KC_8   , KC_9   , KC_PLUS,
        KC_4 , KC_5   , KC_6   , KC_EQL,
        KC_1 , KC_2   , KC_3   , KC_MINS,
        KC_0 , KC_COMM, KC_DOT , KC_ENT
    ),
    [_CALC] = ortho_4x5(
        KC_TRNS, CALC_DIV  , CALC_MUL  , CALC_SUB,
        CALC_7, CALC_8    , CALC_9    , CALC_ADD,
        CALC_4, CALC_5    , CALC_6    , CALC_EXP,
        CALC_1, CALC_2    , CALC_3    , CALC_MOD,
        CALC_0, TG(_EXTRA), CALC_PRINT, CALC_EQL
    ),
};
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif 
  return true;
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
    case CALC_PRINT:
        if (record->event.pressed) {
            send_string(expressions_buffer);
        }
        break;
    case CALC_EQL:
        if (record->event.pressed) {
            double result = te_interp(expressions_buffer, 0);
            char output_string(EXPRESSIONS_BUFF_SIZE);
            dtostrf(result, 1, decimal_point_precision, output_string);
            send_string(output_string);
            input_count = 0;
        }
        break;

    default:
        return true;
  }
}

#ifdef OLED_DRIVER_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}
void oled_task_user(void) { render_logo(); }
#endif

