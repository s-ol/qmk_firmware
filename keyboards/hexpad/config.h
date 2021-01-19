#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x73sd
#define PRODUCT_ID 0x0C70
#define DEVICE_VER 0x0001
#define MANUFACTURER s-ol
#define PRODUCT 0xC.pad
#define DESCRIPTION 12-key macropad

/* key matrix  */
#define MATRIX_ROWS 4
#define MATRIX_COLS 4
#define DIODE_DIRECTION ROW2COL
#define MATRIX_ROW_PINS { B7, B6, B5, B4 }
#define MATRIX_COL_PINS { D4, D3, D2, D1 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* ws2812 RGB LED */
#define RGB_DI_PIN C7
#define DRIVER_LED_TOTAL 12
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_KEYPRESSES
