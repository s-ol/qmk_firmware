#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "font5x8.h"
#include "oled.h"
#include "i2c-bitbang.h"

#define OLED_PORT PORTB
#define OLED_DDR  DDRB
// #define OLED_RESET     1 << PC7

#define SSD1306_MEMORYMODE 0x20          ///< See datasheet
#define SSD1306_COLUMNADDR 0x21          ///< See datasheet
#define SSD1306_PAGEADDR 0x22            ///< See datasheet
#define SSD1306_SETCONTRAST 0x81         ///< See datasheet
#define SSD1306_CHARGEPUMP 0x8D          ///< See datasheet
#define SSD1306_SEGREMAP 0xA0            ///< See datasheet
#define SSD1306_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SSD1306_DISPLAYALLON 0xA5        ///< Not currently used
#define SSD1306_NORMALDISPLAY 0xA6       ///< See datasheet
#define SSD1306_INVERTDISPLAY 0xA7       ///< See datasheet
#define SSD1306_SETMULTIPLEX 0xA8        ///< See datasheet
#define SSD1306_DISPLAYOFF 0xAE          ///< See datasheet
#define SSD1306_DISPLAYON 0xAF           ///< See datasheet
#define SSD1306_COMSCANINC 0xC0          ///< Not currently used
#define SSD1306_COMSCANDEC 0xC8          ///< See datasheet
#define SSD1306_SETDISPLAYOFFSET 0xD3    ///< See datasheet
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5  ///< See datasheet
#define SSD1306_SETPRECHARGE 0xD9        ///< See datasheet
#define SSD1306_SETCOMPINS 0xDA          ///< See datasheet
#define SSD1306_SETVCOMDETECT 0xDB       ///< See datasheet

#define SSD1306_SETLOWCOLUMN 0x00  ///< Not currently used
#define SSD1306_SETHIGHCOLUMN 0x10 ///< Not currently used
#define SSD1306_SETSTARTLINE 0x40  ///< See datasheet

#define SSD1306_EXTERNALVCC 0x01  ///< External display voltage source
#define SSD1306_SWITCHCAPVCC 0x02 ///< Gen. display voltage from 3.3V

#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26              ///< Init rt scroll
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27               ///< Init left scroll
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 ///< Init diag scroll
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A  ///< Init diag scroll
#define SSD1306_DEACTIVATE_SCROLL 0x2E                    ///< Stop scroll
#define SSD1306_ACTIVATE_SCROLL 0x2F                      ///< Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3             ///< Set scroll range


void ssd1306_command1(uint8_t c) {
  i2c_start();
  i2c_writebyte(0x78);
  i2c_writebyte(0x00);
  i2c_writebyte(c);
  i2c_stop();
}

void ssd1306_commandList(const uint8_t *c, uint8_t n) {
  i2c_start();
  i2c_writebyte(0x78);
  i2c_writebyte(0x00);
  while (n--)
    i2c_writebyte(pgm_read_byte(c++));
  i2c_stop();
}

void oled_init(void) {
  //Initialization for a 128x32 OLED (SSD1306)

#ifdef OLED_RESET
  //Toggle reset pin
  OLED_DDR |= OLED_RESET;
  OLED_PORT |= OLED_RESET;
  _delay_ms(1);
  OLED_PORT &= ~OLED_RESET;
  _delay_ms(10);
  OLED_PORT |= OLED_RESET;
#endif

// Init sequence
  static const uint8_t PROGMEM init1[] = {SSD1306_DISPLAYOFF,         // 0xAE
                                          SSD1306_SETDISPLAYCLOCKDIV, // 0xD5
                                          0x80, // the suggested ratio 0x80
                                          SSD1306_SETMULTIPLEX}; // 0xA8

  ssd1306_commandList(init1, sizeof(init1));
  ssd1306_command1(32 - 1);

  static const uint8_t PROGMEM init2[] = {SSD1306_SETDISPLAYOFFSET, // 0xD3
                                          0x0,                      // no offset
                                          SSD1306_SETSTARTLINE | 0x0, // line #0
                                          SSD1306_CHARGEPUMP};        // 0x8D
  ssd1306_commandList(init2, sizeof(init2));

  ssd1306_command1(0x14);

  static const uint8_t PROGMEM init3[] = {SSD1306_MEMORYMODE, // 0x20
                                          0x00, // 0x0 act like ks0108
                                          SSD1306_SEGREMAP, // | 0x1
                                          SSD1306_COMSCANINC}; // DEC
  ssd1306_commandList(init3, sizeof(init3));

  uint8_t comPins = 0x02;
  uint8_t contrast = 0x8F;

  ssd1306_command1(SSD1306_SETCOMPINS);
  ssd1306_command1(comPins);
  ssd1306_command1(SSD1306_SETCONTRAST);
  ssd1306_command1(contrast);

  ssd1306_command1(SSD1306_SETPRECHARGE); // 0xd9
  ssd1306_command1(0xF1);

  //Set column start and end address
  i2c_cmd(SSD1306_COLUMNADDR);
  i2c_cmd(0x00);
  i2c_cmd(0xFF);

  //Set page start and end address
  i2c_cmd(SSD1306_PAGEADDR);
  i2c_cmd(0x00);
  i2c_cmd(0x03);

  static const uint8_t PROGMEM init5[] = {
      SSD1306_SETVCOMDETECT, // 0xDB
      0x40,
      SSD1306_DISPLAYALLON_RESUME, // 0xA4
      SSD1306_NORMALDISPLAY,       // 0xA6
      SSD1306_DEACTIVATE_SCROLL,
      SSD1306_DISPLAYON}; // Main screen turn on
  ssd1306_commandList(init5, sizeof(init5));
}

void oled_clear(uint8_t pattern) {
  i2c_start();
  i2c_writebyte(0x78);
  i2c_writebyte(0x40);
  for (uint16_t col=0; col<(128*32); col++) {
    i2c_writebyte(pattern);
  }
  i2c_stop();
}

void oled_putc(uint8_t letter) {
  uint8_t cols[5];
  memcpy_P(cols, &font5x8[letter-32], 5);

  i2c_start();
  i2c_writebyte(0x78);
  i2c_writebyte(0x40);
  for (uint8_t i=0; i<5; i++) {
    i2c_writebyte(cols[i]);
  }
  i2c_writebyte(0x00);
  i2c_stop();
}

void oled_puts(const char* string) {
  while (*string > 0) {
    oled_putc(*string);
    ++string;
  }
}
