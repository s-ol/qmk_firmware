#include QMK_KEYBOARD_H
// #include "split_util.h"

#define _AF 0
#ifdef MIDI_ENABLE
#		define _WH 1
#else
#		define _WH _AF
#endif
#define _CL 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_AF] = LAYOUT_hexpad( _______,
        KC_D   , KC_F   , KC_K   , _______, TG(_CL),             TG(_CL), _______, KC_J   , KC_U   , KC_R   ,     \
    KC_W   , KC_E   , KC_T   , KC_G   , _______, _______,            _______, KC_B   , KC_N   , KC_I   , KC_L   , \
        KC_S   , KC_C   , KC_V   , KC_LGUI, KC_LSFT,             KC_RSFT, KC_RGUI, KC_Y   , KC_P   , KC_O   ,     \
    KC_A   , KC_X   , KC_LCTL, KC_BSPC, KC_SPC , _______,            KC_SPC , KC_BSPC, KC_RCTL, KC_M   , KC_H   , \
        KC_Z   ,                                                                                     KC_Q         \
  ),
#ifdef MIDI_ENABLE
  [_WH] = LAYOUT_hexpad( _______,
        MI_Cs_2, MI_Eb_2, MI_F_2 , MI_G_2 , MI_A_2 ,             MI_B_2 , MI_Cs_3, MI_Eb_3, MI_F_3 , MI_G_3,     \
    MI_Fs_1, MI_Ab_1, MI_Bb_1, MI_C_2 , MI_D_2 , MI_E_2 ,            MI_Fs_2, MI_Ab_2, MI_Bb_2, MI_C_3 , MI_OCTU, \
        MI_Cs_1, MI_Eb_1, MI_F_1 , MI_G_1 , MI_A_1 ,             MI_B_1 , MI_Cs_2, MI_Eb_2, MI_F_2 , MI_G_2,     \
    MI_Fs  , MI_Ab  , MI_Bb  , MI_C_1 , MI_D_1 , MI_E_1 ,            MI_Fs_1, MI_Ab_1, MI_Bb_1, MI_C_2 , MI_OCTD, \
        TG(_CL),                                                                                     TG(_CL)      \
  ),
#endif
  [_CL] = LAYOUT_hexpad( _______,
          RESET, RGB_TOG, RGB_MOD, _______, DF(_AF),             DF(_AF), _______, RESET, RGB_TOG, RGB_MOD,     \
    _______, RGB_HUD, RGB_HUI, _______, _______, _______,            _______, _______, RGB_HUD, RGB_HUI, _______, \
        RGB_SAD, RGB_SAI, _______,  _______, _______,             _______, _______, _______, RGB_SAD, RGB_SAI,       \
    _______, RGB_VAD, RGB_VAI, _______, _______, _______,            _______, _______, RGB_VAD, RGB_VAI, _______, \
        DF(_WH),                                                                                     DF(_WH)      \
  ),
};

#ifdef RGBLIGHT_ENABLE

