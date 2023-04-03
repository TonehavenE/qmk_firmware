#pragma once

#ifdef CONSOLE_ENABLE
#    define POINTING_DEVICE_DEBUG
#endif
/* Trackball Settings */
#define PMW33XX_CS_PIN B0
#define POINTING_DEVICE_INVERT_X
#define ROTATIONAL_TRANSFORM_ANGLE -10
/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 10

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define POLLING true
