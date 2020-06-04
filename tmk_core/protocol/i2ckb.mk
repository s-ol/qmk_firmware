I2CKB_DIR = protocol/i2ckb

OPT_DEFS += -DPROTOCOL_I2CKB

SRC +=	$(I2CKB_DIR)/main.c \
  $(I2CKB_DIR)/i2ckb.c \
  $(COMMON_DIR)/sendchar_uart.c \
	$(COMMON_DIR)/uart.c \
	i2c_slave.c
	# i2c_master.c
