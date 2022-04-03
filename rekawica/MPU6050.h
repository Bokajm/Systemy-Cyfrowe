#pragma once
#include <inttypes.h>

class MPU6050{
public:
  explicit MPU6050(uint8_t addr);

private:
  uint8_t deviceAddress{0};
};
