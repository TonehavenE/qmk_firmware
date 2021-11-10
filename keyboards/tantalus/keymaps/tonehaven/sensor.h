/***************************
 * Trackball related defines
 **************************/
#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include "../../pmw3360/pmw3360.h"

/***************************
 * Mouse pressed
 **************************/
void on_mouse_button(uint8_t mouse_button, bool pressed);

/***************************
 * Trackball handling
 **************************/
void pointing_device_init(void);

int max(int num1, int num2);
int min(int num1, int num2);

int8_t sign(int x);
int8_t CLAMP_HID(int value);

void tap_code_fast(uint8_t code);
void tap_tb(uint8_t keycode0, uint8_t keycode1, uint8_t keycode2, uint8_t keycode3);
void handle_pointing_device_modes(void);
void get_sensor_data(void);
void pointing_device_task(void);

bool process_record_kb(uint16_t keycode, keyrecord_t *record);