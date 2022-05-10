#pragma once
#include <inttypes.h>
#include <Arduino.h>

struct vec3 {
  int16_t x, y, z;
};

template<typename T>
struct vec2 {
  T x, y;
};

template<typename... T>
void log(T... t) {
  ((Serial1.print(t)), ...);
   }
