// #include "dtostrf.h"
// #include "tinyexpr.c"
#include "tinyexpr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include "print.h"
#include "icarus.h"

#define _main 0
#define _calc 1
#define _func 2

/* WHY WONT THIS WORK */
#define EXPRESSIONS_BUFF_SIZE 64
int            input_count = 0;
char           expressions_buffer[EXPRESSIONS_BUFF_SIZE];
int            decimal_point_precision = 3;
int            error;
bool           use_degree = true;
bool           use_float  = false;
typedef double float64_t;

/*
#############################################################################################
#############################################################################################
#                                                                                           #
#                            TinyExpr Definitions / Declarations                            #
#                                                                                           #
#############################################################################################
#############################################################################################
*/
// typedef struct te_expr {
//     int type;
//     union {double value; const double *bound; const void *function;};
//     void *parameters[1];
// } te_expr;

// enum {
//     TE_VARIABLE = 0,

//     TE_FUNCTION0 = 8, TE_FUNCTION1, TE_FUNCTION2, TE_FUNCTION3,
//     TE_FUNCTION4, TE_FUNCTION5, TE_FUNCTION6, TE_FUNCTION7,

//     TE_CLOSURE0 = 16, TE_CLOSURE1, TE_CLOSURE2, TE_CLOSURE3,
//     TE_CLOSURE4, TE_CLOSURE5, TE_CLOSURE6, TE_CLOSURE7,

//     TE_FLAG_PURE = 32
// };

// typedef struct te_variable {
//     const char *name;
//     const void *address;
//     int type;
//     void *context;
// } te_variable;

// /* Parses the input expression, evaluates it, and frees it. */
// /* Returns NaN on error. */
// double te_interp(const char *expression, int *error);

// /* Parses the input expression and binds variables. */
// /* Returns NULL on error. */
// te_expr *te_compile(const char *expression, const te_variable *variables, int var_count, int *error);

// /* Evaluates the expression. */
// double te_eval(const te_expr *n);

// /* Prints debugging information on the syntax tree. */
// void te_print(const te_expr *n);

