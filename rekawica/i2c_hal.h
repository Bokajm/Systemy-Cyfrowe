#pragma once
#include <inttypes.h>

namespace i2c {
void init();
bool ping(uint8_t deviceAddr);
uint8_t readFromAddr(uint8_t deviceAddr, uint8_t registerAddr);
void readMultipleFromAddr(uint8_t deviceAddr, uint8_t registerAddr, uint8_t *buffer, uint8_t n);
void writeToAddr(uint8_t deviceAddr, uint8_t registerAddr, uint8_t val);
}//i2c
