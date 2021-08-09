#include <Wire.h>

const int openDelay = 15000;
const int doorsCount = 4; 
const int doors[] = {7, 6, 5, 4};

bool doorsOpened[] = {false, false, false, false};
unsigned long doorsTime[] = {0, 0, 0, 0};

void setup() {
  Wire.begin(0x8);
  Wire.onReceive(receiveEvent);
  
  pinMode(doors[0], OUTPUT);
  pinMode(doors[1], OUTPUT);
  pinMode(doors[2], OUTPUT);
  pinMode(doors[3], OUTPUT);
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    int digit = Wire.read() - 1;
    doorsOpened[digit] = true;
    doorsTime[digit] = millis();
  }
}

void loop() {
  updateDoors();
  openDoors();
}

void openDoors() {
 for (int i = 0; i < doorsCount; i++) {
  if (doorsOpened[i]) {
   digitalWrite(doors[i], HIGH);
  } else {
   digitalWrite(doors[i], LOW);
  }
 }
}

void updateDoors() {
  for (int i = 0; i < doorsCount; i++){
    if (doorsOpened[i] and millis() - doorsTime[i] > openDelay) {
      doorsOpened[i] = false;
    } 
  }
}
