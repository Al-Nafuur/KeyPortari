#pragma once

#include "Protocol.h"

class ProtocolASCII : public Protocol {
  public:
    void setup() override;
    void keyDown(char value) override;
    void keyUp() override;
};
