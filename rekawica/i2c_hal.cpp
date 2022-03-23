#include "i2c_hal.h"
#include <Arduino.h>

namespace i2c {
constexpr uint8_t START = 0x08;
constexpr uint8_t SLA_W_ACK_RECEIVED = 0x18;

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

bool checkStatus(uint8_t wantedStatus) {
  return (TWSR & 0xF8) == wantedStatus;//Check if status bits are as expected
}

void sendByte(uint8_t data){
  TWDR = data;//Load data into data register
  TWCR = (1<<TWINT) | (1<<TWEN);//Set int bit and enable bit to send
}

uint8_t readAddr(uint8_t deviceAddr, uint8_t registerAddr) {
  start();
  wait();
  if (!checkStatus(START)) {
    Serial.println("Error sending start condition");
  }
  sendByte((deviceAddr<<1) & 0xFE);//Send slave addr with write command
  wait();
  if(!checkStatus(SLA_W_ACK_RECEIVED)){
    Serial.println("Did not receive ACK");
  }

}
}// i2c
