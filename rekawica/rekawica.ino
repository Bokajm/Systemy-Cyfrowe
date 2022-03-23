#include "i2c_hal.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) ;
  i2c::init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Received byte: ");
  Serial.println(i2c::readFromAddr(0x68, 0x75));
  delay(1000);
}
