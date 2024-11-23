#include <Wire.h>

// LEFT BTS
#define RPWM1_Pin 5
#define LPWM1_Pin 6

// RIGHT BTS
#define RPWM2_Pin 9
#define LPWM2_Pin 10

char receivedData;

// SPEED
int speed = 250;

void setup() {
  Serial.begin(9600);
  
  pinMode(RPWM1_Pin, OUTPUT);
  pinMode(LPWM1_Pin, OUTPUT);
  pinMode(RPWM2_Pin, OUTPUT);
  pinMode(LPWM2_Pin, OUTPUT);

  Wire.begin(11);
  Wire.onReceive(receiveEvent);
}

void loop() {
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    receivedData = Wire.read();
    Serial.print("Gelen veri: ");
    Serial.println(receivedData);

    if (receivedData == 'f') {
      forward(speed);
    }
    if (receivedData == 'b') {
      backward(speed);
    }
    if (receivedData == 'l') {
      left(speed);
    }
    if (receivedData == 'r') {
      right(speed);
    }
    if (receivedData == 's'){
      stop();
   }
  }
}

void forward(int speed) {
  analogWrite(RPWM2_Pin, 0);
  analogWrite(LPWM2_Pin, speed);
  analogWrite(RPWM1_Pin, speed);
  analogWrite(LPWM1_Pin, 0);
  Serial.println("forward");
}

void backward(int speed) {
  analogWrite(RPWM2_Pin, speed);
  analogWrite(LPWM2_Pin, 0);
  analogWrite(RPWM1_Pin, 0);
  analogWrite(LPWM1_Pin, speed);
  Serial.println("backward");
}

void left(int speed) {
  analogWrite(RPWM2_Pin, 0);
  analogWrite(LPWM2_Pin, speed);
  analogWrite(RPWM1_Pin, 0);
  analogWrite(LPWM1_Pin, speed);
  Serial.println("left");
}

void right(int speed) {
  analogWrite(RPWM2_Pin, speed);
  analogWrite(LPWM2_Pin, 0);
  analogWrite(RPWM1_Pin, speed);
  analogWrite(LPWM1_Pin, 0);
  Serial.println("right");
}

void stop() {
  analogWrite(RPWM2_Pin, 0);
  analogWrite(LPWM2_Pin, 0);
  analogWrite(RPWM1_Pin, 0);
  analogWrite(LPWM1_Pin, 0);
  Serial.println("stop");
}