// /* Frees the expression. */
// /* This is safe to call on NULL pointers. */
// void te_free(te_expr *n);
/*
#############################################################################################
#############################################################################################
#                                                                                           #
#                            End of TinyExpr Definitions / Declarations                     #
#                                                                                           #
#############################################################################################
#############################################################################################
*/
void write_char_to_buff(char c, bool oled_write);

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
    CALC_DOT,
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
    CALC_BSPACE,
    CALC_COM,
};
void write_buffer(void) {
    oled_write_P(PSTR("\nIN:"), false);
    oled_write((expressions_buffer), false);
    oled_write_P(PSTR("\nOUT:"), false);
    double out_calc = te_interp(expressions_buffer, &error);
    if (error == 0) {
        char oled_string[EXPRESSIONS_BUFF_SIZE];
        if (use_float) {
            sprintf(oled_string, "%.*f", decimal_point_precision, out_calc);
        } else {
            sprintf(oled_string, "%.*g", decimal_point_precision, out_calc);
        }
        oled_write(oled_string, false);
    } else {
        oled_write_P(PSTR("NAN"), true);
    }
    oled_write_P(PSTR("\nPRS: "), false);
    char precision_string[] = "";
    sprintf(precision_string, "%d", decimal_point_precision);
    oled_write(precision_string, false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("DEG"), use_degree);
    oled_write_P(PSTR("RAD"), !use_degree);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("FP"), use_float);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("SCI"), !use_float);
}
enum {
    CALC_COMPR,
    CALC_DOTPR,
    CALC_EXPMOD,
    CALC_UPPER,
    CALC_DWNPR,
    CALC_SUBCL,
    CALC_MODE,
    FUNC_LPR,
    TAP_EQL,
};
void dance_compr_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        write_char_to_buff(',', true);
    } else if (state->count == 2) {
        write_char_to_buff('(', true);
    } else {
        if (use_float) {
            use_float = false;

        } else {
            use_float = true;
        }
        oled_clear();
        write_buffer();
    }
}
void dance_dotpr_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        write_char_to_buff('.', true);
    } else {
        write_char_to_buff(')', true);
    }
}
void dance_expmod_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        write_char_to_buff('^', true);
    } else {
        write_char_to_buff('%', true);
    }
}
void dance_upper_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        write_char_to_buff('*', true);
    } else {
        if (decimal_point_precision < 17) {
            decimal_point_precision += 1;
#ifdef OLED_DRIVER_ENABLE
            oled_clear();
            write_buffer();
#endif
        }
    }
}
void dance_dwnpr_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        write_char_to_buff('/', true);
    } else {
        if (decimal_point_precision > 1) {
            decimal_point_precision -= 1;
#ifdef OLED_DRIVER_ENABLE
            oled_clear();
            write_buffer();
#endif
        }
    }
}
void dance_subcl_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        write_char_to_buff('-', true);
    } else {
        if (input_count > 1) {
            input_count = 0;
        }
    }
}
void dance_funlpr_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        write_char_to_buff('(', true);
    } else {
        reset_keyboard();
    }
}
void dance_mode_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        write_char_to_buff('+', true);
    } else {
        if (use_degree) {
            use_degree = false;
            oled_clear();
            write_buffer();
        } else {
            use_degree = true;
            oled_clear();
            write_buffer();
        }
    }
}
// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [CALC_COMPR]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_compr_finished, NULL),   //\n
    [CALC_DOTPR]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dotpr_finished, NULL),   //\n
    [CALC_EXPMOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_expmod_finished, NULL),  //\n
    [CALC_UPPER]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_upper_finished, NULL),   //\n
    [CALC_DWNPR]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_dwnpr_finished, NULL),   //\n
    [CALC_SUBCL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_subcl_finished, NULL),   //\n
    [FUNC_LPR]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_funlpr_finished, NULL),  //\n
    [CALC_MODE]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_mode_finished, NULL),    //\n
    [TAP_EQL]     = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_CIRC),                         //\n
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_main] = LAYOUT_MACROPAD(
        TO(_calc), KC_SLSH, KC_ASTR, KC_BSPACE,
        KC_7     , KC_8   , KC_9   , KC_PLUS,
        KC_4     , KC_5   , KC_6   , TD(TAP_EQL),
        KC_1     , KC_2   , KC_3   , KC_MINS,
        KC_0     , KC_COMM, KC_DOT , KC_ENT
    ),
    [_calc] = LAYOUT_MACROPAD(
        TO(_func), TD(CALC_DWNPR), TD(CALC_UPPER)  , CALC_BSPACE,
        CALC_7   , CALC_8    , CALC_9    , TD(CALC_MODE),
        CALC_4   , CALC_5    , CALC_6    , TD(CALC_EXPMOD),
        CALC_1   , CALC_2    , CALC_3    , TD(CALC_SUBCL),
        CALC_0   , TD(CALC_COMPR), TD(CALC_DOTPR), CALC_EQL

    ),
    [_func] = LAYOUT_MACROPAD(
        TO(_main), CALC_LN  , CALC_LOG, CALC_BSPACE ,
        CALC_E, CALC_SIN, CALC_COS, CALC_TAN,
        CALC_SINH, CALC_COSH, CALC_TANH, CALC_SQRT,
        CALC_ATAN2, CALC_ASIN, CALC_ACOS, CALC_ATAN,
        CALC_LPR, TD(FUNC_LPR), CALC_RPR, CALC_PI
    ),
    // clang-format o
};
#ifdef CONSOLE_ENABLE
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
#endif
#ifdef OLED_DRIVER_ENABLE

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER "), false);
    oled_write_P(PSTR("Main"), layer_state_is(_main));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Calc"), layer_state_is(_calc));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("Func"), layer_state_is(_func));
}
void main_keymap(void) {
    oled_write_P(PSTR("LY / * <-\n"), false);
    oled_write_P(PSTR("LY / * <-...7 8 9 +\n"), false);
    oled_write_P(PSTR("4 5 6 =\n"), false);
    oled_write_P(PSTR("1 2 3 -...0 , . ENT"), false);

}
void oled_task_user(void) {
    render_layer_state();
}
#endif


