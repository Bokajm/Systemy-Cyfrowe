#include "temp_mat.h"
#include <math.h>

namespace mat {
constexpr float sensitivity = 25.0f;
vec2<int8_t> calculateMouseMovement(vec3 acc, vec3 gyro) {
  vec2<int8_t> res;

  float x, y;

  x = atan2((float)acc.x, (float)acc.z);
  if (x > 1) {
    x = 1;
  }
  if (x < -1) {
    x = -1;
  }

  y = atan2((float)acc.y, (float)acc.z);
  if (y > 1) {
    y = 1;
  }
  if (y < -1) {
    y = -1;
  }

  res.x = (int8_t) (x * sensitivity);
  res.y = (int8_t) (y * sensitivity);
  return res;
}
}
