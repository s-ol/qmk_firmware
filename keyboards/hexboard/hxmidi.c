#include QMK_KEYBOARD_H
#include <string.h>
#include "hxmidi.h"
#include "process_midi.h"
#include "oled.h"

uint8_t led2note(uint8_t i);

hxmidi_status_t hxmidi_status = {
#ifdef MIDI_ENABLE
    .octave = 36,
    .transpose = 20,
    .scale = SCALE_MAJOR,
#endif
    .flags = HXMIDI_FLAG_DIRTY,
};

#ifdef MIDI_ENABLE
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

void hxmidi_update_leds(void) {
    memset(hxmidi_status.mask, 0, sizeof(hxmidi_status.mask));

    for (uint8_t i = 0; i < 41; i++) {
        uint8_t note = (led2note(i) + hxmidi_status.transpose) % 12;
        uint8_t part = pgm_read_byte(&scale_masks[hxmidi_status.scale][note]);
        if (part == 0) {
            hxmidi_status.mask[i / 4] |= HXLED_OVERRIDE_INVERT << HXLED_SHIFT(i);
        } else if (note == 0) {
            hxmidi_status.mask[i / 4] |= HXLED_OVERRIDE_HSV << HXLED_SHIFT(i);
        }
    }


    oled_setyx(3, 5);
    oled_puts("oct: ");
    oled_putc('0' + hxmidi_status.octave / 12);

    oled_setx(55);
    oled_puts("scale: ");
    oled_puts_P(scale_names[hxmidi_status.scale]);

    hxmidi_status.flags = HXMIDI_FLAG_ENABLED | HXMIDI_FLAG_DIRTY;
    rgblight_set();
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
    }

    return process_record_user(keycode, record);
}
#endif

const uint8_t hxkb_led_override[] PROGMEM = {
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_DIM),
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_DIM, HXLED_OVERRIDE_DIM, HXLED_OVERRIDE_DIM, HXLED_OVERRIDE_NONE),
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE),
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_DIM, HXLED_OVERRIDE_DIM),
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_DIM, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE),
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE),
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_INVERT, HXLED_OVERRIDE_INVERT, HXLED_OVERRIDE_INVERT, HXLED_OVERRIDE_INVERT),
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE),
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_DIM, HXLED_OVERRIDE_INVERT, HXLED_OVERRIDE_INVERT),
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_INVERT, HXLED_OVERRIDE_INVERT, HXLED_OVERRIDE_INVERT, HXLED_OVERRIDE_DIM),
    HXLED_OVERRIDE_BYTE(HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE, HXLED_OVERRIDE_NONE),
};

void hxmidi_clear_leds(void) {
    memcpy_P(hxmidi_status.mask, hxkb_led_override, sizeof(hxkb_led_override));
    hxmidi_status.flags = HXMIDI_FLAG_ENABLED | HXMIDI_FLAG_DIRTY;
    rgblight_set();

    oled_setyx(3, 5);
    oled_puts_P(PSTR("                     "));
}


void rgblight_set_post_kb(LED_TYPE *led) {
    if (!(hxmidi_status.flags & HXMIDI_FLAG_ENABLED))
        return;

    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        switch (HXLED_LOOKUP(hxmidi_status.mask, i)) {
            case HXLED_OVERRIDE_HSV:
                sethsv(128, 255, 255, &led[i]);
                break;
            case HXLED_OVERRIDE_INVERT: {
                uint8_t r = led[i].r >> 1;
                led[i].r = led[i].g >> 1;
                led[i].g = led[i].b >> 1;
                led[i].b = r;
                break;
            }
            case HXLED_OVERRIDE_DIM:
                led[i].r = 0;
                led[i].g = 0;
                led[i].b = 0;
                break;
            default:
                break;
        }
    }
}
