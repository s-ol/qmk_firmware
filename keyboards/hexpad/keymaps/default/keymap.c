#include QMK_KEYBOARD_H
#include "split_util.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_hexpad(
        KC_D   , KC_F   , KC_K   , _______, _______,             RESET  , RGB_MOD, KC_J   , KC_U   , KC_R   ,     \
    KC_W   , KC_E   , KC_T   , KC_G   , _______, _______,            _______, KC_B   , KC_N   , KC_I   , KC_L   , \
        KC_S   , KC_C   , KC_V   , KC_LGUI, KC_LSFT,             KC_RSFT, KC_RGUI, KC_Y   , KC_P   , KC_O   ,     \
    KC_A   , KC_X   , KC_LCTL, KC_BSPC, KC_SPC , _______,            KC_SPC , KC_BSPC, KC_RCTL, KC_M   , KC_H   , \
        KC_Z   ,                                                                                     KC_Q         \
  ),
};

void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=false;
  debug_keyboard=false;
  _delay_ms(1500);

  print("hello there!\n");
  dprintf("is left? %d\n", isLeftHand);
  dprintf("is master? %d\n", is_keyboard_master());
  print("done debugging.!\n");
}

void led_set_user(uint8_t usb_led) {

}
