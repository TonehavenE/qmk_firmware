#include "sensor.h"
/***************************
 * Trackball related defines
 **************************/
#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include "../../pmw3360/pmw3360.h"

uint8_t track_mode = 0;  // 0 Mousecursor; 1 arrowkeys/carret; 2 scrollwheel; 3 sound/brightness
#define cursor_mode 0
#define carret_mode 1
#define scroll_mode 2
#define sound_brightness_mode 3
uint8_t prev_track_mode  = 0;
bool    integration_mode = false;
int16_t cum_x            = 0;
int16_t cum_y            = 0;
int16_t sensor_x         = 0;
int16_t sensor_y         = 0;

// Thresholds help to move only horizontal or vertical. When accumulated distance reaches threshold, only move one discrete value in direction with bigger delta.
uint8_t  carret_threshold      = 60;   // higher means slower
uint16_t carret_threshold_inte = 400;  // in integration mode higher threshold
#define CRT_STEP 5

#define regular_smoothscroll_factor 8
bool     smooth_scroll         = true;
uint8_t  scroll_threshold      = 8 / regular_smoothscroll_factor;  // divide if started smooth
uint16_t scroll_threshold_inte = 1200 / regular_smoothscroll_factor;

uint16_t cursor_multiplier      = 130;  // adjust cursor speed
uint16_t cursor_multiplier_inte = 20;
#define CPI_STEP 10

int16_t cur_factor;

void on_mouse_button(uint8_t mouse_button, bool pressed) {
    report_mouse_t report = pointing_device_get_report();

    if (pressed)
        report.buttons |= mouse_button;
    else
        report.buttons &= ~mouse_button;
    pointing_device_set_report(report);
    pointing_device_send();
}

enum custom_keycodes {
    KC_INTE = SAFE_RANGE,
    KC_CPI_DOWN,
    KC_CPI_STD,
    KC_CPI_UP,
    KC_SMO_SC,
    KC_CURSORMODE,
    KC_SCROLLMODE,
    KC_CARRETMODE,
    KC_CRT_UP,
    KC_CRT_DOWN,
};

void pointing_device_init(void) {
    if (!is_keyboard_master()) return;
    pmw_init();
}

int max(int num1, int num2) { return (num1 > num2) ? num1 : num2; }
int min(int num1, int num2) { return (num1 > num2) ? num2 : num1; }

int8_t sign(int x) { return (x > 0) - (x < 0); }
int8_t CLAMP_HID(int value) { return value < -127 ? -127 : value > 127 ? 127 : value; }

void tap_code_fast(uint8_t code) {
    register_code(code);
    unregister_code(code);
}

void tap_tb(uint8_t keycode0, uint8_t keycode1, uint8_t keycode2, uint8_t keycode3) {
    if (abs(cum_x) + abs(cum_y) >= cur_factor) {
        if (abs(cum_x) > abs(cum_y)) {
            if (cum_x > 0) {
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
            if (cum_y > 0) {
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

void handle_pointing_device_modes(void) {
    report_mouse_t mouse_report = pointing_device_get_report();

    if (track_mode == cursor_mode) {
        if (integration_mode)
            cur_factor = cursor_multiplier_inte;
        else
            cur_factor = cursor_multiplier;
        mouse_report.x = CLAMP_HID(sensor_x * cur_factor / 100);
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
            tap_tb(KC_RIGHT, KC_LEFT, KC_NO, KC_NO);

        } else if (track_mode == scroll_mode) {
            if (integration_mode)
                cur_factor = scroll_threshold_inte;
            else
                cur_factor = scroll_threshold;
            if (abs(cum_x) + abs(cum_y) >= cur_factor) {
                if (abs(cum_x) > abs(cum_y)) {
                    mouse_report.h = sign(cum_x) * (abs(cum_x) + abs(cum_y)) / cur_factor;
                } else {
                    mouse_report.v = sign(cum_y) * (abs(cum_x) + abs(cum_y)) / cur_factor;
                }
                cum_x = 0;
                cum_y = 0;
            }
        } else {  // sound vol/brightness (3)
            cur_factor = carret_threshold;
            tap_tb(KC_BRIGHTNESS_UP, KC_BRIGHTNESS_DOWN, KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN);
        }
    }
    pointing_device_set_report(mouse_report);
    pointing_device_send();
}

void get_sensor_data(void) {
    if (!is_keyboard_master()) return;
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
    if (is_keyboard_master() && integration_mode) handle_pointing_device_modes();
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

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
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
            if (cursor_multiplier > CPI_STEP) cursor_multiplier = cursor_multiplier - CPI_STEP;
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
                    scroll_threshold      = scroll_threshold * regular_smoothscroll_factor;
                    scroll_threshold_inte = scroll_threshold_inte * regular_smoothscroll_factor;
                    smooth_scroll         = false;
                } else {
                    scroll_threshold      = scroll_threshold / regular_smoothscroll_factor;
                    scroll_threshold_inte = scroll_threshold_inte / regular_smoothscroll_factor;
                    smooth_scroll         = true;
                }
            }
        case KC_CRT_DOWN:
            if (carret_threshold > CRT_STEP) carret_threshold = carret_threshold - CRT_STEP;
            return false;

        case KC_CRT_UP:
            carret_threshold = carret_threshold + CRT_STEP;
            return false;
        default:
            return true;
    }
    return process_record_user(keycode, record);
};
