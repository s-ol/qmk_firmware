#include QMK_KEYBOARD_H
#include "oled.h"

#define _AF 0
#define _SB 1
#define _NM 2
#define _MV 3
#ifdef HXMIDI_ENABLE
#   include "hxmidi.h"

#   define HXM (_MV + 1)
#   define HXC (HXM + 1)
#   define _CL (HXC + 1)

#   define HX_LAYER_MASK (~(3UL << HXM))
#else
#   define HXM _AF
#   define _CL (_AF + 1)
#endif

#define HX_SPC      LT(_SB, KC_SPC)
#define HX_BSPC     LT(_NM, KC_BSPC)
#define HX_LSFT     LT(_NM, KC_LSFT)
#define HX_RSFT     LT(_SB, KC_RSFT)
#define HX_TAB      LT(_MV, KC_TAB)
#define HX_ESC      MT(MOD_LALT, KC_ESC)
#define HX_CAPS     MT(MOD_RCTL, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_AF] = LAYOUT_hexboard(
        KC_D   , KC_F   , KC_K   , _______, TG(_CL),             TG(_CL), _______, KC_J   , KC_U   , KC_R   ,     \
    KC_W   , KC_E   , KC_T   , KC_G   , _______, _______,            _______, KC_B   , KC_N   , KC_I   , KC_L   , \
        KC_S   , KC_C   , KC_V   , HX_TAB , HX_LSFT,             HX_RSFT, KC_ENT , KC_Y   , KC_P   , KC_O   ,     \
    KC_A   , KC_X   , _______, KC_LGUI, HX_SPC , HX_ESC ,            HX_BSPC, HX_CAPS, _______, KC_M   , KC_H   , \
        KC_Z   ,                                                                                     KC_Q         \
  ),
  [_SB] = LAYOUT_hexboard(
        KC_LCBR, KC_RCBR, _______, _______, _______,             _______, _______, _______, KC_SLSH, KC_BSLS,     \
    _______, KC_LPRN, KC_RPRN, _______, _______, _______,            _______, _______, KC_COMM, KC_DOT , KC_EQL , \
        KC_GRV , KC_LBRC, KC_RBRC, _______, _______,             _______, _______, KC_QUOT, KC_SCLN, KC_MINS,     \
    _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, \
        _______,                                                                                     _______      \
  ),
  [_MV] = LAYOUT_hexboard(
        KC_PGDN, KC_PGUP, _______, _______, _______,             _______, _______, _______, KC_HOME, KC_END ,     \
    KC_DEL , KC_VOLU, KC_VOLD, _______, _______, _______,            _______, _______, KC_LEFT, KC_UP  , KC_INS , \
        _______, KC_MNXT, KC_MPRV, _______, _______,             _______, _______, _______, KC_DOWN, KC_RGHT,     \
    _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, \
        _______,                                                                                     _______      \
  ),
  [_NM] = LAYOUT_hexboard(
        KC_3   , KC_4   , KC_5   , _______, _______,             _______, _______, KC_6   , KC_7   , KC_8   ,     \
    KC_2   , KC_F1  , KC_F2  , KC_F3  , KC_PSCR, _______,            _______, KC_F4  , KC_F5  , KC_F6  , KC_9   , \
        KC_F7  , KC_F8  , KC_F9  , _______, _______,             _______, _______, KC_F10 , KC_F11 , KC_F12 ,     \
    KC_1   , KC_F1  , KC_F4  , _______, _______, _______,            _______, _______, _______, _______, KC_0   , \
        _______,                                                                                     _______      \
  ),
#ifdef MIDI_ENABLE
  [HXM] = LAYOUT_hexboard(
        HX_N+ 0, HX_N+ 1, HX_N+ 2, HX_N+ 3, HX_N+ 4,             HX_N+ 5, HX_N+ 6, HX_N+ 7, HX_N+ 8, HX_N+ 9,     \
    HX_N+10, HX_N+11, HX_N+12, HX_N+13, HX_N+14, HX_N+15,            HX_N+16, HX_N+17, HX_N+18, HX_N+19, HX_OCTU, \
        HX_N+21, HX_N+22, HX_N+23, HX_N+24, HX_N+25,             HX_N+26, HX_N+27, HX_N+28, HX_N+29, HX_N+30,     \
    HX_N+31, HX_N+32, HX_N+33, HX_N+34, HX_N+35, HX_N+36,            HX_N+37, HX_N+38, HX_N+39, HX_N+40, HX_OCTD, \
        TG(_CL),                                                                                     MO(HXC)      \
  ),
  [HXC] = LAYOUT_hexboard(
        HX_B+ 0, HX_B+ 1, HX_B+ 2, HX_B+ 3, HX_B+ 4,             RESET  , HX_B+ 6, HX_B+ 7, HX_B+ 8, HX_B+ 9,     \
    HX_B+10, HX_B+11, HX_B+12, HX_B+13, HX_B+14, HX_B+15,            HX_B+16, HX_B+17, HX_B+18, HX_B+19, HX_SCLN, \
        HX_B+21, HX_B+22, HX_B+23, HX_B+24, HX_B+25,             HX_B+26, HX_B+27, HX_B+28, HX_B+29, HX_B+30,     \
    HX_B+31, HX_B+32, HX_B+33, HX_B+34, HX_B+35, HX_B+36,            HX_B+37, HX_B+38, HX_B+39, HX_B+40, HX_SCLP, \
        _______,                                                                                     _______      \
  ),
