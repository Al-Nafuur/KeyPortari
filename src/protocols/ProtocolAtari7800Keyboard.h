#pragma once

#include "Protocol.h"
#include "../charsets/Atari7800Keyboard.h"

//typedef void (*CmdHandler)(void);

class ProtocolAtari7800Keyboard : public Protocol {
  private:

    typedef void (ProtocolAtari7800Keyboard::*CmdHandler)(void);

    enum TxStates {
      WAIT_FOR_CMD,
      TRANSFER_BYTE_BIT0_2,
      TRANSFER_BYTE_BIT3_5,
      TRANSFER_BYTE_BIT6_7
    };

    typedef struct {
      uint8_t parent;
      bool isFolder;
      uint8_t children[7];   // 0..6 Childs
      CmdHandler handler;   // != NULL -> Command
    } Node;

    uint8_t current_command = 0xff;
    uint8_t current_node = 0;
    TxStates my_transfer_state = WAIT_FOR_CMD;
    static Node nodes[];
    volatile uint8_t my_current_keycode;
    void sendResponse(uint8_t value);
  public:
    void cmd_GET_KEY();
    void cmd_GET_STATE();
    void setup() override;
    void keyDown(char value) override;
    void keyUp() override;
    void loop() override;
    void pISR() override;
};
