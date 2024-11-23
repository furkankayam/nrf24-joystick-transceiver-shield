#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE, CSN 

const byte address[6] = "00001";

int VRxPin = A0;
int VRyPin = A1;

char currentDirection = 's';

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  int xValue = analogRead(VRxPin);
  int yValue = analogRead(VRyPin);

  if (xValue > 700) {
    if (yValue > 400 && yValue < 600) {
      currentDirection = 'r';
    }
  }
  else if (xValue < 300) {
    if (yValue > 400 && yValue < 600) {
      currentDirection = 'l';
    }
  }
  else if (yValue > 700) {
    if (xValue > 400 && xValue < 600) {
      currentDirection = 'b';
    }
  }
  else if (yValue < 300) {
    if (xValue > 400 && xValue < 600) {
      currentDirection = 'f';
    }
  }
  else if (xValue > 500 && yValue <550) {
    currentDirection = 's';
  }

  bool result = radio.write(&currentDirection, sizeof(currentDirection));
  if (result) {
    Serial.print("Sent Direction: ");
    Serial.println(currentDirection);
  } else {
    Serial.println("Data could not be sent.");
  }

}