void write_char_to_buff (char c, bool oled_write) {
    if (input_count + 1 < EXPRESSIONS_BUFF_SIZE)
    {
        expressions_buffer[input_count] = c;
        expressions_buffer[input_count + 1] = '\0';
        input_count++;
        #ifdef OLED_DRIVER_ENABLE
        if (oled_write) {
            write_buffer();
        }
        #endif
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _calc:
        #ifdef OLED_DRIVER_ENABLE
        oled_clear();
        write_buffer();
        #endif
        break;
    case _func:
        #ifdef OLED_DRIVER_ENABLE
        oled_clear();
        write_buffer();
        #endif
        break;
    default: //  for any other layers, or the default layer
        //input_count = 0;
        oled_clear();
        write_buffer();
        //main_keymap();
        break;
    }
  return state;
}
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(CALC_UPPER):
            return TAPPING_TERM + 50;
        case TD(CALC_DWNPR):
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
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
            write_char_to_buff('1', true);
        }

        break;
    case CALC_2:
        if (record->event.pressed) {
            write_char_to_buff('2', true);
        }

        break;
    case CALC_3:
        if (record->event.pressed) {
            write_char_to_buff('3', true);
        }

        break;
    case CALC_4:
        if (record->event.pressed) {
            write_char_to_buff('4', true);
        }

        break;
    case CALC_5:
        if (record->event.pressed) {
            write_char_to_buff('5', true);
        }

        break;
    case CALC_6:
        if (record->event.pressed) {
            write_char_to_buff('6', true);
        }

        break;
    case CALC_7:
        if (record->event.pressed) {
            write_char_to_buff('7', true);
        }

        break;
    case CALC_8:
        if (record->event.pressed) {
            write_char_to_buff('8', true);
        }

        break;
    case CALC_9:
        if (record->event.pressed) {
            write_char_to_buff('9', true);
        }

        break;
    case CALC_0:
        if (record->event.pressed) {
            write_char_to_buff('0', true);
        }

        break;
    case CALC_ADD:
        if (record->event.pressed) {
            write_char_to_buff('+', true);
        }

        break;
    case CALC_SUB:
        if (record->event.pressed) {
            write_char_to_buff('-', true);
        }

        break;
    case CALC_DIV:
        if (record->event.pressed) {
            write_char_to_buff('/', true);
        }
    case CALC_DOT:
        if (record->event.pressed) {
            write_char_to_buff('.', true);
        }
        break;
    case CALC_MUL:
        if (record->event.pressed) {
            write_char_to_buff('*', true);
        }

        break;
    case CALC_EXP:
        if (record->event.pressed) {
            write_char_to_buff('^', true);
        }

        break;
    case CALC_MOD:
        if (record->event.pressed) {
            write_char_to_buff('%', true);
        }

        break;
    case CALC_COM:
        if (record->event.pressed) {
            write_char_to_buff(',', true);
        }
        break;


    case CALC_SIN:
        if (record->event.pressed) {
           write_char_to_buff('s', false);
           write_char_to_buff('i', false);
           write_char_to_buff('n', false);
           write_char_to_buff('(', true);
        }

        break;
    case CALC_COS:
        if (record->event.pressed) {
           write_char_to_buff('c', false);
           write_char_to_buff('o', false);
           write_char_to_buff('s', false);
           write_char_to_buff('(', true);
        }

        break;
    case CALC_TAN:
        if (record->event.pressed) {
           write_char_to_buff('t', false);
           write_char_to_buff('a', false);
           write_char_to_buff('n', false);
           write_char_to_buff('(', true);
        }

        break;
    case CALC_PI:
        if (record->event.pressed) {
           write_char_to_buff('p', false);
           write_char_to_buff('i', true);
        }

        break;
    case CALC_E:
        if (record->event.pressed) {
           write_char_to_buff('e', true);
        }

        break;
    case CALC_SINH:
        if (record->event.pressed) {
           write_char_to_buff('s', false);
           write_char_to_buff('i', false);
           write_char_to_buff('n', false);
           write_char_to_buff('h', false);
           write_char_to_buff('(', true);
        }

        break;
    case CALC_COSH:
        if (record->event.pressed) {
           write_char_to_buff('c', false);
           write_char_to_buff('o', false);
           write_char_to_buff('s', false);
           write_char_to_buff('h', false);
           write_char_to_buff('(', true);
        }

        break;
    case CALC_TANH:
        if (record->event.pressed) {
           write_char_to_buff('t', false);
           write_char_to_buff('a', false);
           write_char_to_buff('n', false);
           write_char_to_buff('h', false);
            write_char_to_buff('(', true);
        }

        break;
    case CALC_ASIN:
        if (record->event.pressed) {
           write_char_to_buff('a', false);
           write_char_to_buff('s', false);
           write_char_to_buff('i', false);
           write_char_to_buff('n', false);
           write_char_to_buff('(', true);
        }

        break;
    case CALC_ACOS:
        if (record->event.pressed) {
           write_char_to_buff('a', false);
           write_char_to_buff('c', false);
           write_char_to_buff('o', false);
           write_char_to_buff('s', false);
           write_char_to_buff('(', true);
        }

        break;
    case CALC_ATAN:
        if (record->event.pressed) {
           write_char_to_buff('a', false);
           write_char_to_buff('t', false);
           write_char_to_buff('a', false);
           write_char_to_buff('n', false);
           write_char_to_buff('(', true);
        }
        break;
    case CALC_ATAN2:
        if (record->event.pressed) {
           write_char_to_buff('a', false);
           write_char_to_buff('t', false);
           write_char_to_buff('a', false);
           write_char_to_buff('n', false);
           write_char_to_buff('2', false);
           write_char_to_buff('(', true);

        }
        break;
    case CALC_SQRT:
        if (record->event.pressed) {
           write_char_to_buff('s', false);
           write_char_to_buff('q', false);
           write_char_to_buff('r', false);
           write_char_to_buff('t', false);
           write_char_to_buff('(', true);
        }
        break;
    case CALC_LOG:
        if (record->event.pressed) {
           write_char_to_buff('l', false);
           write_char_to_buff('o', false);
           write_char_to_buff('g', false);
           write_char_to_buff('(', true);
        }
        break;
    case CALC_LN:
        if (record->event.pressed) {
           write_char_to_buff('l', false);
           write_char_to_buff('n', false);
           write_char_to_buff('(', true);
        }
        break;
    case CALC_LPR:
        if (record->event.pressed) {
           write_char_to_buff('(', true);
        }
        break;
    case CALC_RPR:
        if (record->event.pressed) {
           write_char_to_buff(')', true);
        }
        break;
    case CALC_BSPACE:
        if (record->event.pressed) {
            if (input_count > 0) {
            input_count -= 1;
            int i;
            for(i = input_count; i < strlen(expressions_buffer); i++)
                expressions_buffer[i] = expressions_buffer[i + 1];
            #ifdef OLED_DRIVER_ENABLE
            oled_clear();
            write_buffer();
            #endif
            }
        }
        break;
    case CALC_PRINT:
        if (record->event.pressed) {
            if (input_count > 0){
            printf("\nCALC_PRINT");
            send_string(expressions_buffer);
            /*double num = 4294967295 + 1;
            double num1 = 4294967295;
            long long num2 = 4294967295;
            uint64_t num3 = 4294967295;
            uint64_t num4 = (double) num1;
            char test_string[100] = "";
            sprintf(test_string, "%f", num);
            uprintf("\nTest_String: %s\n Number: %f\nNumber - 1: %f\n Number Long: %f\n Number UINT: %llu\n Number Convert: %llu", test_string, num, num1, num2, num3, num4);
            */
            }
        }
        break;
    case CALC_EQL:
        if (record->event.pressed) {
            if (input_count > 0) {
            double result = te_interp(expressions_buffer, &error);
            if (error == 0){
                char output_result[EXPRESSIONS_BUFF_SIZE] = "";
                if (use_float) {
                    sprintf(output_result, "%.*f", decimal_point_precision, result);
                } else {
                    sprintf(output_result, "%.*g", decimal_point_precision, result);
                }
                send_string(output_result);
                input_count = 0;
                expressions_buffer[0] = '\0';
                #ifdef OLED_DRIVER_ENABLE
                oled_clear();
                write_buffer();
                #endif
                } else {
                SEND_STRING("NaN");
                input_count = 0;
                expressions_buffer[0] = '\0';
                #ifdef OLED_DRIVER_ENABLE
                oled_clear();
                write_buffer();
                #endif
                }
            }
        }
        break;
    /*
    default:
        return true;*/
  }
  return true;
}
/*
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#                                                                                           #
#                               TinyExpr Functions                                          #
#                                                                                           #
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
*/



