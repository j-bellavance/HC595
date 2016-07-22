
/*
 * Turns on half of the leds,
 * then randomly toggles all the leds
 */
#include <HC595.h>

const int chipCount = 2;  // Number of serialy connected 74HC595 (8 maximum)
const int latchPin = 11;  // Pin ST_CP (12) of the 74HC595
const int clockPin = 10;  // Pin SH_CP (11) of the 74HC595
const int dataPin = 12;   // Pin DS (14) of the 74HC595

//Constructor
HC595 ledArray(chipCount,latchPin,clockPin,dataPin);

int delayMs = 100;
int lastPin = ledArray.lastPin();

void oddsOn() {
  for (int i = 0 ; i <= lastPin ; i+=2) {
    ledArray.setPin(i, ON);
  }
}

void setup() {
  randomSeed(analogRead(A0));  // Nothing connected to A0
  ledArray.reset();
  oddsOn();
}

void loop() {
  ledArray.setPin(random(0,lastPin+1), TOGGLE);
  delay(delayMs);
}
