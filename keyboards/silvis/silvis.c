#include "silvis.h"

#ifdef RGB_MATRIX_ENABLE
/* clang-format off */
led_config_t g_led_config = {
    {
        // Key matrix to LED index
        { 5 , 4 , 3 , 2 , 1 , 0 ,   29, 30, 31, 32, 33, 34 },
        { 6 , 7 , 8 , 9 , 10, 11,   40, 39, 38, 37, 36, 35 },
        { 17, 16, 15, 14, 13, 12,   41, 42, 43, 44, 45, 46 },
        { 18, 19, 20, 21, 22, 23,   52, 51, 50, 49, 48, 47 },
        {      24, 25, 26, 27, 28, 53, 54, 55, 56, 57 },
    },
    {
        // Led index to physical position
        // { x, y } where x = 224 / 11 * COL_POSITION and y = 64 / 4 * ROW_POSITION
        {101,  0}, {81,  0}, {61,  0}, {40,   0}, {20,  0}, { 0, 0 },
        {0  , 16}, {20, 16}, {40, 16}, {60,  16}, {81, 16}, { 101, 16},
        {101, 32}, {81, 32}, {61, 32}, {40,  32}, {20, 32}, { 0, 32},
        {0  , 48}, {20, 48}, {40, 48}, {60,  48}, {81, 48}, {101, 48},
        {40 , 55}, {61, 53}, {91, 58}, {100, 62}, {112, 64},
        {122,  0}, {142, 0}, {163, 0}, {183, 0}, {203, 0}, {224, 0},
        {224, 16}, {203,16}, {183,16}, {163,16}, {142,16}, {122,16},
        {122, 32}, {142,32}, {163,32}, {183,32}, {203,32}, {224,32},
        {224, 48}, {203,48}, {183,48}, {163,48}, {142,48}, {122,48},
        {122, 64}, {130,62}, {135,58}, {163,53}, {183,55},
    },
    {
        // LED Index to Flag
        1, 4, 4, 4, 4, 4,   4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4,   4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 8, 4,   4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4,   4, 4, 4, 4, 4, 1,
            1, 1, 1, 1, 1, 8, 1, 1, 1, 1,
    } };
/* clang-format on */
#endif