// #ifndef NAN
// #define NAN (0.0/0.0)
// #endif

// #ifndef INFINITY
// #define INFINITY (1.0/0.0)
// #endif


// typedef double (*te_fun2)(double, double);

// enum {
//     TOK_NULL = TE_CLOSURE7+1, TOK_ERROR, TOK_END, TOK_SEP,
//     TOK_OPEN, TOK_CLOSE, TOK_NUMBER, TOK_VARIABLE, TOK_INFIX
// };


// enum {TE_CONSTANT = 1};


// typedef struct state {
//     const char *start;
//     const char *next;
//     int type;
//     union {double value; const double *bound; const void *function;};
//     void *context;

//     const te_variable *lookup;
//     int lookup_len;
// } state;


// #define TYPE_MASK(TYPE) ((TYPE)&0x0000001F)

// #define IS_PURE(TYPE) (((TYPE) & TE_FLAG_PURE) != 0)
// #define IS_FUNCTION(TYPE) (((TYPE) & TE_FUNCTION0) != 0)
// #define IS_CLOSURE(TYPE) (((TYPE) & TE_CLOSURE0) != 0)
// #define ARITY(TYPE) ( ((TYPE) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((TYPE) & 0x00000007) : 0 )
// #define NEW_EXPR(type, ...) new_expr((type), (const te_expr*[]){__VA_ARGS__})

// static te_expr *new_expr(const int type, const te_expr *parameters[]) {
//     const int arity = ARITY(type);
//     const int psize = sizeof(void*) * arity;
//     const int size = (sizeof(te_expr) - sizeof(void*)) + psize + (IS_CLOSURE(type) ? sizeof(void*) : 0);
//     te_expr *ret = malloc(size);
//     memset(ret, 0, size);
//     if (arity && parameters) {
//         memcpy(ret->parameters, parameters, psize);
//     }
//     ret->type = type;
//     ret->bound = 0;
//     return ret;
// }


