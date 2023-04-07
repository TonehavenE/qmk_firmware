#include QMK_KEYBOARD_H
#include "combo.c"
#include "tapdance.c"

#define DEFAULT_CPI 1240
// layers
#define _COLEMAK 0
#define _NAV 1
#define _NUM 2
#define _SYM 3
#define NUM MO(_NUM)
#define NAV MO(_NAV)
#define SYM MO(_SYM)

// One shot keys
#define OS_SFT OSM(MOD_LSFT)
#define OS_CTL OSM(MOD_LCTL)
#define OS_ALT OSM(MOD_LALT)
#define OS_GUI OSM(MOD_LGUI)

// Shorthand
#define TAB_LEFT S(C(KC_TAB))
#define TAB_RIGHT C(KC_TAB)

#define RESET QK_BOOT

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK] = LAYOUT_split(
//        ┌───┬───┬───┬─────┬─────┬──────┐       ┌─────┬─────┬───┬───┬───┬─────┐
//        │ q │ w │ f │  p  │  g  │ ([{  │       │ )]} │  j  │ l │ u │ y │ "'" │
//        ├───┼───┼───┼─────┼─────┼──────┤       ├─────┼─────┼───┼───┼───┼─────┤
//        │ a │ r │ s │  t  │  d  │  ;   │       │  -  │  h  │ n │ e │ i │  o  │
//        ├───┼───┼───┼─────┼─────┼──────┘       └─────┼─────┼───┼───┼───┼─────┤
//        │ z │ x │ c │  v  │  b  │                    │  k  │ m │ , │ . │  /  │
//        └───┴───┴───┼─────┼─────┼──────┐             ├─────┼───┴───┴───┴─────┘
//                    │ NAV │ spc │ lsft │             │ NUM │
//                    └─────┴─────┴──────┘             └─────┘
      KC_Q , KC_W , KC_F , KC_P , KC_G   , QK_OBRC ,         QK_CBRC , KC_J , KC_L , KC_U    , KC_Y   , KC_QUOT    ,
      KC_A , KC_R , KC_S , KC_T , KC_D   , KC_SCLN ,         KC_MINS , KC_H , KC_N , KC_E    , KC_I   , KC_O       ,
      KC_Z , KC_X , KC_C , KC_V , KC_B   ,                             KC_K , KC_M , KC_COMM , KC_DOT , KC_SLSH    ,
                           NAV  , KC_SPC , KC_LSFT ,                   NUM
),

[_NAV] = LAYOUT_split(
//        ┌────────┬────────┬──────────┬───────────┬──────┬─────┐       ┌─────┬─────┬──────┬──────┬──────┬──────┐
//        │  tab   │        │          │           │ volu │     │       │     │ ins │ home │  up  │ end  │ bspc │
//        ├────────┼────────┼──────────┼───────────┼──────┼─────┤       ├─────┼─────┼──────┼──────┼──────┼──────┤
//        │ OS_SFT │ OS_CTL │  OS_ALT  │  OS_GUI   │ vold │     │       │     │     │ left │ down │ rght │ del  │
//        ├────────┼────────┼──────────┼───────────┼──────┼─────┘       └─────┼─────┼──────┼──────┼──────┼──────┤
//        │        │        │ TAB_LEFT │ TAB_RIGHT │      │                   │     │ pgdn │ pgup │      │ ent  │
//        └────────┴────────┴──────────┼───────────┼──────┼─────┐             ├─────┼──────┴──────┴──────┴──────┘
//                                     │           │      │     │             │ SYM │
//                                     └───────────┴──────┴─────┘             └─────┘
      KC_TAB  , _______ , _______  , _______   , KC_VOLU , _______ ,         _______ , KC_INSERT , KC_HOME , KC_UP   , KC_END   , KC_BSPC     ,
      OS_SFT  , OS_CTL  , OS_ALT   , OS_GUI    , KC_VOLD , _______ ,         _______ , _______   , KC_LEFT , KC_DOWN , KC_RIGHT , KC_DEL      ,
      _______ , _______ , TAB_LEFT , TAB_RIGHT , _______ ,                             _______   , KC_PGDN , KC_PGUP , _______  , KC_ENTER    ,
                                     _______   , _______ , _______ ,                   SYM
),

