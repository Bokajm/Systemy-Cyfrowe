#pragma once
#include <inttypes.h>

namespace i2c {

void init();
uint8_t readAddr(uint8_t deviceAddr, uint8_t registerAddr);

}//i2c
