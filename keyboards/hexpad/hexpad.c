#include "hexpad.h"

#ifdef RGB_MATRIX_ENABLE
#    define Q(...) __VA_ARGS__

led_config_t g_led_config = {
  // indices
  LAYOUT_hexpad(
         0,  6,
       1,  5,  7,
     2,  4,  8, 11,
       3,  9, 10
  ),
  // phys position
  LED_LAYOUT_hexpad(
                 Q({48,110}), Q({80,110}),
           Q({ 32,83}), Q({ 64,83}), Q({ 96,83}),
    Q({ 16,55}), Q({ 48,55}), Q({ 80,55}), Q({112,55}),
           Q({ 32,28}), Q({ 64,28}), Q({ 96,28})
  ),
  // flags
  LED_LAYOUT_hexpad(
         4,  4,
       4,  4,  4,
     4,  4,  4,  4,
       4,  4,  4
  ),
};
#    undef Q
#endif
