#include "i2c_hal.h"
#include "MPU6050.h"
#include "temp_mat.h"

#include <Mouse.h>

MPU6050 sensor1{0x68};

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  while (!Serial1) ;
  i2c::init();
  Serial1.println("Init done");
  delay(1000);
  Serial1.println(sensor1.begin());
  Mouse.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("Received byte: ");
  //Serial.println(i2c::readFromAddr(0x68, 0x75), HEX);
  Serial1.println("==================================");
  const auto accel = sensor1.readRawAccel();
  const auto gyro = sensor1.readRawGyro();
  //Serial1.print("X: ");
  //Serial1.println(ret.x);
  //Serial1.print("Y: ");
  //Serial1.println(ret.y);
  //Serial1.print("Z: ");
  //Serial1.println(ret.z);
  const auto movement = mat::calculateMouseMovement(accel, gyro);
  Mouse.move(movement.y,movement.x,0);
  delay(10);
}
