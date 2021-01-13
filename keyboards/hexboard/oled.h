void oled_init(void);
void oled_clear(uint8_t letter);
void oled_putc(uint8_t letter);
void oled_puts(const char* string);
void oled_puts_P(const char* string);
void oled_setx(uint8_t column);
void oled_setyx(uint8_t row, uint8_t column);
