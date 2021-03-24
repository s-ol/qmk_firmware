#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x732D
#define PRODUCT_ID      0x2C62
#define DEVICE_VER      0x0001
#define MANUFACTURER    s-ol
#define PRODUCT         0x2C.board
#define DESCRIPTION     Hybrid Keyboard / MIDI controller

#define DF_IS_ALSO_TO

#define TAPPING_TERM 150
#define TAPPING_TOGGLE 2
#define COMBO_TERM 75
#define COMBO_COUNT 7
#define COMBO_ALLOW_ACTION_KEYS
#define COMBO_KEY_BUFFER_LENGTH 2

/* key matrix  */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6
#define DIODE_DIRECTION ROW2COL
#define MATRIX_ROW_PINS       { B0, B1, B2, B3, NO_PIN }
#define MATRIX_COL_PINS       { D5, D4, D3, D2, C2, B4 }
#define MATRIX_ROW_PINS_RIGHT { C7, D6, D5, D4, D3 }
#define MATRIX_COL_PINS_RIGHT { B0, B7, B6, B5, B4, NO_PIN }

/* Split options */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D0
#define SERIAL_USE_MULTI_TRANSACTION
#define SPLIT_HAND_PIN C5
#define SPLIT_USB_DETECT
#define MIDI_MODE_PIN D1

#define HXMIDI_ENABLE
/* MIDI */
#ifdef MIDI_ENABLE
#   define MIDI_BASIC
#   define MIDI_ENABLE_STRICT 1
#   define MIDI_INPUT_QUEUE_LENGTH 32
#   define NO_MUSIC_MODE
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* ws2812 RGB LED */
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   define RGB_DI_PIN C6
#   define RGBW
#   define RGBLED_NUM 44
#   define RGBLED_SPLIT { 23, 21 }
#   define DRIVER_LED_TOTAL 44
#   define DRIVER_LED_SPLIT { 23, 21 }
#   ifdef RGBLIGHT_ENABLE
#       define RGBLIGHT_EFFECT_BREATHING
#       define RGBLIGHT_EFFECT_RAINBOW_MOOD
#       define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#       define RGBLIGHT_LIMIT_VAL 200
#       define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#       define RGBLIGHT_LAYERS
#   endif
#endif

/* -------- LEFT HAND --------     -------- RIGHT HAND ------- */
#define LED_LAYOUT_pointy(                                      \
                                                                \
      A2, A3, A4, A5, A6,             F1, F2, F3, F4, F5,       \
    B1, B2, B3, B4, B5, B6,             G2, G3, G4, G5, G1,     \
      C1, C2, C3, C4, C5,             H2, H3, H4, H5, H1,       \
    D6, D1, D2, D3, D4, D5,             I3, I4, I5, I1, I2,     \
      C6,                                             J2      ) \
                                                                \
  {                         \
    A2, A3, A4, A5, A6,     \
    B1, B2, B3, B4, B5, B6, \
    C1, C2, C3, C4, C5,     \
    D6, D1, D2, D3, D4, D5, \
    C6,                     \
    F1, F2, F3, F4, F5,     \
    G2, G3, G4, G5, G1,     \
    H2, H3, H4, H5, H1,     \
    I3, I4, I5, I1, I2,     \
    J2,                     \
  }

#define RGBLIGHT_LED_MAP LED_LAYOUT_pointy(                        \
       0,  1,  2,  3,  4,              5,  6,  7,  8,  9,   \
    10, 11, 12, 13, 14, 15,             16, 17, 18, 19, 20, \
      21, 22, 23, 24, 25,             26, 27, 28, 29, 30,   \
    31, 32, 33, 34, 35, 36,             37, 38, 39, 40, 41, \
      42,                                             43    )

/*
 non-mapped layout:
       0,  1,  2,  3,  4,             23, 24, 25, 26, 27,
     5,  6,  7,  8,  9, 10,             28, 29, 30, 31, 32,
      11, 12, 13, 14, 15,             33, 34, 35, 36, 37,
    16, 17, 18, 19, 20, 21,             38, 39, 40, 41, 42,
      22,                                             43
*/
