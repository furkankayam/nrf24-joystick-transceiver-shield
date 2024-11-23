#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

RF24 radio(7, 8);  // CE, CSN

const int i2cAddress = 11;

const byte address[6] = "00001";

char currentDirection = 's';

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  Wire.begin();
}

void loop() {

  if (radio.available()) {
    radio.read(&currentDirection, sizeof(currentDirection));

    switch (currentDirection) {
      case 'b':
        Serial.println("Backward");
        sendI2C('b');
        break;
      case 'r':
        Serial.println("Right");
        sendI2C('r');
        break;
      case 'f':
        Serial.println("Forward");
        sendI2C('f');
        break;
      case 'l':
        Serial.println("Left");
        sendI2C('l');
        break;
      case 's':
        Serial.println("Stop");
        sendI2C('s');
        break;
    }
  }
}

void sendI2C(char direction) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(direction);
  Wire.endTransmission();
}