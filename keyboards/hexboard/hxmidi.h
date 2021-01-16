#pragma once

typedef enum {
    SCALE_MAJOR,
    SCALE_MINOR,
    SCALE_PENTA,
    SCALE_BLUES,
    SCALE_MAX
} hxmidi_scale_t;

#define HXMIDI_FLAG_DIRTY   1 << 1
#define HXMIDI_FLAG_ENABLED 1 << 2

enum HXLED_OVERRIDE {
    HXLED_OVERRIDE_NONE = 0,
    HXLED_OVERRIDE_DIM = 1,
    HXLED_OVERRIDE_INVERT = 2,
    HXLED_OVERRIDE_HSV = 3,
};

#define HXLED_SHIFT(i) ((i % 4)*2)
#define HXLED_LOOKUP(mask, i) ((mask[i / 4] >> HXLED_SHIFT(i)) & 0b11)
#define HXLED_OVERRIDE_BYTE(a, b, c, d) (a | (b << 2) | (c << 4) | (d << 6))

typedef struct {
    uint8_t octave;
    uint8_t transpose;
    hxmidi_scale_t scale;
    uint8_t flags;
    uint8_t mask[11];
} hxmidi_status_t;

extern hxmidi_status_t hxmidi_status;

void hxmidi_clear_leds(void);
void hxmidi_update_leds(void);
