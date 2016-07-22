
/*
 * Shows on the serial minitor the states of the pins
 * for a fictional set of 8 74HC595s
 * switching with setPin( pinNumber, action)
 * where action is either of : ON or HIGH, OFF or LOW, TOGGLE
 */
#include <HC595.h>

const int chipCount = 8;  // Number of serialy connected 74HC595 (8 maximum)
const int latchPin = 10;  // Pin ST_CP (12) of the 74HC595
const int clockPin = 11;  // Pin SH_CP (11) of the 74HC595
const int dataPin = 12;   // Pin DS (14) of the 74HC595

//Constructor
HC595 ledArray(chipCount,latchPin,clockPin,dataPin);

void setup() {
  Serial.begin(9600);
  
  ledArray.reset();
  for (int i = 0 ; i < 64 ; i++) {
    ledArray.setPin(i, ON);
    Serial.println(ledArray.toString());
  }
  for (int i = 0 ; i < 64 ; i++) {
    ledArray.setPin(i, OFF);
    Serial.println(ledArray.toString());
  }
  for (int i = 0 ; i < 64 ; i++) {
    ledArray.setPin(i, TOGGLE);
    Serial.println(ledArray.toString());
  }
  ledArray.reset();
  Serial.println(ledArray.toString());
}

void loop() {
}
