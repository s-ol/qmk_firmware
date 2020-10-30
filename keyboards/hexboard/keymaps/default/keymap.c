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
        MI_Cs_2, MI_Eb_2, MI_F_2 , MI_G_2 , MI_A_1 ,             MI_B_2 , MI_Cs_3, MI_Eb_3, MI_F_3 , MI_G_3,     \
    MI_Fs_1, MI_Ab_1, MI_Bb_1, MI_C_2 , MI_D_2 , MI_E_2 ,            MI_Fs_2, MI_Ab_2, MI_Bb_2, MI_C_3 , MI_OCTU, \
        MI_Cs_1, MI_Eb_1, MI_F_1 , MI_G_1 , MI_A_1 ,             MI_B_1 , MI_Cs_2, MI_Eb_2, MI_F_2 , MI_G_2,     \
    MI_Fs  , MI_Ab  , MI_Bb  , MI_C_1 , MI_D_1 , MI_E_1 ,            MI_Fs_1, MI_Ab_1, MI_Bb_1, MI_C_2 , MI_OCTD, \
        TG(_CL),                                                                                     TG(_CL)      \
  ),
#endif
  [_CL] = LAYOUT_hexpad(
        _______, _______, _______, _______, DF(_AF),             DF(_AF), _______, RESET, RGB_TOG, RGB_MOD,     \
    _______, _______, _______, _______, _______, _______,            _______, _______, RGB_HUD, RGB_HUI, _______, \
        _______, _______, _______, _______, _______,             _______, _______, _______, RGB_SAD, RGB_SAI,       \
    _______, _______, _______, _______, _______, _______,            _______, _______, RGB_VAD, RGB_VAI, _______, \
        DF(_WH),                                                                                     DF(_WH)      \
  ),
};

#ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM led_layer_af[] = RGBLIGHT_LAYER_SEGMENTS(
  // left
  //{ 0, 3, HSV_SPRINGGREEN}, {5, 4, HSV_SPRINGGREEN}, {11, 3, HSV_SPRINGGREEN}, {16, 2, HSV_SPRINGGREEN},
  //{14, 2, HSV_PURPLE}, {19, 2, HSV_PURPLE},
  { 4, 1, HSV_ORANGE},
  // right
  //{25, 3, HSV_SPRINGGREEN}, {29, 4, HSV_SPRINGGREEN}, {35, 3, HSV_SPRINGGREEN}, {41, 2, HSV_SPRINGGREEN},
  //{33, 2, HSV_PURPLE}, {38, 2, HSV_PURPLE},
  {23, 1, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM led_layer_wh[] = RGBLIGHT_LAYER_SEGMENTS(
  {23, 32, HSV_SPRINGGREEN}, {33, 9, HSV_SPRINGGREEN},
  {32, 1, HSV_PURPLE}, {42, 1, HSV_PURPLE},
  {22, 1, HSV_ORANGE}, {43, 1, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM led_layer_cl[] = RGBLIGHT_LAYER_SEGMENTS(
  // RGB control
  {26, 2, HSV_PURPLE},
  {30, 2, HSV_PURPLE},
  {36, 2, HSV_PURPLE},
  {40, 2, HSV_PURPLE},
  // DF control
  { 4, 1, HSV_ORANGE},
  {22, 1, HSV_ORANGE},
  {23, 1, HSV_ORANGE},
  {43, 1, HSV_ORANGE},
  // RESET
  {25, 1, HSV_RED}
);

const rgblight_segment_t* const PROGMEM led_layers[] = RGBLIGHT_LAYERS_LIST(
  [_AF] = led_layer_af,
  [_WH] = led_layer_wh,
  [_CL] = led_layer_cl
);

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(_AF, layer_state_cmp(state, _AF));
  rgblight_set_layer_state(_WH, layer_state_cmp(state, _WH));
  rgblight_set_layer_state(_CL, layer_state_cmp(state, _CL));
  return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(_AF, layer_state_cmp(state, _AF));
  rgblight_set_layer_state(_WH, layer_state_cmp(state, _WH));
  return state;
}

void keyboard_post_init_user(void) {
  rgblight_layers = led_layers;
  rgblight_set_layer_state(_AF, true);
}
#endif
