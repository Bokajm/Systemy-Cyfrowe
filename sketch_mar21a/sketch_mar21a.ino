void i2c_init() {
  DDRD &= 0b11111100; //data direction register = 0 -> input
  PORTD |= 3; //port = 1 -> pull-up enabled

  TWBR = 72; //baud rate 100KHz
  TWSR = 0;
  TWCR |= 1 << TWEN; //enable I2C
}

void i2c_transmit() {
    
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
