#pragma once

#include "Protocol.h"
#include "../charsets/24char.h"

class Protocol24char : public Protocol {
  public:
    void setup() override;
    void keyDown(char value) override;
    void keyUp() override;
};
