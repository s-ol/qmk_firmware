#include QMK_KEYBOARD_H
#include <string.h>
#include "hxmidi.h"
#include "process_midi.h"
#include "oled.h"

uint8_t led2note(uint8_t i);

hxmidi_status_t hxmidi_status = {
    .octave = 36,
    .base = 38,
    .transpose = 20,
    .scale = SCALE_MAJOR,
    .flags = HXMIDI_FLAG_DIRTY,
};

const uint8_t scale_masks[][12] PROGMEM = {
    /* major:
        08  10 [00]
       01  03 [05  07  09  11]
                [00  02  04] 06
    */
    [SCALE_MAJOR] = { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 },

    /* minor:
        [08  10  00]
       01 [03  05  07] 09  11
                [00  02] 04  06
    */
    [SCALE_MINOR] = { 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0 },

    /* penta:
         08  10 [00]
       01  03 [05  07  09] 11
                [00  02] 04  06
    */
    [SCALE_PENTA] = { 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0 },

    /* blues:
         08 [10  00]
       01 [03  05  07] 09  11
                [00] 02  04 [06]
    */
    [SCALE_BLUES] = { 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0 },
};

const char scale_names[][6] PROGMEM = {
    [SCALE_MAJOR] = "major",
    [SCALE_MINOR] = "minor",
    [SCALE_PENTA] = "penta",
    [SCALE_BLUES] = "blues",
};

uint8_t led2note(uint8_t i) {
    switch (i) {
        default:
            return 255;

        case 31 ... 40:
            return 2 * (i-31) + 6*1;

        case 21 ... 30:
            return 2 * (i-21) + 6*2 + 1;

        case 10 ... 19:
            return 2 * (i-10) + 6*3;

        case 0 ... 9:
            return 2 * (i- 0) + 6*4 + 1;
    }
}

void hxmidi_clear_leds(void) {
    hxmidi_status.flags &= ~HXMIDI_FLAG_ENABLED;

    oled_setyx(3, 5);
    oled_puts_P(PSTR("                    "));
}

void hxmidi_update_leds(void) {
    memset(hxmidi_status.mask, 0, sizeof(hxmidi_status.mask));

    for (uint8_t i = 0; i < 41; i++) {
        uint8_t note = led2note(i) + hxmidi_status.transpose;
        uint8_t part = pgm_read_byte(&scale_masks[hxmidi_status.scale][note % 12]);
        if (part == 0) {
            hxmidi_status.mask[i / 8] |= (1 << (i%8));
        }
    }

    oled_setyx(3, 5);
    oled_puts("oct: ");
    oled_putc('0' + hxmidi_status.octave / 12);

    oled_setx(55);
    oled_puts("scale: ");
    oled_puts_P(scale_names[hxmidi_status.scale]);

    hxmidi_status.flags = HXMIDI_FLAG_ENABLED | HXMIDI_FLAG_DIRTY;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HX_N ... HX_N_END: {
            uint8_t i = keycode - HX_N;
            uint8_t note = led2note(i) + hxmidi_status.octave;

            if (note > 127)
                return false;

            if (record->event.pressed)
                process_midi_basic_noteon(note);
            else
                process_midi_basic_noteoff(note);

            return false;
        }
        case HX_B ... HX_B_END:
            if (record->event.pressed) {
                hxmidi_status.base = keycode - HX_B;
                hxmidi_status.transpose = 12 - (led2note(keycode - HX_B) % 12);
                hxmidi_update_leds();
            }
            return false;
        case HX_OCTU:
            if (record->event.pressed && hxmidi_status.octave <= 103) {
                hxmidi_status.octave += 12;
                hxmidi_update_leds();
            }
            return false;
        case HX_OCTD:
            if (record->event.pressed && hxmidi_status.octave >= 12) {
                hxmidi_status.octave -= 12;
                hxmidi_update_leds();
            }
            return false;
        case HX_SCLN:
            if (record->event.pressed) {
                hxmidi_status.scale = (hxmidi_status.scale + 1) % SCALE_MAX;
                hxmidi_update_leds();
            }
            return false;
        case HX_SCLP:
            if (record->event.pressed) {
                hxmidi_status.scale = (hxmidi_status.scale - 1 + SCALE_MAX) % SCALE_MAX;
                hxmidi_update_leds();
            }
            return false;
        default:
            return true;
    }
}

void rgblight_set_post_kb(LED_TYPE *led) {
    if (!(hxmidi_status.flags & HXMIDI_FLAG_ENABLED))
        return;

    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        if (i == hxmidi_status.base) {
            sethsv(128, 255, 255, &led[i]);
        } else if ((hxmidi_status.mask[i / 8] & (1 << (i%8)))) {
            uint8_t r = led[i].r >> 1;
            led[i].r = led[i].g >> 1;
            led[i].g = led[i].b >> 1;
            led[i].b = r;
        }
    }
}
