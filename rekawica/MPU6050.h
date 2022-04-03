#pragma once
#include <inttypes.h>

class MPU6050{
public:
  explicit MPU6050(uint8_t addr);
  bool begin();

private:
  void writeByte(uint8_t addr, uint8_t val);
  uint8_t readByte(uint8_t addr);
  uint8_t deviceAddress{0};
};
