#pragma once

#include "Protocol.h"
#include "../charsets/Atari7800Keyboard.h"

class ProtocolAtari7800Keyboard : public Protocol {
  private:
    volatile uint8_t my_current_keycode;
  public:
    void setup() override;
    void keyDown(char value) override;
    void keyUp() override;
    void loop() override;
    void pISR() override;
};
