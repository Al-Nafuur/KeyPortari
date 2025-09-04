/*
 from stella/src/emucore/CartCM.hxx
     SWCHA: D7 = Audio input from tape player
           D6 = Audio out to tape player and 4017 CLK
                1 -> increase key column (0 to 9)
           D5 = 4017 RST, and RAM direction. (high = write, low = read)
                1 -> reset key column to 0 (if D4 = 0)
                0 -> enable RAM writing (if D4 = 1)
           D4 = RAM enable: 1 = disable RAM, 0 = enable RAM
           D3 = keyboard row 3 input (0 = key pressed)
           D2 = keyboard row 1 input (0 = key pressed)
           D1 = bank select high bit
           D0 = bank select low bit

    INPT0: D7 = FUNC key input (0 on startup / 1 = key pressed)
    INPT1: D7 = always HIGH input (pulled high thru 20K resistor)
    INPT2: D7 = always HIGH input (pulled high thru 20K resistor)
    INPT3: D7 = SHIFT key input (0 on startup / 1 = key pressed)
    INPT4: D7 = keyboard row 0 input (0 = key pressed)
    INPT5: D7 = keyboard row 2 input (0 = key pressed)
*/

#include "ProtocolCompuMate.h"

#define RAM _BV(PD4)
#define RST _BV(PD5)


void ProtocolCompuMate::setup() {
  // disable joystick port forwarding
  digitalWrite(OE_LEFT_PORT, LOW);
  digitalWrite(OE_RIGHT_PORT, LOW);

  // set port on RIOT bus to input/output.
  DDRD = 0b00001100;
  PORTD = 0b00001100; // inputs no pullups, outputs high
//  PORTD = 0b11111111; // activate pullups

  pinMode(INPT_0, OUTPUT);
  digitalWrite(INPT_0, LOW); // FUNC Key
  pinMode(INPT_1, OUTPUT);
  digitalWrite(INPT_1, HIGH);
  pinMode(INPT_2, OUTPUT);
  digitalWrite(INPT_2, HIGH);
  pinMode(INPT_3, OUTPUT);
  digitalWrite(INPT_3, LOW); // Shift key
  pinMode(INPT_4, OUTPUT);
  digitalWrite(INPT_4, HIGH); // row 0
  pinMode(INPT_5, OUTPUT);
  digitalWrite(INPT_5, HIGH); // row 2

  my_4017_counter = 0;

  cli();                    // globale Interrupts aus
  PCICR |= _BV(PCIE2);      // Pin-Change-Interrupts auf Port D aktivieren
  PCMSK2 |= _BV(PCINT21)    // nur PD5 (PCINT21)
         |  _BV(PCINT22);   // und PD6 (PCINT22) maskieren
  sei();                    // globale Interrupts an
}

void ProtocolCompuMate::keyDown(char value){
  uint8_t i = 0;

  const CompuMateKeyEntry* entry = getCompuMateKeyEntry(value);
  if (!entry) return;

  if(entry->shift){
      digitalWrite(INPT_3, HIGH); // Press SHIFT key
  }
  if(entry->func){
      digitalWrite(INPT_0, HIGH); // Press FUNC key
  }
//  while(i++ < 2 || !keyboard_action) { // do as long as key is not released, but at least two scans
  while(i++ < 4 ) { // do for 4 column scans
    while(my_4017_counter != entry->column) {}
    digitalWrite(entry->row, LOW);
//    while(my_4017_counter == entry->column) {} //&& !keyboard_action) {}
    // Wait for 4017 reset on SWCHA_6
    // The compuMate ROM resets the 4017 if he has found a pressd key?
    // while (!(PIND & _BV(PD5))) { /* no-op */ } // wait for RST PD5 going high
    // while (!(PIND & _BV(PD6))) { /* no-op */ } // wait for CLK PD6 LOW→HIGH
    while (!(PIND & RST) || !(PIND & RAM)) { /* no-op */ }
  //    b) dann bis PD5==0 oder PD4==0, das Ende der Column
//    while  ((PIND & RST) &&  (PIND & RAM)) { /* no-op */ }

    digitalWrite(entry->row, HIGH);
  }
  if(entry->shift){
    digitalWrite(INPT_3, LOW); // Release SHIFT key
  }
  if(entry->func){
    digitalWrite(INPT_0, LOW); // Release FUNC key
  }
//  keyboard_action = false; // toDo should be done in main loop

}

void ProtocolCompuMate::pISR() {
  static bool last5 = false, last6 = false;
  uint8_t currPortD = PIND;         // Port-D-Pins einlesen

  // PD5: SWCHA Bit 5
  bool now5  = currPortD & _BV(PD5);
  if (!last5 && now5 && (currPortD & _BV(PD4))) {
      my_4017_counter = 0;
  }

  // PD6: SWCHA Bit 6
  bool now6  = currPortD & _BV(PD6);
  if (!last6 && now6 && !now5){
    if(++my_4017_counter > 9){
      my_4017_counter = 0;
    }
  }

  last5 = now5;
  last6 = now6;
}