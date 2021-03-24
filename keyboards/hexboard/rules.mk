# MCU name
MCU = atmega32u2

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no  # Virtual DIP switch configuration
MOUSEKEY_ENABLE  = no  # Mouse keys
EXTRAKEY_ENABLE  = no  # Audio control and System control
CONSOLE_ENABLE   = no  # Console for debug
COMMAND_ENABLE   = no  # Commands for debug and configuration
NKRO_ENABLE      = no  # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
UNICODE_ENABLE   = no  # Unicode
SLEEP_LED_ENABLE = no
MUSIC_ENABLE     = no
MIDI_ENABLE      = no
RGBLIGHT_ENABLE  = yes
COMBO_ENABLE     = yes
# RGB_MATRIX_ENABLE = WS2812

SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = serial

SRC += i2c-bitbang.c oled.c

SRC += hxmidi.c transport.c
SPLIT_TRANSPORT = custom
OPT_DEFS += -DSERIAL_DRIVER_BITBANG
QUANTUM_LIB_SRC += serial.c
