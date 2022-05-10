#include "complementary.h"
#include <math.h>

void complementaryFilter::update(const vec3& accelData, const vec3& gyroData)
{
  integrateGyroData(gyroData);
  log("Raw values: x=", gyroData.x, ", y=", gyroData.y, ", z=", gyroData.z, "\t\t\t");
  log("Integrated gyro val: x=", integratedAngles.x, ", y=", integratedAngles.y, "\r\n");
  const auto accelMagnitude = calculateAccelMagnitude(accelData);

  if (accelMagnitudeValid(accelMagnitude))
  {
    const auto x = calculateAngle(accelData.x, accelData.z);
    const auto y = calculateAngle(accelData.y, accelData.z);
    //log("Raw values: x=", accelData.x, ", y=", accelData.y, ", z=", accelData.z, "\t\t");
    //log("Current accel values: x=", x, ", y=", y, "\r\n");
    updateStoredAngles(x, y);
  }
}

void complementaryFilter::integrateGyroData(const vec3& gyroSample)
{
  integratedAngles.y += (static_cast<float>(gyroSample.x) / gyroSensitivity) * integratingTimeInterval;
  integratedAngles.x -= (static_cast<float>(gyroSample.y) / gyroSensitivity) * integratingTimeInterval;
}

int32_t complementaryFilter::calculateAccelMagnitude(const vec3& accelData) const
{
  return fabs(accelData.x) + fabs(accelData.y) + fabs(accelData.z);
}


float complementaryFilter::calculateAngle(int16_t side, int16_t down) const
{
  const auto tmp = atan2((float)side, (float)down);
  return min(max(tmp, -1), 1) * accelSensitivity;;
}

void complementaryFilter::updateStoredAngles(float x, float y)
{
  constexpr int16_t scalingFactor = 256;
  integratedAngles.y = integratedAngles.y * gyroWeight + y * accelWeight;
  integratedAngles.x = integratedAngles.x * gyroWeight + x * accelWeight;
}
