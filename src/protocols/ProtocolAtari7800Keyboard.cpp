/*
*/

#include "ProtocolAtari7800Keyboard.h"

#define COM_RETURN             0b111
#define COM_SCAN_KEYBOARD      0b000
#define COM_SIO_OPERATION      0b001
#define COM_PROGRAM_RECORDER   0b010
#define COM_CASSETTE_RECORDER  0b011

ProtocolAtari7800Keyboard::Node ProtocolAtari7800Keyboard::nodes[] = {
  /* 0 */ { 0, true, {  1, 2, 3, 4,-1,-1,-1 }, nullptr },           // ROOT

  // ROOT folder commands and subfolders
  /* 1 */ { 0, true, {  5, 6,-1,-1,-1,-1,-1 }, nullptr },           // KEYBOARD-SCAN
  /* 2 */ { 0, true, { -1,-1,-1,-1,-1,-1,-1 }, nullptr },           // SIO-OPERATIONS
  /* 3 */ { 0, true, { -1,-1,-1,-1,-1,-1,-1 }, nullptr },           // PROGRAM RECORDER
  /* 4 */ { 0, true, { -1,-1,-1,-1,-1,-1,-1 }, nullptr },           // CASSETTE RECORDER

  // KEYBOARD commands and subfolders
  /* 4 */ { 1, false, { -1,-1,-1,-1,-1,-1,-1 }, &ProtocolAtari7800Keyboard::cmd_GET_KEY },   // GET-KEY (Command)
  /* 5 */ { 1, false, { -1,-1,-1,-1,-1,-1,-1 }, &ProtocolAtari7800Keyboard::cmd_GET_STATE }  // GET-STATE (Command)

};

void ProtocolAtari7800Keyboard::cmd_GET_KEY() {
  sendResponse(my_current_keycode);
}
void ProtocolAtari7800Keyboard::cmd_GET_STATE() { sendResponse(0x00); }

void ProtocolAtari7800Keyboard::sendResponse(uint8_t value) {

}

void ProtocolAtari7800Keyboard::setup() {
  // disable joystick port forwarding (left)
  digitalWrite(OE_LEFT_PORT, LOW);

  // set port on RIOT bus to input/output.
  DDRD = 0b00000000;
  PORTD = 0b00000000; // inputs no pullups, outputs high
//  PORTD = 0b11111111; // activate pullups

  pinMode(KCLK, OUTPUT);
  digitalWrite(KCLK, HIGH); // KCLK

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
  if (current_command != 0xff){
    if (current_command == 0b111){
      current_node = nodes[current_node].parent;
    } else {
      uint8_t new_node = nodes[current_node].children[current_command];
      if (new_node == -1){
        // Not implemented yet!!
      } else if (nodes[new_node].isFolder){
        current_node = new_node;
      } else {
        // Base-Unit really want something from us now..
        (this->*nodes[new_node].handler)();
      }
    }

    PINB = (1 << PB3);  // Toggle Bit 3 of Port B (KCLK) to tell Base-Unit we are done and ready.
    current_command = 0xff;
  }
}

void ProtocolAtari7800Keyboard::pISR() {
  // Base-Unit toggled BCLK
  switch (my_transfer_state){
    case WAIT_FOR_CMD:
      current_command = PIND & 0b111;
      break;
    case TRANSFER_BYTE_BIT3_5:
      my_transfer_state = TRANSFER_BYTE_BIT6_7;
      break;
    case TRANSFER_BYTE_BIT6_7:
      my_transfer_state = WAIT_FOR_CMD;
      break;
  }
}
