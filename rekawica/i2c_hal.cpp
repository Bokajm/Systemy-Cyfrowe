#include "i2c_hal.h"
#include <Arduino.h>

namespace i2c {
constexpr uint8_t START = 0x08;
constexpr uint8_t SLA_W_ACK_RECEIVED = 0x18;
constexpr uint8_t DATA_ACK_RECEIVED = 0x28;
constexpr uint8_t RESTART = 0x10;
constexpr uint8_t SLA_R_ACK_RECEIVED = 0x40;

namespace {
template<typename... T>
void log(T... t) {
  ((Serial.println(t)), ...);
}

void logb(uint8_t b) {
  Serial.println(b, BIN);
}
}

void init() {
  DDRD &= 0b11111100; //DDRXx = 0 -> pinx in port X set as input(data direction register)
  PORTD |= 3; //PORTXx = 1 -> pull-up enabled on pin x in port X(port register)

  TWBR = 72; //baud rate 100KHz (two wire baudrate register)
  TWSR = 0; // two wire status register, prescaler(2 lower bits) = 0
  TWCR |= 1 << TWEN; //enable I2C
}

void wait() {
  while (!(TWCR & (1 << TWINT)));
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

void sendByte(uint8_t data) {
  TWDR = data;//Load data into data register
  TWCR = (1 << TWINT) | (1 << TWEN); //Set int bit and enable bit to send
}

bool sendRegisterAddrToSlave(uint8_t deviceAddr, uint8_t registerAddr) {
  start();
  wait();
  if (!checkStatus(START)) {
    log("Error sending start condition");
  }
  sendByte((deviceAddr << 1) & 0xFE); //Send slave addr with write command
  wait();
  if (!checkStatus(SLA_W_ACK_RECEIVED)) {
    Serial.println("Did not receive ACK on addr");
    return false;
  }
  sendByte(registerAddr);
  wait();
  if (!checkStatus(DATA_ACK_RECEIVED)) {
    Serial.println("Did not receive ACK on data");
    return false;
  }
  return true;
}

void stop() {
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

uint8_t readByteFromSlave(uint8_t deviceAddr) {
  start();//Restart actually, but command is the same
  wait();
  if (!checkStatus(RESTART)) {
    Serial.println("Error sending restart condition");
  }
  sendByte(deviceAddr << 1 | 1); //Slave addr with read command
  wait();
  if (!checkStatus(SLA_R_ACK_RECEIVED)) {
    Serial.println("Didn't receive ACK on 2nd addr");
  }

  TWCR = 1 << TWINT | 1 << TWEN; //Let us receive data;
  wait();
  uint8_t receivedByte = TWDR;
  stop();
  return receivedByte;
}

uint8_t readFromAddr(uint8_t deviceAddr, uint8_t registerAddr) {
  if (!sendRegisterAddrToSlave(deviceAddr, registerAddr)) {
    return 0;
  }
  return readByteFromSlave(deviceAddr);
}
void writeToAddr(uint8_t deviceAddr, uint8_t registerAddr, uint8_t val) {
  if (!sendRegisterAddrToSlave(deviceAddr, registerAddr)) {
    return;
  }
  sendByte(val);
  wait();
  stop();
}

bool ping(uint8_t deviceAddr) {
  bool success=false;
  start();
  wait();
  if (!checkStatus(START)) {
    log("Error sending start condition");
  }
  sendByte((deviceAddr << 1) & 0xFE); //Send slave addr with write command
  wait();
  if (checkStatus(SLA_W_ACK_RECEIVED)) {
    success=true;
  }
  stop();
  return success;
}
}// i2c