// void te_free_parameters(te_expr *n) {
//     if (!n) return;
//     switch (TYPE_MASK(n->type)) {
//         case TE_FUNCTION7: case TE_CLOSURE7: te_free(n->parameters[6]);     /* Falls through. */
//         case TE_FUNCTION6: case TE_CLOSURE6: te_free(n->parameters[5]);     /* Falls through. */
//         case TE_FUNCTION5: case TE_CLOSURE5: te_free(n->parameters[4]);     /* Falls through. */
//         case TE_FUNCTION4: case TE_CLOSURE4: te_free(n->parameters[3]);     /* Falls through. */
//         case TE_FUNCTION3: case TE_CLOSURE3: te_free(n->parameters[2]);     /* Falls through. */
//         case TE_FUNCTION2: case TE_CLOSURE2: te_free(n->parameters[1]);     /* Falls through. */
//         case TE_FUNCTION1: case TE_CLOSURE1: te_free(n->parameters[0]);
//     }
// }


// void te_free(te_expr *n) {
//     if (!n) return;
//     te_free_parameters(n);
//     free(n);
// }


// static double pi(void) {return 3.14159265358979323846;}
// static double e(void) {return 2.71828182845904523536;}
// static double fac(double a) {/* simplest version of fac */
//     if (a < 0.0)
//         return NAN;
//     if (a > UINT_MAX)
//         return INFINITY;
//     unsigned int ua = (unsigned int)(a);
//     unsigned long int result = 1, i;
//     for (i = 1; i <= ua; i++) {
//         if (i > ULONG_MAX / result)
//             return INFINITY;
//         result *= i;
//     }
//     return (double)result;
// }
// static double sin_d(double x) {
//     if (use_degree) {
//         x = x * (M_PI / 180); // convert to rads
//     }
//     return(sin(x));
// }
// static double cos_d(double x) {
//     if (use_degree) {
//         x = x * (M_PI / 180); // convert to rads
//     }
//     return(cos(x));
// }
// static double tan_d(double x) {
//     if (use_degree) {
//         x = x * (M_PI / 180); // convert to rads
//     }
//     return(tan(x));
// }
// static double ncr(double n, double r) {
//     if (n < 0.0 || r < 0.0 || n < r) return NAN;
//     if (n > UINT_MAX || r > UINT_MAX) return INFINITY;
//     unsigned long int un = (unsigned int)(n), ur = (unsigned int)(r), i;
//     unsigned long int result = 1;
//     if (ur > un / 2) ur = un - ur;
//     for (i = 1; i <= ur; i++) {
//         if (result > ULONG_MAX / (un - ur + i))
//             return INFINITY;
//         result *= un - ur + i;
//         result /= i;
//     }
//     return result;
// }
// static double npr(double n, double r) {return ncr(n, r) * fac(r);}

// static const te_variable functions[] = {
//     /* must be in alphabetical order */
//     {"abs", abs,     TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"acos", acos,    TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"asin", asin,    TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"atan", atan,    TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"atan2", atan2,  TE_FUNCTION2 | TE_FLAG_PURE, 0},
//     {"ceil", ceil,    TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"cos", cos_d,      TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"cosh", cosh,    TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"e", e,          TE_FUNCTION0 | TE_FLAG_PURE, 0},
//     {"exp", exp,      TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"fac", fac,      TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"floor", floor,  TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"ln", log,       TE_FUNCTION1 | TE_FLAG_PURE, 0},
// #ifdef TE_NAT_LOG
//     {"log", log,      TE_FUNCTION1 | TE_FLAG_PURE, 0},
// #else
//     {"log", log10,    TE_FUNCTION1 | TE_FLAG_PURE, 0},
// #endif
//     {"log10", log10,  TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"ncr", ncr,      TE_FUNCTION2 | TE_FLAG_PURE, 0},
//     {"npr", npr,      TE_FUNCTION2 | TE_FLAG_PURE, 0},
//     {"pi", pi,        TE_FUNCTION0 | TE_FLAG_PURE, 0},
//     {"pow", pow,      TE_FUNCTION2 | TE_FLAG_PURE, 0},
//     {"sin", sin_d,      TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"sinh", sinh,    TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"sqrt", sqrt,    TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"tan", tan_d,      TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {"tanh", tanh,    TE_FUNCTION1 | TE_FLAG_PURE, 0},
//     {0, 0, 0, 0}
// };

// static const te_variable *find_builtin(const char *name, int len) {
//     int imin = 0;
//     int imax = sizeof(functions) / sizeof(te_variable) - 2;

//     /*Binary search.*/
//     while (imax >= imin) {
//         const int i = (imin + ((imax-imin)/2));
//         int c = strncmp(name, functions[i].name, len);
//         if (!c) c = '\0' - functions[i].name[len];
//         if (c == 0) {
//             return functions + i;
//         } else if (c > 0) {
//             imin = i + 1;
//         } else {
//             imax = i - 1;
//         }
//     }

