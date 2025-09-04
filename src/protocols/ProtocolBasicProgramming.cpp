/*
 * This protocol is "inspired by"
 * https://github.com/SteveGuidi/video-companion-media/tree/main/2021.06.09%20-%20Atari%202600%20Keyboard
*/

#include "ProtocolBasicProgramming.h"


static void ProtocolBasicProgramming::WaitForPinState(uint8_t pin, uint8_t state) {
  while(digitalRead(pin) != state) { }
}

void ProtocolBasicProgramming::Write(uint8_t scanPin, uint8_t outputPin) {
  
  // Wait for the scanning pin transisitions before setting the corresponding
  // output pin state.  Restore the output pin to the HIGH state when completed.
  uint8_t i(0);
  while(i++ < 2 || !keyboard_action) { // do as long as key is not released, but at least twice
//  for(uint8_t i(0); i <= 4; ++i) { // 8 scan cycles should be enough for key
    WaitForPinState(scanPin, HIGH);
    digitalWrite(outputPin, HIGH);
    WaitForPinState(scanPin, LOW);
    digitalWrite(outputPin, LOW);
  }
  
  digitalWrite(outputPin, HIGH);
  keyboard_action = false; // toDo should be  done in main loop
};

void ProtocolBasicProgramming::SwitchColor() {
  // Wait for the scanning pin transisitions before setting the corresponding
  // output pin state.  Restore the output pin to the HIGH state when completed.
  for(uint8_t i = 0; i <= 2; ++i) { // 3 scan cycles should be enough for inc color
    WaitForPinState(COLOR_KEY_SCAN_PIN, HIGH);
    digitalWrite(COLOR_KEY_OUTPUT_PIN, HIGH);
    WaitForPinState(COLOR_KEY_SCAN_PIN, LOW);
    digitalWrite(COLOR_KEY_OUTPUT_PIN, LOW);
  }
  digitalWrite(COLOR_KEY_OUTPUT_PIN, HIGH);
};

void ProtocolBasicProgramming::setup(){
  // disable joystick port forwarding
  digitalWrite(OE_LEFT_PORT, LOW);
  digitalWrite(OE_RIGHT_PORT, LOW);

  // set port on RIOT bus to input.
  DDRD = 0b00000000;
  PORTD = 0b00000000; // no pullups
//  PORTD = 0b11111111; // activate pullups
  pinMode(INPT_0, OUTPUT);
  digitalWrite(INPT_0, HIGH);
  pinMode(INPT_1, OUTPUT);
  digitalWrite(INPT_1, HIGH);
  pinMode(INPT_2, OUTPUT);
  digitalWrite(INPT_2, HIGH);
  pinMode(INPT_3, OUTPUT);
  digitalWrite(INPT_3, HIGH);
  pinMode(INPT_4, OUTPUT);
  digitalWrite(INPT_4, HIGH);
  pinMode(INPT_5, OUTPUT);
  digitalWrite(INPT_5, HIGH);

  _currentColor = KeyColor::White;
}

//void protocol_parallel_both_BasicProgramming_keyUp(){
// nothing to do here, we are using the global "keyboard_action"
// to end the key press
//}

void ProtocolBasicProgramming::keyDown(char value){
    const KeyControllerEntry* entry = getKeyControllerEntry(value);
    if (!entry) return;

    // EnsureColor of Controller
    while ((_currentColor & entry->color) != _currentColor) {
      SwitchColor(); // Write(SWCHA_7, INPT_1);
      _currentColor = next(_currentColor);
    }

    // now signal the key pressed
    Write(entry->scanPin , entry->outPin);

}