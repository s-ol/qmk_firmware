- reimplement quantum/split_common/transport.c
  - transport_master:
    - i2c > slave matrix, encoder
    - i2c < backlight, wpm, rgb
    - i2c < USB descriptor, dirty flag
  - tranpost_slave: (unchanged)
    - i2c < slave matrix, encoder
    - i2c > backlight, wpm, rgb

  - raspi driver:
    - READ SLAVE matrix, encoder
    - READ MASTER backlight, wpm, rgb, USB+dirty
    - if dirty: send USB
    - WRITE MASTER matrix, encoder; unset dirty flag
    - WRITE SLAVE backlight, wpm, rgb 