//     return 0;
// }

// static const te_variable *find_lookup(const state *s, const char *name, int len) {
//     int iters;
//     const te_variable *var;
//     if (!s->lookup) return 0;

//     for (var = s->lookup, iters = s->lookup_len; iters; ++var, --iters) {
//         if (strncmp(name, var->name, len) == 0 && var->name[len] == '\0') {
//             return var;
//         }
//     }
//     return 0;
// }



// static double add(double a, double b) {return a + b;}
// static double sub(double a, double b) {return a - b;}
// static double mul(double a, double b) {return a * b;}
// static double divide(double a, double b) {return a / b;}
// static double negate(double a) {return -a;}
// static double comma(double a, double b) {(void)a; return b;}


// void next_token(state *s) {
//     s->type = TOK_NULL;

//     do {

//         if (!*s->next){
//             s->type = TOK_END;
//             return;
//         }

//         /* Try reading a number. */
//         if ((s->next[0] >= '0' && s->next[0] <= '9') || s->next[0] == '.') {
//             s->value = strtod(s->next, (char**)&s->next);
//             s->type = TOK_NUMBER;
//         } else {
//             /* Look for a variable or builtin function call. */
//             if (s->next[0] >= 'a' && s->next[0] <= 'z') {
//                 const char *start;
//                 start = s->next;
//                 while ((s->next[0] >= 'a' && s->next[0] <= 'z') || (s->next[0] >= '0' && s->next[0] <= '9') || (s->next[0] == '_')) s->next++;

//                 const te_variable *var = find_lookup(s, start, s->next - start);
//                 if (!var) var = find_builtin(start, s->next - start);

//                 if (!var) {
//                     s->type = TOK_ERROR;
//                 } else {
//                     switch(TYPE_MASK(var->type))
//                     {
//                         case TE_VARIABLE:
//                             s->type = TOK_VARIABLE;
//                             s->bound = var->address;
//                             break;

//                         case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:         /* Falls through. */
//                         case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:         /* Falls through. */
//                             s->context = var->context;                                                  /* Falls through. */

//                         case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:     /* Falls through. */
//                         case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:     /* Falls through. */
//                             s->type = var->type;
//                             s->function = var->address;
//                             break;
//                     }
//                 }

//             } else {
//                 /* Look for an operator or special character. */
//                 switch (s->next++[0]) {
//                     case '+': s->type = TOK_INFIX; s->function = add; break;
//                     case '-': s->type = TOK_INFIX; s->function = sub; break;
//                     case '*': s->type = TOK_INFIX; s->function = mul; break;
//                     case '/': s->type = TOK_INFIX; s->function = divide; break;
//                     case '^': s->type = TOK_INFIX; s->function = pow; break;
//                     case '%': s->type = TOK_INFIX; s->function = fmod; break;
//                     case '(': s->type = TOK_OPEN; break;
//                     case ')': s->type = TOK_CLOSE; break;
//                     case ',': s->type = TOK_SEP; break;
//                     case ' ': case '\t': case '\n': case '\r': break;
//                     default: s->type = TOK_ERROR; break;
//                 }
//             }
//         }
//     } while (s->type == TOK_NULL);
// }


// static te_expr *list(state *s);
// static te_expr *expr(state *s);
// static te_expr *power(state *s);

// static te_expr *base(state *s) {
//     /* <base>      =    <constant> | <variable> | <function-0> {"(" ")"} | <function-1> <power> | <function-X> "(" <expr> {"," <expr>} ")" | "(" <list> ")" */
//     te_expr *ret;
//     int arity;

//     switch (TYPE_MASK(s->type)) {
//         case TOK_NUMBER:
//             ret = new_expr(TE_CONSTANT, 0);
//             ret->value = s->value;
//             next_token(s);
//             break;

//         case TOK_VARIABLE:
//             ret = new_expr(TE_VARIABLE, 0);
//             ret->bound = s->bound;
//             next_token(s);
//             break;

//         case TE_FUNCTION0:
//         case TE_CLOSURE0:
//             ret = new_expr(s->type, 0);
//             ret->function = s->function;
//             if (IS_CLOSURE(s->type)) ret->parameters[0] = s->context;
//             next_token(s);
//             if (s->type == TOK_OPEN) {
//                 next_token(s);
//                 if (s->type != TOK_CLOSE) {
//                     s->type = TOK_ERROR;
//                 } else {
//                     next_token(s);
//                 }
//             }
//             break;

//         case TE_FUNCTION1:
//         case TE_CLOSURE1:
//             ret = new_expr(s->type, 0);
//             ret->function = s->function;
//             if (IS_CLOSURE(s->type)) ret->parameters[1] = s->context;
//             next_token(s);
//             ret->parameters[0] = power(s);
//             break;

