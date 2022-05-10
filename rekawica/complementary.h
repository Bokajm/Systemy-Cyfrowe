#pragma once
#include "ownTypes.h"

class complementaryFilter
{
    constexpr static float accelWeight = 0.65f;
    constexpr static float gyroWeight = 1.0f - accelWeight;
    constexpr static float integratingTimeInterval = 0.01;
    constexpr static float gyroSensitivity = (float)256;
    constexpr static float accelSensitivity = (float)30;
  public:
    void update(const vec3& accelData, const vec3& gyroData);
    vec2<int8_t> getAngles() const {
      return integratedAngles;
    }

  private:
    void integrateGyroData(const vec3& gyroSample);

    int32_t calculateAccelMagnitude(const vec3& accelData) const;

    bool accelMagnitudeValid(int32_t magnitude)
    {
      return magnitude > 8192 and magnitude < 32768;
    }
    float calculateAngle(int16_t side, int16_t down) const;

    void updateStoredAngles(float x, float y);


    vec2<int8_t> integratedAngles{};
};
