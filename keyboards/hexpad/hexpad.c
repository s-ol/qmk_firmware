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
                 Q({ 32,55}), Q({ 48,55}),
           Q({ 24,42}), Q({ 40,42}), Q({ 56,42}),
    Q({ 16,28}), Q({ 32,28}), Q({ 48,28}), Q({ 64,28}),
           Q({ 24,14}), Q({ 40,14}), Q({ 56,14})
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
