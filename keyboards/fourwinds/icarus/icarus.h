#pragma once

#include "quantum.h"

// Any changes to the layout names and/or definitions must also be made to info.json

#define LAYOUT_ortho_4x5( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13, \
    K20, K21, K22, K23, \
    K30, K31, K32, K33, \
    K40, K41, K42, K43  \
) { \
    { K00,   K01,   K02,   K03 }, \
    { K10,   K11,   K12,   K13 }, \
    { K20,   K21,   K22,   K23 }, \
    { K30,   K31,   K32,   K33 }, \
    { K40,   K41,   K42,   K43 }  \
}
