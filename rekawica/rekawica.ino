#include "i2c_hal.h"
#include "MPU6050.h"
#include "temp_mat.h"
#include "complementary.h"

#include <Mouse.h>

MPU6050 sensor1{0x68};
MPU6050 sensor2{0x69};
complementaryFilter calculator;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  while (!Serial1) ;
  i2c::init();
  Serial1.println("Init done");
  delay(1000);
  Serial1.println(sensor1.begin());
  Serial1.println(sensor2.begin());
  Mouse.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("Received byte: ");
  //Serial.println(i2c::readFromAddr(0x68, 0x75), HEX);
  //Serial1.println("==================================");
  const auto accel = sensor1.readRawAccel();
  const auto gyro = sensor1.readRawGyro();

  const auto accel2 = sensor2.readRawAccel();
  const auto gyro2 = sensor2.readRawGyro();
  //Serial1.print("X: ");
  //Serial1.println(ret.x);
  //Serial1.print("Y: ");
  //Serial1.println(ret.y);
  //Serial1.print("Z: ");
  //Serial1.println(ret.z);
  //const auto movement = mat::calculateMouseMovement(accel, gyro);
  calculator.update(accel, gyro);
  const auto movement = calculator.getAngles();
  Mouse.move(movement.y,movement.x,0);
  const auto m2 = mat::calculateMouseMovement(accel2, gyro2);

  if(!Mouse.isPressed()){
    if(m2.x < -20){
      Mouse.press();
    }
  } else {
    if(m2.x > -15){
      Mouse.release();
    }
  }
  
  log("S1.x=", movement.x, ", S1.y=", movement.y, ",\tS2.x=", m2.x, ", S2.y=", m2.y, "\r\n");
  delay(10);
}
