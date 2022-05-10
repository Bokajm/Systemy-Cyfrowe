#include "complementary.h"
#include <math.h>

void complementaryFilter::update(const vec3& accelData, const vec3& gyroData)
{
  integrateGyroData(gyroData);
  const auto accelMagnitude = calculateAccelMagnitude(accelData);
  if (accelMagnitudeValid(accelMagnitude))
  {
    const auto x = calculateAngle(accelData.x, accelData.z);
    const auto y = calculateAngle(accelData.y, accelData.z);

    updateStoredAngles(x, y);
  }
}

void complementaryFilter::integrateGyroData(const vec3& gyroSample)
{
  gyroIntegratedAngles.x += (static_cast<float>(gyroSample.x) / gyroSensitivity) * integratingTimeInterval;
  gyroIntegratedAngles.y += (static_cast<float>(gyroSample.y) / gyroSensitivity) * integratingTimeInterval;
}

float complementaryFilter::calculateAngle(int16_t side, int16_t down) const
{
  return atan2f(side, down) * accelSensitivity;
}

void complementaryFilter::updateStoredAngles(float x, float y)
{
  constexpr uint16_t scalingFactor = 256;
  lastCalculatedAngles.x = (gyroIntegratedAngles.x / scalingFactor) * gyroSensitivity + (x / scalingFactor) * accelSensitivity;
  lastCalculatedAngles.y = (gyroIntegratedAngles.y / scalingFactor) * gyroSensitivity + (y / scalingFactor) * accelSensitivity;
}