//         case TE_FUNCTION2: case TE_FUNCTION3: case TE_FUNCTION4:
//         case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
//         case TE_CLOSURE2: case TE_CLOSURE3: case TE_CLOSURE4:
//         case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
//             arity = ARITY(s->type);

//             ret = new_expr(s->type, 0);
//             ret->function = s->function;
//             if (IS_CLOSURE(s->type)) ret->parameters[arity] = s->context;
//             next_token(s);

//             if (s->type != TOK_OPEN) {
//                 s->type = TOK_ERROR;
//             } else {
//                 int i;
//                 for(i = 0; i < arity; i++) {
//                     next_token(s);
//                     ret->parameters[i] = expr(s);
//                     if(s->type != TOK_SEP) {
//                         break;
//                     }
//                 }
//                 if(s->type != TOK_CLOSE || i != arity - 1) {
//                     s->type = TOK_ERROR;
//                 } else {
//                     next_token(s);
//                 }
//             }

//             break;

//         case TOK_OPEN:
//             next_token(s);
//             ret = list(s);
//             if (s->type != TOK_CLOSE) {
//                 s->type = TOK_ERROR;
//             } else {
//                 next_token(s);
//             }
//             break;

//         default:
//             ret = new_expr(0, 0);
//             s->type = TOK_ERROR;
//             ret->value = NAN;
//             break;
//     }

//     return ret;
// }


// static te_expr *power(state *s) {
//     /* <power>     =    {("-" | "+")} <base> */
//     int sign = 1;
//     while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
//         if (s->function == sub) sign = -sign;
//         next_token(s);
//     }

//     te_expr *ret;

//     if (sign == 1) {
//         ret = base(s);
//     } else {
//         ret = NEW_EXPR(TE_FUNCTION1 | TE_FLAG_PURE, base(s));
//         ret->function = negate;
//     }

//     return ret;
// }

// #ifdef TE_POW_FROM_RIGHT
// static te_expr *factor(state *s) {
//     /* <factor>    =    <power> {"^" <power>} */
//     te_expr *ret = power(s);

//     int neg = 0;

//     if (ret->type == (TE_FUNCTION1 | TE_FLAG_PURE) && ret->function == negate) {
//         te_expr *se = ret->parameters[0];
//         free(ret);
//         ret = se;
//         neg = 1;
//     }

//     te_expr *insertion = 0;

//     while (s->type == TOK_INFIX && (s->function == pow)) {
//         te_fun2 t = s->function;
//         next_token(s);

//         if (insertion) {
//             /* Make exponentiation go right-to-left. */
//             te_expr *insert = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, insertion->parameters[1], power(s));
//             insert->function = t;
//             insertion->parameters[1] = insert;
//             insertion = insert;
//         } else {
//             ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, power(s));
//             ret->function = t;
//             insertion = ret;
//         }
//     }

//     if (neg) {
//         ret = NEW_EXPR(TE_FUNCTION1 | TE_FLAG_PURE, ret);
//         ret->function = negate;
//     }

//     return ret;
// }
// #else
// static te_expr *factor(state *s) {
//     /* <factor>    =    <power> {"^" <power>} */
//     te_expr *ret = power(s);

//     while (s->type == TOK_INFIX && (s->function == pow)) {
//         te_fun2 t = s->function;
//         next_token(s);
//         ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, power(s));
//         ret->function = t;
//     }

//     return ret;
// }
// #endif



// static te_expr *term(state *s) {
//     /* <term>      =    <factor> {("*" | "/" | "%") <factor>} */
//     te_expr *ret = factor(s);

//     while (s->type == TOK_INFIX && (s->function == mul || s->function == divide || s->function == fmod)) {
//         te_fun2 t = s->function;
//         next_token(s);
//         ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, factor(s));
//         ret->function = t;
//     }

//     return ret;
// }


// static te_expr *expr(state *s) {
//     /* <expr>      =    <term> {("+" | "-") <term>} */
//     te_expr *ret = term(s);

//     while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
//         te_fun2 t = s->function;
//         next_token(s);
//         ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, term(s));
//         ret->function = t;
//     }

//     return ret;
// }


// static te_expr *list(state *s) {
//     /* <list>      =    <expr> {"," <expr>} */
//     te_expr *ret = expr(s);

//     while (s->type == TOK_SEP) {
//         next_token(s);
//         ret = NEW_EXPR(TE_FUNCTION2 | TE_FLAG_PURE, ret, expr(s));
//         ret->function = comma;
//     }

//     return ret;
// }


// #define TE_FUN(...) ((double(*)(__VA_ARGS__))n->function)
// #define M_tinyexpr(e) te_eval(n->parameters[e])


// double te_eval(const te_expr *n) {
//     if (!n) return NAN;

