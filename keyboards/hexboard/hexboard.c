#include "hexboard.h"
#include "i2c-bitbang.h"
#include "oled.h"

bool is_keyboard_left(void) {
     // Test pin SPLIT_HAND_PIN for High/Low, if high it's right hand
     // (this is the opposite of regular SPLIT_HAND_PIN)
     setPinInput(SPLIT_HAND_PIN);
     return !readPin(SPLIT_HAND_PIN);
}

void keyboard_post_init_kb(void) {
    debug_enable=true;

    i2c_init();
    oled_init();
    oled_clear(0);
    oled_putc(' ');

    oled_putc('H');
    wait_ms(30);
    oled_putc('e');
    wait_ms(30);
    oled_putc('l');
    wait_ms(30);
    oled_putc('l');
    wait_ms(30);
    oled_putc('o');
    wait_ms(30);
    oled_puts(" :)");

    keyboard_post_init_user();
}
