#include "ProtocolNone.h"

void ProtocolNone::setup() {
  digitalWrite(OE_LEFT_PORT, HIGH);  // Activate left joystick forwarding via first 74HC4066
  digitalWrite(OE_RIGHT_PORT, HIGH); // Activate right joystick forwarding via second 74HC4066
}