#pragma once

#include "Protocol.h"
#include "../charsets/CompuMate.h"

class ProtocolCompuMate : public Protocol {
  private:
    volatile uint8_t my_4017_counter;
  public:
    void setup() override;
    void keyDown(char value) override;
    void pISR() override;
};
