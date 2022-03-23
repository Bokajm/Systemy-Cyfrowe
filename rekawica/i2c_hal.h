#pragma once
#include <inttypes.h>

void i2c_init();
uint8_t i2c_read_addr(uint8_t deviceAddr, uint8_t registerAddr);
