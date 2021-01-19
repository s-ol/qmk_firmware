#pragma once

#include "quantum.h"

#define LAYOUT(                     \
                                    \
          k01, k05,                 \
        k02, k06, k10,              \
      k03, k07, k11, k15,           \
        k08, k12, k16         )     \
                                    \
    {                               \
        { k01, k05, KC_NO, KC_NO }, \
        { k02, k06, k10, KC_NO   }, \
        { k03, k07, k11, k15     }, \
        { KC_NO, k08, k12, k16   }, \
    }

#define LED_LAYOUT(            \
                               \
          k01, k05,            \
        k02, k06, k10,         \
      k03, k07, k11, k15,      \
        k08, k12, k16    )     \
                               \
    {                          \
        k01, k02, k03, k08,    \
        k07, k06, k05, k10,    \
        k11, k12, k16, k15,    \
    }
