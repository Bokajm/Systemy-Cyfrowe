#include "i2c_hal.h"
#include <avr/io.h>

void i2c_init() {
  DDRD &= 0b11111100; //DDRXx = 0 -> pinx in port X set as input(data direction register)
  PORTD |= 3; //PORTXx = 1 -> pull-up enabled on pin x in port X(port register)

  TWBR = 72; //baud rate 100KHz (two wire baudrate register)
  TWSR = 0; // two wire status register, prescaler(2 lower bits) = 0
  TWCR |= 1 << TWEN; //enable I2C
}

uint8_t i2c_read_addr(uint8_t deviceAddr, uint8_t registerAddr) {
  
}
