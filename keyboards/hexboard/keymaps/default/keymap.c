#include QMK_KEYBOARD_H
#include "oled.h"
#include "hxmidi.h"

#define _AF 0x0
#define _NS 0x1
#define _FS 0x2
#define _MV 0x3
#define _CL 0xF
#ifdef MIDI_ENABLE
#    define HXM 0x8
#    define HXC 0x9
#    define HX_LAYER_MASK (~(3UL << HXM))
#else
#    define HXM _AF
#endif

#define THMB_L1 LT(_NS, KC_SPC)
#define THMB_L2 KC_BSPC
#define THMB_L3 KC_DEL
#define THMB_L4 LALT_T(KC_CAPS)
#define THMB_Lm KC_LGUI
#define THMB_Lx LT(_MV, KC_TAB)
#define THMB_R1 LT(_FS, KC_ESC)
#define THMB_R2 LSFT_T(KC_ENT)
#define THMB_R3 RCTL_T(KC_INS)
#define THMB_Rm KC_RGUI
#define THMB_R4 KC_RALT

// const uint16_t PROGMEM combo_L1m[] = { THMB_L1, THMB_Lm, COMBO_END };
// const uint16_t PROGMEM combo_L13[] = { THMB_L1, THMB_L3, COMBO_END };
const uint16_t PROGMEM combo_L1x[] = { THMB_L1, THMB_Lx, COMBO_END };
const uint16_t PROGMEM combo_Lx3[] = { THMB_L1, THMB_Lx, COMBO_END };
const uint16_t PROGMEM combo_R1m[] = { THMB_R1, THMB_Rm, COMBO_END };
const uint16_t PROGMEM combo_L12[] = { THMB_L1, THMB_L2, COMBO_END };
const uint16_t PROGMEM combo_R12[] = { THMB_R1, THMB_R2, COMBO_END };
const uint16_t PROGMEM combo_R13[] = { THMB_R1, THMB_R3, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo_Lx3, KC_DEL),  // makes pressing DEL easier
    COMBO(combo_R1m, KC_RGUI), // makes pressing GUI easier
    COMBO(combo_L12, KC_HOME),
    COMBO(combo_L1x, KC_LGUI),
    COMBO(combo_R12, KC_END),
    COMBO(combo_R13, C_S_T(KC_INS)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_AF] = LAYOUT_pointy(
        KC_X   , KC_F   , KC_K   , _______, TG(_CL),             TG(_CL), _______, KC_J   , KC_U   , KC_P   ,
    KC_W   , KC_E   , KC_T   , KC_G   , _______, TG(_MV),            _______, KC_B   , KC_N   , KC_I   , KC_Y   ,
        KC_S   , KC_C   , KC_D   , THMB_Lm, THMB_L3,             THMB_R3, THMB_Rm, KC_L   , KC_R   , KC_O   ,
    KC_A   , KC_V   , KC_LALT, THMB_L2, THMB_L1, THMB_Lx,            THMB_R1, THMB_R2, KC_RALT, KC_M   , KC_H   ,
        KC_Z   ,                                                                                     KC_Q
  ),
  [_NS] = LAYOUT_pointy(
        KC_3   , KC_4   , KC_5   , _______, _______,             _______, _______, KC_6   , KC_7   , KC_8   ,
    KC_2   , KC_LBRC, KC_LPRN, KC_MINS, _______, _______,            _______, KC_UNDS, KC_RPRN, KC_RBRC, KC_9   ,
        KC_LCBR, KC_COMM, KC_DOT , _______, _______,             _______, _______, KC_COLN, KC_SCLN, KC_RCBR,
    KC_1   , KC_QUOT, _______, _______, _______, _______,            _______, _______, _______, KC_DQUO, KC_0   ,
        KC_LABK,                                                                                     KC_RABK
  ),
  [_FS] = LAYOUT_pointy(
        KC_F3  , KC_F4  , KC_F5  , KC_F11 , _______,             _______, KC_F12 , KC_F6  , KC_F7  , KC_F8  ,
    KC_F2  , KC_EQL , KC_ASTR, KC_TILD, _______, _______,            _______, KC_CIRC, KC_GRV , KC_PLUS, KC_F9  ,
        KC_SLSH, KC_DLR , KC_HASH, _______, _______,             _______, _______, KC_AT  , KC_PIPE, KC_BSLS,
    KC_F1  , KC_EXLM, _______, _______, _______, _______,            _______, _______, _______, KC_QUES, KC_F10 ,
        KC_AMPR,                                                                                     KC_PERC
  ),
  [_MV] = LAYOUT_pointy(
        KC_2   , KC_3   , KC_F   , _______, _______,             _______, _______, KC_VOLU, KC_MPRV, KC_MPLY,
    KC_1   , KC_W   , KC_D   , KC_E   , _______, _______,            _______, KC_VOLD, KC_LEFT, KC_UP  , KC_MNXT,
        KC_A   , KC_S   , KC_R   , _______, _______,             _______, _______, KC_PGUP, KC_DOWN, KC_RGHT,
    KC_TAB , KC_X   , KC_C   , KC_LSFT, KC_SPC , KC_LCTL,            _______, _______, _______, KC_PGDN, _______,
        KC_Z   ,                                                                                     _______
  ),
