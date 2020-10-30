#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_hexpad( KC_NO,
     RGB_MOD, KC_B, KC_E   , KC_T   , RESET   ,
        KC_S   , KC_C   , KC_V   , KC_LGUI,  KC_G ,
     KC_LCTL, KC_BSPC
  ),
};