#endif
  [_CL] = LAYOUT_hexboard(
          RESET, RGB_TOG, RGB_MOD, _______, DF(_AF),             DF(_AF), _______,   RESET, RGB_TOG, RGB_MOD,     \
    _______, RGB_HUD, RGB_HUI, _______, _______, _______,            _______, _______, RGB_HUD, RGB_HUI, _______, \
        RGB_SAD, RGB_SAI, _______,  _______, _______,            _______, _______, _______, RGB_SAD, RGB_SAI,     \
    _______, RGB_VAD, RGB_VAI, _______, _______, _______,            _______, _______, RGB_VAD, RGB_VAI, _______, \
        DF(HXM),                                                                                      DF(HXM)     \
  ),
};

#ifdef RGBLIGHT_ENABLE

#    ifdef RGBLIGHT_LED_MAP
const rgblight_segment_t PROGMEM led_layer_af[] = RGBLIGHT_LAYER_SEGMENTS(
  { 4, 2, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM led_layer_wh[] = RGBLIGHT_LAYER_SEGMENTS(
  {20, 1, HSV_RED}, {41, 1, HSV_RED}, {42, 1, HSV_ORANGE}, {43, 1, HSV_RED}
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
  {32, 1, HSV_PURPLE}, {42, 2, HSV_PURPLE},
  {22, 1, HSV_ORANGE},
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
#ifdef HXMIDI_ENABLE
  [HXM] = led_layer_wh,
#endif
  [_CL] = led_layer_cl
);

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(_AF, layer_state_cmp(state, _AF));
  rgblight_set_layer_state(_CL, layer_state_cmp(state, _CL));

#ifdef HXMIDI_ENABLE
  rgblight_set_layer_state(HXM, layer_state_cmp(state, HXM));

  if (layer_state_cmp(state, HXM))
      hxmidi_update_leds();
  else
      hxmidi_clear_leds();
#endif

  oled_setyx(0, 6*16);
  if (layer_state_cmp(state, _CL))
    oled_puts(" CTRL");
  else if (layer_state_cmp(state, HXM))
    oled_puts("WK/HY");
  else
    oled_puts(" TYPE");

  return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(_AF, layer_state_cmp(state, _AF));
#ifdef HXMIDI_ENABLE
  rgblight_set_layer_state(HXM, layer_state_cmp(state, HXM));
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
  LAYOUT_hexboard(
       0,  1,  2,  3,  4,             23, 24, 25, 26, 27,
     5,  6,  7,  8,  9, 10,             28, 29, 30, 31, 32,
      11, 12, 13, 14, 15,             33, 34, 35, 36, 37,
    16, 17, 18, 19, 20, 21,             38, 39, 40, 41, 42,
      22,                                             43
  ),
  // phys position
  LED_LAYOUT_hexboard(
           Q({ 24,69}), Q({ 40,69}), Q({ 56,69}), Q({ 72,69}), Q({ 88,69}),             Q({104,69}), Q({120,69}), Q({136,69}), Q({152,69}), Q({168,69}),
    Q({ 16,55}), Q({ 32,55}), Q({ 48,55}), Q({ 64,55}), Q({ 55,55}), Q({ 96,55}),             Q({112,55}), Q({128,55}), Q({144,55}), Q({160,55}), Q({176,55}),
           Q({ 24,42}), Q({ 40,42}), Q({ 56,42}), Q({ 72,42}), Q({ 88,42}),             Q({104,42}), Q({120,42}), Q({136,42}), Q({152,42}), Q({168,42}),
    Q({ 16,28}), Q({ 32,28}), Q({ 48,28}), Q({ 64,28}), Q({ 28,28}), Q({ 96,28}),             Q({112,28}), Q({128,28}), Q({144,28}), Q({160,28}), Q({176,28}),
           Q({ 24,14}),                                             																																				Q({168,14})
  ),
  // flags
  LED_LAYOUT_hexboard(
       4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
     4,  4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
     4,  4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
       4,                                              4
  ),
};
#		undef Q
#endif


