#pragma once

#include "Protocol.h"
#include "../charsets/BasicProgramming.h"

class ProtocolBasicProgramming : public Protocol {
  private:
    KeyColor _currentColor;
    static void WaitForPinState(uint8_t pin, uint8_t state);
    void Write(uint8_t scanPin, uint8_t outputPin);
    void SwitchColor();
  public:
    void setup() override;
    void keyDown(char value) override;
};
