# HC595
//Constructor

HC595 ledArray(chipCount,latchPin,clockPin,dataPin);



//Available methods :

// void isLeastSignificantBitFirst();            
//// Declare the type of output to the 74HC595 LSBFIRST

// void isMostSignificantBitFirst();             
//// Declare the type of output to the 74HC595 MSBFIRST (Default)

// void reset();                                 
//// Reset all 64 pins to zero

// void setPin(int pin, int action);             
//// Set the value of a pin
//// - "action" can be : ON or HIGH, OFF or LOW, TOGGLE

// void setPins(int from, int to, int action);   
//// Set the values of contigous pins

// void send();                                  
//// Sent the contents of the pins to the 74HC595
//// Send is always automaticaly called after :
//// setPin(), setPins() and reset()

// int getState(int pin);                        
//// Get the state of a particular pin

// String toString();                            
//// See the contents of all pins as a string of '0' or '1'

// int lastPin();                                
//// Pins are numbered from 0 to lastPin()
