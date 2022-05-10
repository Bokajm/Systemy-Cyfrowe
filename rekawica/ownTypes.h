#pragma once
#include <inttypes.h>

struct vec3 {
  int16_t x, y, z;
};

template<typename T>
struct vec2 {
  T x, y;
};
