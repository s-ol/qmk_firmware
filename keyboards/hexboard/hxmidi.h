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

typedef struct {
    uint8_t octave;
    uint8_t base;
    uint8_t transpose;
    hxmidi_scale_t scale;
    uint8_t flags;
    uint8_t mask[6];
} hxmidi_status_t;

extern hxmidi_status_t hxmidi_status;

void hxmidi_clear_leds(void);
void hxmidi_update_leds(void);
