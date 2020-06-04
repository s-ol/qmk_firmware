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

#include <avr/wdt.h>
#include <util/delay.h>
#include <stdint.h>
#include "host.h"
#include "report.h"
#include "host_driver.h"
#include "uart.h"
#include "print.h"
#include "debug.h"
#include "i2c_slave.h"

#define TIMEOUT 100

static uint8_t i2ckb_keyboard_leds = 0;

/*------------------------------------------------------------------*
 * Host driver
 *------------------------------------------------------------------*/
static uint8_t keyboard_leds(void);
static void    send_keyboard(report_keyboard_t *report);
static void    send_mouse(report_mouse_t *report);
static void    send_system(uint16_t data);
static void    send_consumer(uint16_t data);

static host_driver_t driver = {keyboard_leds, send_keyboard, send_mouse, send_system, send_consumer};

host_driver_t *i2ckb_driver(void) { return &driver; }

static uint8_t keyboard_leds(void) { return i2ckb_keyboard_leds; }

static void send_keyboard(report_keyboard_t *report) {
    // i2c_writeReg(0x37, 0x01, report->raw, KEYBOARD_REPORT_SIZE, TIMEOUT);
}

static void send_mouse(report_mouse_t *report) {
#ifdef MOUSE_ENABLE
    //
#endif
}

static void send_system(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    //
#endif
}

static void send_consumer(uint16_t data) {
#ifdef EXTRAKEY_ENABLE
    //
#endif
}
