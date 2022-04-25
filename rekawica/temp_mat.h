#pragma once
#include "MPU6050.h"

struct vec2 {
  int8_t x, y;
};

namespace mat {
  vec2 calculateMouseMovement(vec3 ax, vec3 gyro);
}
