
/*
 * Sweeps back and forth like Kitt in Knight Rider
 * Uses the possibility to send the most or least significant bit first
 */
#include <HC595.h>

const int chipCount = 2;  // Number of serialy connected 74HC595 (8 maximum)
const int latchPin = 11;  // Pin ST_CP (12) of the 74HC595
const int clockPin = 10;  // Pin SH_CP (11) of the 74HC595
const int dataPin = 12;   // Pin DS (14) of the 74HC595

//Constructor
HC595 ledArray(chipCount,latchPin,clockPin,dataPin);

int delayMs = 50;
int lastPin = ledArray.lastPin();

void sweep() {
  for (int i = 0 ; i <= lastPin ; i++) {
    ledArray.setPin(i, TOGGLE);
    delay(delayMs);
    ledArray.setPin(i, TOGGLE);
  }
}

void setup() {
  ledArray.reset();
}

void loop() {
  sweep();
  ledArray.isLeastSignificantBitFirst();
  sweep();
  ledArray.isMostSignificantBitFirst(); 
}
