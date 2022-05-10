#include "complementary.h"
#include <math.h>

void complementaryFilter::update(const vec3& accelData, const vec3& gyroData)
{
  integrateGyroData(gyroData);
  log("Integrated gyro val: x=", gyroIntegratedAngles.x, ", y=", gyroIntegratedAngles.y, "\r\n");
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
  gyroIntegratedAngles.y += (static_cast<float>(gyroSample.x)) * integratingTimeInterval;
  gyroIntegratedAngles.x -= (static_cast<float>(gyroSample.y)) * integratingTimeInterval;
}

int32_t complementaryFilter::calculateAccelMagnitude(const vec3& accelData) const
{
  return fabs(accelData.x) + fabs(accelData.y) + fabs(accelData.z);
}


float complementaryFilter::calculateAngle(int16_t side, int16_t down) const
{
  return atan2(side * 4, down) * accelSensitivity;
}

void complementaryFilter::updateStoredAngles(float x, float y)
{
  constexpr int16_t scalingFactor = 256;
  lastCalculatedAngles.x = (float)(gyroIntegratedAngles.x / scalingFactor) * gyroWeight + (float)(x / scalingFactor) * accelWeight;
  lastCalculatedAngles.y = (float)(gyroIntegratedAngles.y / scalingFactor) * gyroWeight + (float)(y / scalingFactor) * accelWeight;
}
