#pragma once

#include "Protocol.h"

class ProtocolNone : public Protocol {
  public:
    void setup() override;
};