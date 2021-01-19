#pragma once

#include "quantum.h"

/* -------- LEFT HAND --------     -------- RIGHT HAND ------- */
#define LAYOUT_pointy(                                          \
                                                                \
      A2, A3, A4, A5, A6,             F1, F2, F3, F4, F5,       \
    B1, B2, B3, B4, B5, B6,             G2, G3, G4, G5, G1,     \
      C1, C2, C3, C4, C5,             H2, H3, H4, H5, H1,       \
    D6, D1, D2, D3, D4, D5,             I3, I4, I5, I1, I2,     \
      C6,                                             J2      ) \
                                                                \
  {                                                             \
    { KC_NO, A2, A3, A4, A5, A6 },                              \
    { B1, B2, B3, B4, B5, B6 },                                 \
    { C1, C2, C3, C4, C5, C6 },                                 \
    { D1, D2, D3, D4, D5, D6 },                                 \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },               \
    { F1, F2, F3, F4, F5, KC_NO },                              \
    { G1, G2, G3, G4, G5, KC_NO },                              \
    { H1, H2, H3, H4, H5, KC_NO },                              \
    { I1, I2, I3, I4, I5, KC_NO },                              \
    { KC_NO, J2, KC_NO, KC_NO, KC_NO, KC_NO },                  \
  }

#define LAYOUT_flat(                                            \
            A2,                                    F5,          \
        B1,     A3,                            F4,     G1,      \
            B2,     A4,                    F3,     G5,          \
        C1,     B3,     A5,            F2,     G4,     H1,      \
    D6,     C2,     B4,     A6,    F1,     G3,     H5,     I2,  \
        D1,     C3,     B5,            G2,     H4,     I1,      \
    C6,     D2,     C4,     B6,            H3,     I5,     J2,  \
                D3,     C5,            H2,     I4,              \
                    D4,                    I3,                  \
                        D5                                    ) \
                                                                \
  {                                                             \
    { KC_NO, A2, A3, A4, A5, A6 },                              \
    { B1, B2, B3, B4, B5, B6 },                                 \
    { C1, C2, C3, C4, C5, C6 },                                 \
    { D1, D2, D3, D4, D5, D6 },                                 \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },               \
    { F1, F2, F3, F4, F5, KC_NO },                              \
    { G1, G2, G3, G4, G5, KC_NO },                              \
    { H1, H2, H3, H4, H5, KC_NO },                              \
    { I1, I2, I3, I4, I5, KC_NO },                              \
    { KC_NO, J2, KC_NO, KC_NO, KC_NO, KC_NO },                  \
  }

enum extra_keycodes {
    HX_N = SAFE_RANGE, // note
    HX_N_END = HX_N+40,

    HX_B, // scale base
    HX_B_END = HX_B+40,

    HX_OCTU,
    HX_OCTD,
    HX_SCLN,
    HX_SCLP,
};
