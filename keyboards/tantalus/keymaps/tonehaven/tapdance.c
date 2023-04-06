#include "keycodes.h"
#include "quantum.h"
enum { TD_OPEN_BRC = 0, TD_CLOSE_BRC };

tap_dance_action_t tap_dance_actions[] = {
    // tap once for parentheses, twice for square brackets
    [TD_OPEN_BRC]  = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_LBRC),
    [TD_CLOSE_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_RPRN, KC_RBRC)};

#define QK_OBRC TD(TD_OPEN_BRC)
#define QK_CBRC TD(TD_CLOSE_BRC)
