/*
 * HC595.h pour contrôler jusqu'à 8 registres à décalage 74HC595.
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
#ifndef HC595_h
#define HC595_h

#define OFF 0
#define ON 1
#define TOGGLE 3
#define MSBF 0
#define LSBF 1

#include "arduino.h"

class HC595 {
  public:
    HC595(int count, int latchPin, int clockPin, int dataPin); // Constructeur
	void isLeastSignificantBitFirst();                         // LSBFirst
	void isMostSignificantBitFirst();                          // MSBFirst par défaut
	void reset();                                              // Remise à zéro des 64 sorties
    void setPin(int pin, int action);                          // Affectation d'une sortie
    void setPins(int from, int to, int action);                // Affectation de plusieurs sorties contigues
    void send();                                               // Envoyer le contenu de l'Arduino vers le(s) 74HC595
    int getState(int pin);                                     // Consulter l'état de la broche 'pin'
    String toString();                                         // Voir le contenu des 74HC595
	int lastPin();                                             // Dernière broche disponible 
  private:
    void sendToChips();                     // Envoyer le contenu de l'Arduino vers le(s) 74HC595
	void reverseSendToChips();              // Envoyer le contenu de l'Arduino vers le(s) 74HC595
	String byteToString(int data);          // Convertir les valeurs contenues dans un octet en chaîne de '0' et de '1'
    int MYarray[8] = {0,0,0,0,0,0,0,0};     // Le contenu des 64 broches en banques d'un octet
    int MYmask[8]= {1,2,4,8,16,32,64,128};  // Les puissances de deux pour les opérations binaires (bitwise operators)
    int MYchipCount;                        // Le nombre de 74HC595 du montage
    int MYlatchPin;                         // Broche du verrou
    int MYclockPin;                         // Broche de l'horloge
    int MYdataPin;                          // Broche de données
	int MYway = MSBF;                       // MSBFIRST (par défaut) ou LSBFIRST
	int MYlastPin;                          // Dernière broche disponible 
};

#endif
