
/*
 * A random (between 1 and 4) number of leds follow the leader
 */
#include <HC595.h>

const int chipCount = 2;  // Number of serialy connected 74HC595 (8 maximum)
const int latchPin = 11;  // Pin ST_CP (12) of the 74HC595
const int clockPin = 10;  // Pin SH_CP (11) of the 74HC595
const int dataPin = 12;   // Pin DS (14) of the 74HC595

//Constructor
HC595 ledArray(chipCount,latchPin,clockPin,dataPin);

int delayMs = 200;
int lastPin = ledArray.lastPin();

void setup() {
  ledArray.reset();
  randomSeed(analogRead(A0)); //nothing connected to A0
}

void loop() {
  int followers = random(1,5);
  for(int i = 0 ; i <= lastPin ; i++) {
    ledArray.setPin(i, ON);
    if (i >= followers) ledArray.setPin(i-followers, OFF);
    delay(delayMs);
  }
  for (int i = lastPin-followers ; i <= lastPin; i++) {
    ledArray.setPin(i, OFF);
    delay(delayMs); 
  }
}

