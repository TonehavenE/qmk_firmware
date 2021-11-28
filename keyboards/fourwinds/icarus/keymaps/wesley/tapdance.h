#define _main 0
#define _calc 1

#define EXPRESSIONS_BUFF_SIZE 64
int            input_count = 0;
char           expressions_buffer[EXPRESSIONS_BUFF_SIZE];
int            decimal_point_precision = 3;
int            error;
bool           use_degree = true;
bool           use_float  = false;
typedef double float64_t;

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
    CALC_PI,
    CALC_SQRT,
    CALC_LPR,
    CALC_RPR,
    CALC_BSPACE,
    CALC_COM,
    KC_LMAO,
};
void write_buffer(void) {
    oled_write_P(PSTR("\nIN:\n"), false);
    oled_write((expressions_buffer), false);
    oled_write_P(PSTR("\nOUT:\n"), false);
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
    // oled_write_P(PSTR("\nPRS: "), false);
    // char precision_string[] = "";
    // sprintf(precision_string, "%d", decimal_point_precision);
    // oled_write(precision_string, false);
    // oled_write_P(PSTR(" "), false);
    // oled_write_P(PSTR("DEG"), use_degree);
    // oled_write_P(PSTR("RAD"), !use_degree);
    // oled_write_P(PSTR(" "), false);
    // oled_write_P(PSTR("FP"), use_float);
    // oled_write_P(PSTR(" "), false);
    // oled_write_P(PSTR("SCI"), !use_float);
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

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_90; }

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("BASE\n"), layer_state_is(_main));
    oled_write_P(PSTR("CALC\n"), layer_state_is(_calc));
}
void oled_task_user(void) { render_layer_state(); }
#endif

void write_char_to_buff(char c, bool oled_write) {
    if (input_count + 1 < EXPRESSIONS_BUFF_SIZE) {
        expressions_buffer[input_count]     = c;
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
        default:
            oled_clear();
            write_buffer();
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
    switch (keycode) {
        case KC_LMAO:
            if (record->event.pressed) {
                SEND_STRING("LMAO");
            }

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

        case CALC_COM:
            if (record->event.pressed) {
                write_char_to_buff(',', true);
            }
            break;

        case CALC_PI:
            if (record->event.pressed) {
                write_char_to_buff('p', false);
                write_char_to_buff('i', true);
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
                    for (i = input_count; i < strlen(expressions_buffer); i++) expressions_buffer[i] = expressions_buffer[i + 1];
#ifdef OLED_DRIVER_ENABLE
                    oled_clear();
                    write_buffer();
#endif
                }
            }
            break;
        case CALC_PRINT:
            if (record->event.pressed) {
                if (input_count > 0) {
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
                    if (error == 0) {
                        char output_result[EXPRESSIONS_BUFF_SIZE] = "";
                        if (use_float) {
                            sprintf(output_result, "%.*f", decimal_point_precision, result);
                        } else {
                            sprintf(output_result, "%.*g", decimal_point_precision, result);
                        }
                        send_string(output_result);
                        input_count           = 0;
                        expressions_buffer[0] = '\0';
#ifdef OLED_DRIVER_ENABLE
                        oled_clear();
                        write_buffer();
#endif
                    } else {
                        SEND_STRING("NaN");
                        input_count           = 0;
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
