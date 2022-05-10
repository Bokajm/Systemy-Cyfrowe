#pragma once
#include "MPU6050.h"
#include "ownTypes.h"

namespace mat {
  vec2<int8_t> calculateMouseMovement(vec3 ax, vec3 gyro);
}
