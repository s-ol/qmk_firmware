#include QMK_KEYBOARD_H
#include "split_util.h"

#define _AF 0
#define _WH 1
#define _CL 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_AF] = LAYOUT_hexpad(
        KC_D   , KC_F   , KC_K   , _______, TG(_CL),             TG(_CL), _______, KC_J   , KC_U   , KC_R   ,     \
    KC_W   , KC_E   , KC_T   , KC_G   , _______, _______,            _______, KC_B   , KC_N   , KC_I   , KC_L   , \
        KC_S   , KC_C   , KC_V   , KC_LGUI, KC_LSFT,             KC_RSFT, KC_RGUI, KC_Y   , KC_P   , KC_O   ,     \
    KC_A   , KC_X   , KC_LCTL, KC_BSPC, KC_SPC , _______,            KC_SPC , KC_BSPC, KC_RCTL, KC_M   , KC_H   , \
        KC_Z   ,                                                                                     KC_Q         \
  ),
#ifdef MIDI_ENABLE
  [_WH] = LAYOUT_hexpad(
        MI_Gb_3, MI_Ab_3, MI_Bb_3, MI_C_3 , MI_D_3 ,             MI_E_3 , MI_Fs_3, MI_Gs_3, MI_As_3, _______,     \
    MI_B_2 , MI_Db_3, MI_Eb_3, MI_F_3 , MI_G_3 , MI_A_3 ,            MI_B_3 , MI_Fs_3, MI_Gs_3, MI_As_3, _______, \
        MI_Gb_1, MI_Ab_1, MI_Bb_1, MI_C_2 , MI_D_2 ,             MI_E_2 , MI_Fs_2, MI_Gs_2, MI_As_2, MI_OCTU,     \
    MI_B   , MI_Db_1, MI_Eb_1, MI_F_2 , MI_G_2 , MI_A_2 ,            MI_B_2 , MI_Fs_2, MI_Gs_2, MI_As_2, MI_OCTD, \
        TG(_CL),                                                                                     TG(_CL)      \
  ),
#endif
  [_CL] = LAYOUT_hexpad(
        _______, _______, _______, _______, _______,             _______, _______, RGB_TOG, RGB_MOD, RGB_HUI,     \
    _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______,             DF(_AF), DF(_WH), _______, _______, RESET,       \
    _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, \
        _______,                                                                                     _______      \
  ),
};

const rgblight_segment_t PROGMEM led_layer_af[] = RGBLIGHT_LAYER_SEGMENTS(
#ifdef PER_FINGER
  // r thumb
  {26, 2, HSV_SPRINGGREEN}, {37, 2, HSV_SPRINGGREEN},
  // r index
  { 7, 2, HSV_RED}, {17, 2, HSV_RED}, {28, 1, HSV_RED},
  // r middle
  { 9, 1, HSV_MAGENTA}, {19, 1, HSV_MAGENTA}, {29, 1, HSV_MAGENTA},
  // r ring
  {20, 1, HSV_PURPLE}, {30, 1, HSV_PURPLE}, {40, 1, HSV_PURPLE},
  // r pinky
  {41, 1, HSV_TURQUOISE}, {43, 1, HSV_TURQUOISE},
#else
  // left
  { 0, 3, HSV_SPRINGGREEN}, {10, 4, HSV_SPRINGGREEN}, {21, 6, HSV_SPRINGGREEN},
  {31, 2, HSV_SPRINGGREEN}, {34, 2, HSV_SPRINGGREEN}, {42, 1, HSV_SPRINGGREEN},
  // right
  { 7, 3, HSV_SPRINGGREEN}, {17, 4, HSV_SPRINGGREEN}, {26, 6, HSV_SPRINGGREEN},
  {37, 2, HSV_SPRINGGREEN}, {40, 2, HSV_SPRINGGREEN}, {43, 1, HSV_SPRINGGREEN},
#endif
  // ctl
  {4, 2, HSV_ORANGE}
);

#ifdef MIDI_ENABLE
const rgblight_segment_t PROGMEM led_layer_wh[] = RGBLIGHT_LAYER_SEGMENTS(
  { 9, 1, HSV_SPRINGGREEN}, {20, 1, HSV_SPRINGGREEN},
  {30, 1, HSV_SPRINGGREEN}, {41, 1, HSV_SPRINGGREEN},
  // ctl
  {42, 2, HSV_ORANGE}
);
#endif

const rgblight_segment_t PROGMEM led_layer_cl[] = RGBLIGHT_LAYER_SEGMENTS(
  // RGB control
  { 8, 3, HSV_PURPLE},
  // DF control
  {26, 2, HSV_TEAL},
  // RESET
  {30, 1, HSV_RED}
);

const rgblight_segment_t* const PROGMEM led_layers[] = RGBLIGHT_LAYERS_LIST(
  [_AF] = led_layer_af,
#ifdef MIDI_ENABLE
  [_WH] = led_layer_wh,
#endif
  [_CL] = led_layer_cl
);

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(_CL, layer_state_cmp(state, _CL));
  return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(_AF, layer_state_cmp(state, _AF));
#ifdef MIDI_ENABLE
  rgblight_set_layer_state(_WH, layer_state_cmp(state, _WH));
#endif
  return state;
}

void keyboard_post_init_user(void) {
  rgblight_layers = led_layers;
}