#ifdef MIDI_ENABLE
  [HXM] = LAYOUT_pointy(
        HX_N+ 0, HX_N+ 1, HX_N+ 2, HX_N+ 3, HX_N+ 4,             HX_N+ 5, HX_N+ 6, HX_N+ 7, HX_N+ 8, HX_N+ 9,
    HX_N+10, HX_N+11, HX_N+12, HX_N+13, HX_N+14, HX_N+15,            HX_N+16, HX_N+17, HX_N+18, HX_N+19, HX_OCTU,
        HX_N+21, HX_N+22, HX_N+23, HX_N+24, HX_N+25,             HX_N+26, HX_N+27, HX_N+28, HX_N+29, HX_N+30,
    HX_N+31, HX_N+32, HX_N+33, HX_N+34, HX_N+35, HX_N+36,            HX_N+37, HX_N+38, HX_N+39, HX_N+40, HX_OCTD,
        TG(_CL),                                                                                     MO(HXC)
  ),
  [HXC] = LAYOUT_pointy(
        HX_B+ 0, HX_B+ 1, HX_B+ 2, HX_B+ 3, HX_B+ 4,             RESET  , HX_B+ 6, HX_B+ 7, HX_B+ 8, HX_B+ 9,
    HX_B+10, HX_B+11, HX_B+12, HX_B+13, HX_B+14, HX_B+15,            HX_B+16, HX_B+17, HX_B+18, HX_B+19, HX_SCLN,
        HX_B+21, HX_B+22, HX_B+23, HX_B+24, HX_B+25,             HX_B+26, HX_B+27, HX_B+28, HX_B+29, HX_B+30,
    HX_B+31, HX_B+32, HX_B+33, HX_B+34, HX_B+35, HX_B+36,            HX_B+37, HX_B+38, HX_B+39, HX_B+40, HX_SCLP,
        _______,                                                                                     _______
  ),
#endif
  [_CL] = LAYOUT_pointy(
          RESET, RGB_TOG, RGB_MOD, _______, DF(_AF),             DF(_AF), _______,   RESET, RGB_TOG, RGB_MOD,
    _______, RGB_HUD, RGB_HUI, _______, _______, _______,            _______, _______, RGB_HUD, RGB_HUI, _______,
        RGB_SAD, RGB_SAI, _______,  _______, _______,            _______, _______, _______, RGB_SAD, RGB_SAI,
    _______, RGB_VAD, RGB_VAI, _______, _______, _______,            _______, _______, RGB_VAD, RGB_VAI, _______,
        DF(HXM),                                                                                      DF(HXM)
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
  led_layer_af,
  led_layer_wh,
  led_layer_cl
);

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(0, layer_state_cmp(state, _AF));
  rgblight_set_layer_state(2, layer_state_cmp(state, _CL));

#ifdef MIDI_ENABLE
  rgblight_set_layer_state(1, layer_state_cmp(state, HXM));

  if (layer_state_cmp(state, HXM))
      hxmidi_update_leds();
  else
      hxmidi_clear_leds();
#else
  hxmidi_clear_leds();
#endif

  oled_setyx(0, 6*16);
  if (layer_state_cmp(state, _CL))
    oled_puts(" CTRL");
#ifdef MIDI_ENABLE
  else if (layer_state_cmp(state, HXM))
    oled_puts("WK/HY");
#endif
  else if (layer_state_cmp(state, _MV))
    oled_puts(" WASD");
  else if (layer_state_cmp(state, _FS))
    oled_puts(" FNSM");
  else if (layer_state_cmp(state, _NS))
    oled_puts(" NMSM");
  else
    oled_puts(" TYPE");

  return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
  rgblight_set_layer_state(0, layer_state_cmp(state, _AF));
#ifdef MIDI_ENABLE
  rgblight_set_layer_state(1, layer_state_cmp(state, HXM));
#endif

  return state;
}

void keyboard_post_init_user(void) {
  rgblight_layers = led_layers;
  rgblight_set_layer_state(_AF, true);
}
#endif

#ifdef RGB_MATRIX_ENABLE
#    define Q(...) __VA_ARGS__

led_config_t g_led_config = {
  // indices
  LAYOUT_pointy(
       0,  1,  2,  3,  4,             23, 24, 25, 26, 27,
     5,  6,  7,  8,  9, 10,             28, 29, 30, 31, 32,
      11, 12, 13, 14, 15,             33, 34, 35, 36, 37,
    16, 17, 18, 19, 20, 21,             38, 39, 40, 41, 42,
      22,                                             43
  ),
  // phys position
  LED_LAYOUT_pointy(
           Q({ 24,69}), Q({ 40,69}), Q({ 56,69}), Q({ 72,69}), Q({ 88,69}),             Q({104,69}), Q({120,69}), Q({136,69}), Q({152,69}), Q({168,69}),
    Q({ 16,55}), Q({ 32,55}), Q({ 48,55}), Q({ 64,55}), Q({ 55,55}), Q({ 96,55}),             Q({112,55}), Q({128,55}), Q({144,55}), Q({160,55}), Q({176,55}),
           Q({ 24,42}), Q({ 40,42}), Q({ 56,42}), Q({ 72,42}), Q({ 88,42}),             Q({104,42}), Q({120,42}), Q({136,42}), Q({152,42}), Q({168,42}),
    Q({ 16,28}), Q({ 32,28}), Q({ 48,28}), Q({ 64,28}), Q({ 28,28}), Q({ 96,28}),             Q({112,28}), Q({128,28}), Q({144,28}), Q({160,28}), Q({176,28}),
           Q({ 24,14}),                                                                                                                     Q({168,14})
  ),
  // flags
  LED_LAYOUT_pointy(
       4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
     4,  4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
       4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
     4,  4,  4,  4,  4,  4,              4,  4,  4,  4,  4,
       4,                                              4
  ),
};
#    undef Q
#endif


