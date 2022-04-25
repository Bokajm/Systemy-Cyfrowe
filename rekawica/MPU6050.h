#pragma once
#include <inttypes.h>

struct vec3 {
  int16_t x, y, z;
};

class MPU6050 {
  public:
    explicit MPU6050(uint8_t addr);
    bool begin();
    vec3 readRawAccel();
    vec3 readRawGyro();

  private:
    void writeByte(uint8_t addr, uint8_t val);
    uint8_t readByte(uint8_t addr);
    void readManyBytes(uint8_t addr, uint8_t *buffer, uint8_t n);
    vec3 readVec3FromAddr(uint8_t addr);
    uint8_t deviceAddress{0};
};
