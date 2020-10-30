#pragma once

#include "quantum.h"

/* -------- LEFT HAND --------     -------- RIGHT HAND ------- */
#define LAYOUT_hexpad(                                          \
                                                                \
      A2, A3, A4, A5, A6,             F1, F2, F3, F4, F5,       \
    B1, B2, B3, B4, B5, B6,             G2, G3, G4, G5, G1,     \
      C1, C2, C3, C4, C5,             H2, H3, H4, H5, H1,       \
    D6, D1, D2, D3, D4, D5,             I3, I4, I5, I1, I2,     \
      C6,                                             J2      ) \
                                                                \
  {                                              \
    { KC_NO, A2, A3, A4, A5, A6 },                \
    { B1, B2, B3, B4, B5, B6 },                   \
    { C1, C2, C3, C4, C5, C6 },                   \
    { D1, D2, D3, D4, D5, D6 },                   \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { F1, F2, F3, F4, F5, KC_NO },                \
    { G1, G2, G3, G4, G5, KC_NO },                \
    { H1, H2, H3, H4, H5, KC_NO },                \
    { I1, I2, I3, I4, I5, KC_NO },                \
    { KC_NO, J2, KC_NO, KC_NO, KC_NO, KC_NO },    \
  }
