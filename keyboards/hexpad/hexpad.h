#pragma once

#include "quantum.h"

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