[_NUM] = LAYOUT_split(
//        ┌────────┬────────┬────────┬────────┬──────┬─────┐       ┌─────┬─────┬────────┬────────┬────────┬────────┐
//        │   1    │   2    │   3    │   4    │  5   │     │       │     │  6  │   7    │   8    │   9    │   0    │
//        ├────────┼────────┼────────┼────────┼──────┼─────┤       ├─────┼─────┼────────┼────────┼────────┼────────┤
//        │ OS_SFT │ OS_CTL │ OS_ALT │ OS_GUI │  f6  │     │       │     │ f12 │ OS_GUI │ OS_ALT │ OS_CTL │ OS_SFT │
//        ├────────┼────────┼────────┼────────┼──────┼─────┘       └─────┼─────┼────────┼────────┼────────┼────────┤
//        │   f1   │   f2   │   f3   │   f4   │  f5  │                   │ f11 │  f10   │   f9   │   f8   │   f7   │
//        └────────┴────────┴────────┼────────┼──────┼─────┐             ├─────┼────────┴────────┴────────┴────────┘
//                                   │  SYM   │ bspc │  0  │             │     │
//                                   └────────┴──────┴─────┘             └─────┘
      KC_1   , KC_2   , KC_3   , KC_4   , KC_5    , _______ ,         _______ , KC_6    , KC_7   , KC_8   , KC_9   , KC_0      ,
      OS_SFT , OS_CTL , OS_ALT , OS_GUI , KC_F6   , _______ ,         _______ , KC_F12  , OS_GUI , OS_ALT , OS_CTL , OS_SFT    ,
      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5   ,                             KC_F11  , KC_F10 , KC_F9  , KC_F8  , KC_F7     ,
                                 SYM    , KC_BSPC , KC_0    ,                   _______
),

[_SYM] = LAYOUT_split(
//        ┌─────┬───┬───┬─────┬─────┬──────┐       ┌──────┬──────┬────────┬────────┬────────┬────────┐
//        │ esc │ [ │ { │  (  │  ~  │ boot │       │ boot │  ^   │   )    │   }    │   ]    │   `    │
//        ├─────┼───┼───┼─────┼─────┼──────┤       ├──────┼──────┼────────┼────────┼────────┼────────┤
//        │  -  │ * │ = │  _  │  $  │ boot │       │ boot │ '--' │ OS_GUI │ OS_ALT │ OS_CTL │ OS_SFT │
//        ├─────┼───┼───┼─────┼─────┼──────┘       └──────┼──────┼────────┼────────┼────────┼────────┤
//        │  +  │ | │ @ │  /  │  %  │                     │      │  '\'   │   &    │   ?    │   !    │
//        └─────┴───┴───┼─────┼─────┼──────┐              ├──────┼────────┴────────┴────────┴────────┘
//                      │     │     │      │              │      │
//                      └─────┴─────┴──────┘              └──────┘
      KC_ESC  , KC_LBRC , KC_LCBR  , KC_LPRN , KC_TILDE  , RESET   ,         RESET , KC_CIRC , KC_RPRN , KC_RCBR , KC_RBRC , KC_GRAVE    ,
      KC_MINS , KC_ASTR , KC_EQUAL , KC_UNDS , KC_DOLLAR , RESET   ,         RESET , KC_HASH , OS_GUI  , OS_ALT  , OS_CTL  , OS_SFT      ,
      KC_PLUS , KC_PIPE , KC_AT    , KC_SLSH , KC_PERC   ,                           _______ , KC_BSLS , KC_AMPR , KC_QUES , KC_EXLM     ,
                                     _______ , _______   , _______ ,                 _______
)
};

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(DEFAULT_CPI);
    // Customise these values to desired behaviour
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    // debug_matrix = true;
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

// when I change to the raise layer, I want my CPI to get reduced
// by half. When I drop that layer, it needs to go back up.
layer_state_t layer_state_set_kb(layer_state_t state) {
    uint16_t current_cpi = pointing_device_get_cpi();
    switch (get_highest_layer(state)) {
        case _NAV:
            pointing_device_set_cpi(current_cpi / 4);
            break;
        case _COLEMAK:
            pointing_device_set_cpi(DEFAULT_CPI);
            break;
        default:
            break;
    }
    return state;
}
