#include "i2c_hal.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) ;
  i2c::init();
}

void loop() {
  // put your main code here, to run repeatedly:

}
