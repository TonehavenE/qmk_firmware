#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _GAME 1
#define _RAISE 2
#define _FUNC 3
#define _VIM 4

#define RAISE MO(_RAISE)
#define LT_FUNC LT(_FUNC, KC_ENT)

enum my_keycodes {
    vim_h = SAFE_RANGE,
    vim_j,
    vim_k,
    vim_l,
    vim_w,
    vim_b,
    vim_d,
    vim_e,
    vim_$,
    vim_0,
    vim_y,
    vim_c,
    vim_s,
    vim_x,
    vim_p,
    vim_ins,
    vim_ext,
    vim_ent
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK] = LAYOUT_ortho_5x12(
        KC_GESC, KC_1,    KC_2,    KC_3 ,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_EQL,
        KC_LALT, KC_Q,    KC_W,    KC_F ,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,   KC_SCLN,
        KC_LSFT, KC_A,    KC_R,    KC_S ,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,      KC_RSFT,
        KC_LCTL, KC_Z,    KC_X,    KC_C ,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_MINS,
                 KC_LPRN, KC_RPRN, RAISE,    KC_SPC,  KC_TAB,  KC_LGUI, LT_FUNC, KC_BSPC, KC_LBRC, KC_RBRC
    ),
    [_GAME] = LAYOUT_ortho_5x12(
        KC_ESC , KC_5,    KC_1,    KC_2,    KC_3,    KC_4,    KC_6,    KC_7,    KC_8,    KC_9,   KC_0   , KC_EQL,
        KC_TAB , KC_T,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_J,    KC_L,    KC_U,    KC_Y,   KC_QUOT, KC_SCLN,
        KC_LSFT, KC_G,    KC_A,    KC_S,    KC_D,    KC_F,    KC_H,    KC_N,    KC_E,    KC_I,   KC_O   , KC_RSFT,
        KC_LCTL, KC_B,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_K,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS,
                 KC_F3,   KC_F12,  KC_LALT, KC_SPC,  MO(_FUNC), _______, _______, _______, TG(_GAME), TG(_GAME)
    ),
    [_RAISE] = LAYOUT_ortho_5x12(
        KC_GRAVE, _______,    _______,  KC_0   ,  _______,  vim_ent,        _______,  KC_DEL ,  _______,  _______  ,  _______  , _______,
        _______ , _______,    KC_7   ,  KC_8   ,  KC_9   ,  _______,        _______,  KC_HOME,  KC_UP  ,  KC_END   ,  _______  , _______,
        _______ , KC_0   ,    KC_4   ,  KC_5   ,  KC_6   ,  _______,        _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT ,  _______  , _______,
        _______ , _______,    KC_1   ,  KC_2   ,  KC_3   ,  _______,        _______,  _______,  _______,  _______  ,  _______  , _______,
                  _______,    _______,  _______,  _______,  _______,        KC_BSLS,  _______,  KC_DEL ,  TG(_GAME),  TG(_GAME)
    ),
    [_FUNC] = LAYOUT_ortho_5x12(
        _______ , _______,    KC_F10 ,  KC_F11 ,  KC_F12 ,  _______,        RGB_TOG,  RGB_MOD,  RGB_RMOD,  _______,  _______, RESET  ,
        _______ , _______,    KC_F7  ,  KC_F8  ,  KC_F9  ,  _______,        _______,  RGB_HUI,  RGB_HUD,  _______,  _______, _______,
        _______ , KC_LGUI,    KC_F4  ,  KC_F5  ,  KC_F6  ,  _______,        _______,  RGB_SAI,  RGB_SAD,  KC_RALT,  KC_LGUI, _______,
        _______ , _______,    KC_F1  ,  KC_F2  ,  KC_F3  ,  _______,        _______,  RGB_VAI,  RGB_VAD,  _______,  _______, _______,
                  _______,    _______,  _______,  _______,  _______,        _______,  _______,  _______,  TG(_GAME),  TG(_GAME)
    ),
    [_VIM] = LAYOUT_ortho_5x12(
        vim_ext, _______, _______, _______, vim_$  , _______,                   _______, _______, _______, _______, vim_0  , _______,
        _______, vim_q  , vim_w  , _______, vim_p  , _______,                   vim_j  , vim_l  , _______, vim_y  , _______, _______,
        _______, _______, _______, vim_s  , _______, vim_d  ,                   vim_h  , _______, vim_e  , vim_ins, _______, _______,
        _______, _______, vim_x  , vim_c  , _______, vim_b  ,                   vim_k  , _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______
            )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case vim_ext:
            if (record->event.pressed) {
                // do something on press 
            } else {
                // do something on release 
            }
            return false;
        case vim_ent:
            if (record->event.pressed) {

            } else {

            }
            return false;

        case vim_ins:
            if (record->event.pressed) {

            } else {

            }
            return false;
        case vim_h:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LEFT));
            } else {

            }
            return false;
        case vim_j:
            if (record->event.pressed) {
               SEND_STRING(SS_TAP(X_DOWN));
            } else {

            }
            return false;
        case vim_k:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_UP));
            } else {

            }
            return false;
        case vim_l:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_RIGHT));
            } else {

            }
            return false;
        case vim_w:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
            } else {

            }
            return false;
        case vim_b:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
            } else {

            }
            return false;
        case vim_d:
            // This should be a tap dance on d twice
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)) SS_LCTL("c") SS_TAP(X_BSPC));
            } else {
            }
            return false;
        case vim_e:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
            } else {

            }
            return false;
        case vim_0:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_HOME));
            } else {
            }
            return false;
        case vim_y:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_RIGHT)) SS_LCTL("c") SS_LSFT(SS_TAP(X_LEFT)));
            } else {

            }
            return false;
        case vim_c:
            if (record->event.pressed) {
                SEND_STRING("c");
            } else {
            }
            return false;
        case vim_s:
            if (record->event.pressed) {
                SEND_STRING("s");
            } else {
            }
            return false;
        case vim_x:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_DEL));
            } else {
            }
            return false;
        case vim_p: 
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("v"));
            } else {

            }
            return false;
     	}
  return true;
};
