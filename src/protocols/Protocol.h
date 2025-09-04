#pragma once

#include <Arduino.h>
#include "../../global.h"

class Protocol {
  public:
    virtual void setup();
    virtual void keyDown(char value);
    virtual void keyUp();
    virtual void loop();
    virtual void pISR();
    virtual ~Protocol();
};