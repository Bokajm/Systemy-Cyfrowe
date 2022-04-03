#include "MPU6050.h"
#include "i2c_hal.h"

MPU6050::MPU6050(uint8_t addr)
  : deviceAddress{addr} {}

bool MPU6050::begin() {
  if(!i2c::ping(deviceAddress)){
    return false;
  }
  return true;
}

void MPU6050::writeByte(uint8_t addr, uint8_t val)
{
  i2c::writeToAddr(deviceAddress, addr, val);
}
uint8_t MPU6050::readByte(uint8_t addr)
{
  return i2c::readFromAddr(deviceAddress, addr);
}
