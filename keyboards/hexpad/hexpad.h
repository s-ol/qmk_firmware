#pragma once

#include "quantum.h"

/*
#define LAYOUT_hexpad( kNONE,   \
                                \
          k01, k05,             \
        k02, k06, k10,          \
      k03, k07, k11, k15,       \
        k08, k12, k16         ) \
                                \
  {                             \
    { k01, k05, kNONE, kNONE }, \
    { k02, k06, k10, kNONE   }, \
    { k03, k07, k11, k15     }, \
    { kNONE, k08, k12, k16   }, \
  }

#define LED_LAYOUT_hexpad( \
                           \
          k01, k05,        \
        k02, k06, k10,     \
      k03, k07, k11, k15,  \
        k08, k12, k16    ) \
                           \
  {                        \
    k01, k02, k03, k08,    \
    k07, k06, k05, k10,    \
    k11, k12, k16, k15,    \
  }

#define LED2_LAYOUT_hexpad(                                 \
                                                            \
                    k01x, k01y,   k05x, k05y,               \
             k02x, k02y,   k06x, k06y,   k10x, k10y,        \
      k03x, k03y,   k07x, k07y,   k11x, k11y,   k15x, k15y, \
             k08x, k08y,   k12x, k12y,   k16x, k16y       ) \
                                                            \
  {                                                         \
    { k01x, k01y }, { k02x, k02y }, { k03x, k03y },         \
   	{ k08x, k08y }, { k07x, k07y }, { k06x, k06y },         \
   	{ k05x, k05y }, { k10x, k10y }, { k11x, k11y },         \
    { k12x, k12y }, { k16x, k16y }, { k15x, k15y },         \
  }
*/

#define LAYOUT_hexpad( kNONE,          \
                                       \
          kF1, kF2,                    \
        kF3, kF4, kF5,                 \
      kG2, kG3, kG4, kG5,              \
        kG1, kH2, kH3                ) \
                                       \
  {                                    \
    { kF1, kF2, kF3, kF4, kF5 },       \
    { kG1, kG2, kG3, kG4, kG5 },       \
    { kNONE, kH2, kH3, kNONE, kNONE }, \
  }

#define LED_LAYOUT_hexpad(   \
                             \
          kA1, kA2,          \
        kB1, kB2, kB3,       \
      kC1, kC2, kC3, kC4,    \
        kD2, kD3, kD4      ) \
                             \
  {                          \
    kA1, kA2, kB1, kB2, kB3, \
    kC1, kC2, kC3, kC4,      \
    kD2, kD3, kD4,           \
  }

#define LED2_LAYOUT_hexpad(                             \
                                                        \
                kA1a, kA1b,   kA2a, kA2b,               \
         kB1a, kB1b,   kB2a, kB2b,   kB3a, kB3b,        \
  kC1a, kC1b,   kC2a, kC2b,   kC3a, kC3b,   kC4a, kC4b, \
         kD2a, kD2b,   kD3a, kD3b,   kD4a,  kD4b      ) \
                                                        \
  {                                                     \
    { kA1a, kA1b }, { kA2a, kA2b }, { kB1a, kB1b },     \
    { kB2a, kB2b }, { kB3a, kB3b }, { kC1a, kC1b },     \
   	{ kC2a, kC2b }, { kC3a, kC3b }, { kC4a, kC4b },     \
    { kD2a, kD2b }, { kD3a, kD3b }, { kD4a, kD4b },     \
  }
