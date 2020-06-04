/*
Copyright 2020 Sol Bekic <s+qmk@s-ol.nu>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "i2ckb.h"
#include "keyboard.h"
#include "host.h"
#include "timer.h"
#include "uart.h"
#include "debug.h"
#include "suspend.h"
#include "wait.h"
#include "sendchar.h"
#include "i2c_slave.h"

#define UART_BAUD_RATE 115200

int main(void) __attribute__((weak));
int main(void) {
#ifdef CLKPR
    // avoid unintentional changes of clock frequency in devices that have a
    // clock prescaler
    CLKPR = 0x80, CLKPR = 0;
#endif
#ifndef NO_UART
    uart_init(UART_BAUD_RATE);
#endif
    keyboard_setup();

    i2c_slave_init(0x31);
    for (uint8_t i = 0; i < 0xf; i++) {
      i2c_slave_reg[i] = i;
      i2c_slave_reg[i+0xf] = 0xf - i;
    }
    host_set_driver(i2ckb_driver());
    print_set_sendchar(sendchar);
    sei();

    wait_ms(50);

    keyboard_init();

    debug("main loop\n");
    while (1) {
        keyboard_task();
    }
}
