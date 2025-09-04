/*
*/

#include "ProtocolAtari7800Keyboard.h"

void ProtocolAtari7800Keyboard::setup() {
  // disable joystick port forwarding (left)
  digitalWrite(OE_LEFT_PORT, LOW);

  // set port on RIOT bus to input/output.
  DDRD = 0b00000000;
  PORTD = 0b00000000; // inputs no pullups, outputs high
//  PORTD = 0b11111111; // activate pullups

  pinMode(INPT_5, OUTPUT);
  digitalWrite(INPT_5, HIGH); // KCLK

  cli();                    // globale Interrupts aus
  PCICR |= _BV(PCIE2);      // Pin-Change-Interrupts auf Port D aktivieren
  PCMSK2 = _BV(PCINT19);    // only PD3 (BCLK) enabled
  sei();                    // globale Interrupts an

}

void ProtocolAtari7800Keyboard::keyDown(char value) {
  my_current_keycode = getAtari7800KeyboardKeyEntry(value);
}

void ProtocolAtari7800Keyboard::keyUp() {
  my_current_keycode = 0x00;
}

void ProtocolAtari7800Keyboard::loop() {
    // Periodische Logik für ProtoA
}

void ProtocolAtari7800Keyboard::pISR() {
    // ISR-spezifische Logik für ProtoA
}