#    ifdef RGBLIGHT_LED_MAP
const rgblight_segment_t PROGMEM led_layer_af[] = RGBLIGHT_LAYER_SEGMENTS(
  { 4, 2, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM led_layer_wh[] = RGBLIGHT_LAYER_SEGMENTS(
  {20, 1, HSV_RED}, {41, 1, HSV_RED}, {42, 2, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM led_layer_cl[] = RGBLIGHT_LAYER_SEGMENTS(
  // RGB control
  { 1, 2, HSV_PURPLE},
  {11, 2, HSV_PURPLE},
  {21, 2, HSV_PURPLE},
  {32, 2, HSV_PURPLE},
  { 8, 2, HSV_PURPLE},
  {18, 2, HSV_PURPLE},
  {29, 2, HSV_PURPLE},
  {39, 2, HSV_PURPLE},
  // DF
  { 4, 2, HSV_ORANGE},
  {42, 2, HSV_ORANGE},
  // RESET
  { 0, 1, HSV_RED},
  { 7, 1, HSV_RED}
);
#    else
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
  // {23, 32, HSV_SPRINGGREEN}, {33, 9, HSV_SPRINGGREEN},
  {32, 1, HSV_PURPLE}, {42, 1, HSV_PURPLE},
  {22, 1, HSV_ORANGE}, {43, 1, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM led_layer_cl[] = RGBLIGHT_LAYER_SEGMENTS(
  // RGB control
  { 1, 2, HSV_PURPLE},
  { 6, 2, HSV_PURPLE},
  {11, 2, HSV_PURPLE},
  {17, 2, HSV_PURPLE},
  {26, 2, HSV_PURPLE},
  {30, 2, HSV_PURPLE},
  {36, 2, HSV_PURPLE},
  {40, 2, HSV_PURPLE},
  // DF
  { 4, 1, HSV_ORANGE},
  {22, 1, HSV_ORANGE},
  {23, 1, HSV_ORANGE},
  {43, 1, HSV_ORANGE},
  // RESET
  { 0, 1, HSV_RED},
  {25, 1, HSV_RED}
);
#    endif

const rgblight_segment_t* const PROGMEM led_layers[] = RGBLIGHT_LAYERS_LIST(
  [_AF] = led_layer_af,
#ifdef MIDI_ENABLE
  [_WH] = led_layer_wh,
#endif
  [_CL] = led_layer_cl
);

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(_AF, layer_state_cmp(state, _AF));
#ifdef MIDI_ENABLE
  rgblight_set_layer_state(_WH, layer_state_cmp(state, _WH));
#endif
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
  rgblight_set_layer_state(_AF, true);
}
#endif

#ifdef RGB_MATRIX_ENABLE
#		define Q(...) __VA_ARGS__

led_config_t g_led_config = {
  // indices
  LAYOUT_hexpad( NO_LED,
       0,  1,  2,  3,  4,             23, 24, 25, 26, 27,
     5,  6,  7,  8,  9, 10,             28, 29, 30, 31, 32,
      11, 12, 13, 14, 15,             33, 34, 35, 36, 37,
    16, 17, 18, 19, 20, 21,             38, 39, 40, 41, 42,
      22,                                             43
  ),
  // phys position
  LED_LAYOUT_hexpad(
           Q({ 24,69}), Q({ 40,69}), Q({ 56,69}), Q({ 72,69}), Q({ 88,69}),             Q({104,69}), Q({120,69}), Q({136,69}), Q({152,69}), Q({168,69}),
    Q({ 16,55}), Q({ 32,55}), Q({ 48,55}), Q({ 64,55}), Q({ 55,55}), Q({ 96,55}),             Q({112,55}), Q({128,55}), Q({144,55}), Q({160,55}), Q({176,55}),
           Q({ 24,42}), Q({ 40,42}), Q({ 56,42}), Q({ 72,42}), Q({ 88,42}),             Q({104,42}), Q({120,42}), Q({136,42}), Q({152,42}), Q({168,42}),
    Q({ 16,28}), Q({ 32,28}), Q({ 48,28}), Q({ 64,28}), Q({ 28,28}), Q({ 96,28}),             Q({112,28}), Q({128,28}), Q({144,28}), Q({160,28}), Q({176,28}),
           Q({ 24,14}),                                             																																				Q({168,14})
  ),
  // flags
  LED_LAYOUT_hexpad(
       4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
     4,  4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
     4,  4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
       4,                                              4
  ),
};
#		undef Q
#endif

#ifdef MIDI_ENABLE_TRASH
uint8_t scale_base;
uint8_t scale_mask[44 / 8];

// always safe: +21 / -21 (one octave up/down vertically)

uint8_t scales[] PROGMEM = {
    // major
    3, ?, 4

    // minor
    2, ?, 3, ?, 3

    // blues
    1, ?, 3, ?, 1, ?, 2
};


void set_base(uint8_t base) {
    if (base >= 21) {
        block_shift = 21;
        base -= 21;
    } else {
        block_shift = 0;
    }
}

void setled_scale(uint8_t o) {
    // set o
    if (base + o < 8)
        // set o+8

}

void set_scale_major(void) {
    // + + + + - -
    //  O + + - - -

    setled_scale(1);
    setled_scale(2);
    setled_scale(12-6);
    setled_scale(12-5);
    setled_scale(12-4);
    setled_scale(12-3);
}

void set_scale_minor(void) {
    // + + O + - -
    //  + + + - - -

    // + + - - - +
    //  O + - - + +

    setled_scale(1);
    setled_scale(4);
    setled_scale(5);
    setled_scale(12-6);
    setled_scale(12-5);
    setled_scale(12-1);
}

void set_scale_blues(void) {
    // + - + O + -
    //  - + + + - -

    // + + - - - +
    //  O + - + - +

    setled_scale(1);
    setled_scale(3);
    setled_scale(5);
    setled_scale(12-6);
    setled_scale(12-5);
    setled_scale(12-1);
}

void set_scale_penta(void) {
    // + + + - - -
    //  O + - - -

    setled_scale(1);
    setled_scale(12-6);
    setled_scale(12-5);
    setled_scale(12-4);
}

void rgblight_set_post_kb(LED_TYPE *led, rgblight_ranges_t ranges) {
    scale_base = 34;
    set_scale_major();

    uint8_t I = ranges.clipping_start_pos + ranges.clipping_num_leds;
    for (uint8_t i = ranges.clipping_start_pos; i < I; i++) {
        if (i == scale_base)
            sethsv(128, 255, 255, &led[i]);
        else if (!(scale_mask[i / 8] & (1 << (i%8))))
            sethsv(0,0,0, &led[i]);
    }
}
#endif
