#include "i2c_hal.h"
#include <avr/io.h>

namespace i2c {

void init() {
  DDRD &= 0b11111100; //DDRXx = 0 -> pinx in port X set as input(data direction register)
  PORTD |= 3; //PORTXx = 1 -> pull-up enabled on pin x in port X(port register)

  TWBR = 72; //baud rate 100KHz (two wire baudrate register)
  TWSR = 0; // two wire status register, prescaler(2 lower bits) = 0
  TWCR |= 1 << TWEN; //enable I2C
}

void wait() {
  while (!(TWCR & (1 << TWINT))) ;
  //Wait until interrupt bit in control register becomes 0
}

void start() {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  //Set interrupt flag to 1(inactive),
  //Set start bit to send start condition,
  //set enable interface
}

uint8_t readAddr(uint8_t deviceAddr, uint8_t registerAddr) {

}
}// i2c
