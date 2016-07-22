/*
 * HC595.cpp pour contrôler jusqu'à 8 registres à décalage 74HC595.
 * Jusqu'à 64 sorties à l'aide de seulement 3 broches d'un Arduino.
 * Voir : https://www.arduino.cc/en/Tutorial/ShiftOut pour les connexions.
 * Créé par Jacques Bellavance le 2 juillet 2016.
 * Ce code est du domaine public.
 */
 /*
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General
 Public License along with this library; if not, write to the
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA  02111-1307  USA
 */
#include "arduino.h"
#include "HC595.h"

//Conctructeur=======================================================================
//Initialisation du mode des trois broches.
//Décompte du nombre de 74HC595 du montage.
//Remise à zéro du tableau des 8 octets contenant la valeur des 64 broches de sortie.
//-----------------------------------------------------------------------------------
HC595::HC595(int count, int latchPin, int clockPin, int dataPin) {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  MYchipCount = count;
  MYlatchPin = latchPin;
  MYclockPin = clockPin;
  MYdataPin = dataPin;
  MYlastPin = count * 8 - 1;
  reset();
}//Constructeur----------------------------------------------------------------------

//isLeastSignificantBitFirst()============================
//Permet de déterminer que les données seront envoyées
//vers les 74HC595 à partir du bit le moins significatif
//--------------------------------------------------------
void HC595::isLeastSignificantBitFirst() {
	MYway = LSBF;
}//isLeastSignificantBitFirst()---------------------------

//isMostSignificantBitFirst()============================
//Permet de déterminer que les données seront envoyées
//vers les 74HC595 à partir du bit le plus significatif
//C'est la valeur par défaut.
//--------------------------------------------------------
void HC595::isMostSignificantBitFirst() {
	MYway = MSBF;
}//isMostSignificantBitFirst()----------------------------

//reset()==========================================
//Remise à zéro du tableau des 8 octets contenant 
//la valeur des 64 broches de sortie.
//-------------------------------------------------
void HC595::reset() {
  for (int i = 0 ; i < 8 ; i++) MYarray[i] = 0;
  send();
}//reset()-----------------------------------------

//sendToChips()==================================================
//Verrou=LOW; data=LOW
//Envoyer, pour chaque 74HC595 du montage, 
//le bit le plus significatif en premier, un bit à la fois.
//(Clock=LOW; data=BitToSend; clock=HIGH; data=LOW)
//Verrou=HIGH
//---------------------------------------------------------------
void HC595::sendToChips() {
  digitalWrite(MYlatchPin, LOW);
  digitalWrite(MYdataPin, LOW);
  for (int i = MYchipCount-1 ; i >= 0 ; i--) {
	  for (int j = 7; j >= 0; j--) {
		  digitalWrite(MYclockPin, LOW);
		  if ((MYarray[i] & MYmask[j]) > 0) {
			  digitalWrite(MYdataPin, HIGH);
		  }
		  digitalWrite(MYclockPin, HIGH);
		  digitalWrite(MYdataPin, LOW);
	  }
  }
  digitalWrite(MYlatchPin, HIGH);
}//sendToChips()-------------------------------------------------

//reverseSendToChips()===========================================
//Verrou=LOW; data=LOW
//Envoyer, pour chaque 74HC595 du montage, 
//le bit le moins significatif en premier, un bit à la fois.
//(clock=LOW; data=valeurDuBit; clock=HIGH; data=LOW)
//Verrou=HIGH
//---------------------------------------------------------------
void HC595::reverseSendToChips() {
	digitalWrite(MYlatchPin, LOW);
	digitalWrite(MYdataPin, LOW);
	for (int i = 0; i < MYchipCount; i++) {
		for (int j = 0; j < 8; j++) {
			digitalWrite(MYclockPin, LOW);
			if ((MYarray[i] & MYmask[j]) > 0) {
				digitalWrite(MYdataPin, HIGH);
			}
			digitalWrite(MYclockPin, HIGH);
			digitalWrite(MYdataPin, LOW);
		}
	}
	digitalWrite(MYlatchPin, HIGH);
}//reverseSendToChips()--------------------------------------------

//send()========================================
//Envoyer aux 74HC595
//----------------------------------------------
void HC595::send() {
  if (MYway == MSBF) sendToChips();
  else               reverseSendToChips();
}//send()---------------------------------------

//setpin()====================================================
//Utilisation des opérateurs binaires
//MYmask[] contient les puissances de 2,
//255 - MYmask[] contient son inverse
// 00000001  11111110
// 00000010  11111101
// 00000100  11111011
// 00001000  11110111
// 00010000  11101111
// 00100000  11011111
// 01000000  10111111
// 10000000  01111111

// ON:   10101010 | 00000001 = 10101011
// OFF:  10101010 & 11111101 = 10101000
// Lire: 10101010 & 00000010 = 00000010
//------------------------------------------------------------
void HC595::setPin(int pin, int action) {
  int chip = int(pin / 8);
  int pos = pin - (chip * 8);
  switch (action) {
    case OFF:{
      MYarray[chip] = MYarray[chip] & (255 - MYmask[pos]);
      break;  
    }
    case ON:{
      MYarray[chip] = MYarray[chip] | MYmask[pos];
      break;
    }
    case TOGGLE:{
      if ((MYarray[chip] & MYmask[pos]) == 0) 
        MYarray[chip] = MYarray[chip] | MYmask[pos];
      else
        MYarray[chip] = MYarray[chip] & (255 - MYmask[pos]);
      break;
    }
  }
  send();
}

//setPins()=================================================
//Utilise une boucle pour actionner un intervale de broches
//----------------------------------------------------------
void HC595::setPins(int from, int to, int action) {
  for (int i = from ; i <= to ; i++) setPin(i, action);
}//setPins()------------------------------------------------

//getState()=======================================
//Lire la valeur de la broche.
//-------------------------------------------------
int HC595::getState(int pin) {
  int chip = int(pin / 8);
  int pos = chip - (pin * 8);
  int actualValue = MYarray[chip] & MYmask[pos];
  if (actualValue == 0) return 0; else return 1;
}//getState()--------------------------------------

//toString()==============================================
//Construit une chaîne représentant l'état des 64 broches
//--------------------------------------------------------
String HC595::toString() {
  String s = "";
  for (int i = (MYchipCount - 1) ; i >= 0; i--) {
    s += byteToString(MYarray[i]);
    s += "|";
  }
  return s;
}//toString()---------------------------------------------

//byteToString()=================================
//Construit une chaîne représentant l'état 
//des broches d'un octet.
//-----------------------------------------------
String HC595::byteToString(int data) {
  String s = "";
  for (int i = 7 ; i >= 0; i--) {
    s += bitRead(data,i);
  }
  return s;
}//byteToString()-------------------------------

int HC595::lastPin() {
	return MYlastPin;
}



