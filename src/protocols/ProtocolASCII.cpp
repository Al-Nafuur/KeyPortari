#include "ProtocolASCII.h"

void ProtocolASCII::setup(){
  digitalWrite(OE_LEFT_PORT, HIGH);  // Activate left joystick forwarding via first 74HC4066
  digitalWrite(OE_RIGHT_PORT, HIGH); // Activate right joystick forwarding via second 74HC4066
}

void ProtocolASCII::keyUp(){
  // set port on RIOT bus to input. Also used on init!
  DDRD = 0b00000000;
  PORTD = 0b00000000; // floating, no pullups
  digitalWrite(OE_LEFT_PORT, HIGH);
  digitalWrite(OE_RIGHT_PORT, HIGH);
}

void ProtocolASCII::keyDown(char value){
  // Key down for
  // 1. set both SN74HC4066 to OE off!
  // 2. set data Port to output
  // 3. set data Port to keyvalue
  digitalWrite(OE_LEFT_PORT, LOW);
  digitalWrite(OE_RIGHT_PORT, LOW);
  
  #if DEBUG
  Serial.print(value);
  Serial.println(" down");
  #else
  DDRD = 0b11111111;
  // todo mapping/protocol specific
  PORTD = value;
  #endif
}