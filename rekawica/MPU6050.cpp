#include "MPU6050.h"
#include "i2c_hal.h"
#include <Arduino.h>

MPU6050::MPU6050(uint8_t addr)
  : deviceAddress{addr} {}

bool MPU6050::begin() {
  if(!i2c::ping(deviceAddress) || (readByte(0x75) != 0x68)){
    return false;
  }
  Serial.println("Ping success");
  writeByte(0x6B, 0b00000001);//Set clock source to gyro x, enable everything
  writeByte(0x1B, 0b00010000);//Set gyroscope full scale to +-1000deg/s
  writeByte(0x1C, 0b00001000);//Set accelerometer full range to 4g.
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
