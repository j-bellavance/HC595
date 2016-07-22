
/*
 * Sweeps from the center of leds
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
int half = int((lastPin+1)/2);

void inwardSweep() {
  for (int i = 0 ; i < half ; i++) {
    ledArray.setPin(i, TOGGLE);
    ledArray.setPin(lastPin-i, TOGGLE);
    delay(delayMs);
    ledArray.setPin(i, TOGGLE);
    ledArray.setPin(lastPin-i, TOGGLE);
  }
}
void outwardSweep() {
  for (int i = half ; i >= 0 ; i--) {
    ledArray.setPin(i, TOGGLE);
    ledArray.setPin(lastPin-i, TOGGLE);
    delay(delayMs);
    ledArray.setPin(i, TOGGLE);
    ledArray.setPin(lastPin-i, TOGGLE);
  }
}

void setup() {
  ledArray.reset();
}

void loop() {
  outwardSweep();
  inwardSweep();
}