//     switch(TYPE_MASK(n->type)) {
//         case TE_CONSTANT: return n->value;
//         case TE_VARIABLE: return *n->bound;

//         case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
//         case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
//             switch(ARITY(n->type)) {
//                 case 0: return TE_FUN(void)();
//                 case 1: return TE_FUN(double)(M_tinyexpr(0));
//                 case 2: return TE_FUN(double, double)(M_tinyexpr(0), M_tinyexpr(1));
//                 case 3: return TE_FUN(double, double, double)(M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2));
//                 case 4: return TE_FUN(double, double, double, double)(M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3));
//                 case 5: return TE_FUN(double, double, double, double, double)(M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4));
//                 case 6: return TE_FUN(double, double, double, double, double, double)(M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4), M_tinyexpr(5));
//                 case 7: return TE_FUN(double, double, double, double, double, double, double)(M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4), M_tinyexpr(5), M_tinyexpr(6));
//                 default: return NAN;
//             }

//         case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
//         case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
//             switch(ARITY(n->type)) {
//                 case 0: return TE_FUN(void*)(n->parameters[0]);
//                 case 1: return TE_FUN(void*, double)(n->parameters[1], M_tinyexpr(0));
//                 case 2: return TE_FUN(void*, double, double)(n->parameters[2], M_tinyexpr(0), M_tinyexpr(1));
//                 case 3: return TE_FUN(void*, double, double, double)(n->parameters[3], M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2));
//                 case 4: return TE_FUN(void*, double, double, double, double)(n->parameters[4], M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3));
//                 case 5: return TE_FUN(void*, double, double, double, double, double)(n->parameters[5], M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4));
//                 case 6: return TE_FUN(void*, double, double, double, double, double, double)(n->parameters[6], M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4), M_tinyexpr(5));
//                 case 7: return TE_FUN(void*, double, double, double, double, double, double, double)(n->parameters[7], M_tinyexpr(0), M_tinyexpr(1), M_tinyexpr(2), M_tinyexpr(3), M_tinyexpr(4), M_tinyexpr(5), M_tinyexpr(6));
//                 default: return NAN;
//             }

//         default: return NAN;
//     }

// }

// #undef TE_FUN
// #undef M_tinyexpr

// static void optimize(te_expr *n) {
//     /* Evaluates as much as possible. */
//     if (n->type == TE_CONSTANT) return;
//     if (n->type == TE_VARIABLE) return;

//     /* Only optimize out functions flagged as pure. */
//     if (IS_PURE(n->type)) {
//         const int arity = ARITY(n->type);
//         int known = 1;
//         int i;
//         for (i = 0; i < arity; ++i) {
//             optimize(n->parameters[i]);
//             if (((te_expr*)(n->parameters[i]))->type != TE_CONSTANT) {
//                 known = 0;
//             }
//         }
//         if (known) {
//             const double value = te_eval(n);
//             te_free_parameters(n);
//             n->type = TE_CONSTANT;
//             n->value = value;
//         }
//     }
// }


// te_expr *te_compile(const char *expression, const te_variable *variables, int var_count, int *error) {
//     state s;
//     s.start = s.next = expression;
//     s.lookup = variables;
//     s.lookup_len = var_count;

//     next_token(&s);
//     te_expr *root = list(&s);

//     if (s.type != TOK_END) {
//         te_free(root);
//         if (error) {
//             *error = (s.next - s.start);
//             if (*error == 0) *error = 1;
//         }
//         return 0;
//     } else {
//         optimize(root);
//         if (error) *error = 0;
//         return root;
//     }
// }


// double te_interp(const char *expression, int *error) {
//     te_expr *n = te_compile(expression, 0, 0, error);
//     double ret;
//     if (n) {
//         ret = te_eval(n);
//         te_free(n);
//     } else {
//         ret = NAN;
//     }
//     return ret;
// }

// static void pn (const te_expr *n, int depth) {
//     int i, arity;
//     printf("%*s", depth, "");

//     switch(TYPE_MASK(n->type)) {
//     case TE_CONSTANT: printf("%f\n", n->value); break;
//     case TE_VARIABLE: printf("bound %p\n", n->bound); break;

//     case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
//     case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
//     case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
//     case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
//          arity = ARITY(n->type);
//          printf("f%d", arity);
//          for(i = 0; i < arity; i++) {
//              printf(" %p", n->parameters[i]);
//          }
//          printf("\n");
//          for(i = 0; i < arity; i++) {
//              pn(n->parameters[i], depth + 1);
//          }
//          break;
//     }
// }


// void te_print(const te_expr *n) {
//     pn(n, 0);
// }

/*
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#                                                                                           #
#                              End OF TinyExpr Functions                                    #
#                                                                                           #
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
#############################################################################################
*/
