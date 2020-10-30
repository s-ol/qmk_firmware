#include "hexpad.h"

led_config_t g_led_config = {
  // indices
  LAYOUT_hexpad( NO_LED,
        0,  1,
      2,  3,  4,
    5,  6,  7,  8,
      9, 10, 11
  ),
  // phys position
	LED2_LAYOUT_hexpad(
  	/*
            	   64, 80 ,  96, 80 ,
           48, 56 ,  80, 56 ,  122, 56 ,
     32, 32 ,  64, 32 ,  96, 32 ,  128, 32 ,
           48,  8 ,  80,  8 ,  122, 8 
    */
    32, 80,  64, 80,  96, 80, 128, 80, 160, 80,
      48, 56,  80, 56, 112, 56, 144, 56, 176, 56,
    32, 32,  64, 32
  ),
  // flags
  LED_LAYOUT_hexpad(
        4,  4,
      4,  4,  4,
    4,  4,  4,  4,
      4,  4,  4
  )
};
