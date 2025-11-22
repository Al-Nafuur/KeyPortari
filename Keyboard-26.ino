/*

*/

#include "PS2Keymaps.h"
#include "global.h"
#include "src/protocols/Protocol.h"
#include "src/protocols/ProtocolNone.h"
#include "src/protocols/Protocol24char.h"
#include "src/protocols/ProtocolBasicProgramming.h"
#include "src/protocols/ProtocolCompuMate.h"
#include "src/protocols/ProtocolAtari7800Keyboard.h"
#include "src/protocols/ProtocolASCII.h"


PS2Keymap_t *keymap;

static ProtocolNone              protocolNone;
static Protocol24char            protocol24char;
static ProtocolBasicProgramming  protocolBasicProgramming;
static ProtocolCompuMate         protocolCompuMate;
static ProtocolAtari7800Keyboard protocolAtari7800Keyboard;
static ProtocolASCII             protocolASCII;

Protocol* protocols[] = { &protocolNone, &protocol24char, &protocolBasicProgramming, &protocolCompuMate, &protocolAtari7800Keyboard, &protocolASCII };

volatile Protocol* activeProtocol = nullptr;

enum InitState {
  INIT_IDLE,
  INIT_WAIT_FOR_FFFF,
  INIT_WAIT_FOR_ZERO_AGAIN,
  INIT_WAIT_FOR_PROTOCOL
};

typedef struct {
  int adc_threshold;
  uint8_t id;
} AdcMapping;

const AdcMapping adc_mappings[] PROGMEM = {
  {  52, 15}, { 55,  7}, { 59, 11},
  {  64,  3}, { 70, 13}, { 77,  5},
  {  86,  9}, { 97,  1}, {111, 14},
  { 129,  6}, {154, 10}, {192,  2},
  { 253, 12}, {373,  4}, {739,  8},
  {1024, 0}
};

void set_right_nibble(char value){
  // this might be moved to a protocol later
  // 1. set right SN74HC4066 to OE off !
  // 2. set right data port to output
  // 3. set right data port to keyvalue
  digitalWrite(OE_RIGHT_PORT, LOW);
  DDRD = 0b00001111;
  PORTD = value & 0x0F;
}

uint8_t map_adc_value(int adc_value) {
  int i = 0;
  while (i < 16 && pgm_read_word(&adc_mappings[i].adc_threshold) < adc_value ) {
      i++;
  }
  return pgm_read_byte(&adc_mappings[i].id); 
}

void setup() {

  #if DEBUG
  Serial.begin(115200);
  #endif

  pinMode(CLOCK, INPUT_PULLUP); // For most keyboards the builtin pullups are sufficient, so the 10k pullups can be omitted
  pinMode(DATA, INPUT_PULLUP);
  pinMode(OE_LEFT_PORT, OUTPUT);
  pinMode(OE_RIGHT_PORT, OUTPUT);
  // Disable joystick forwarding via both 74HC4066 (protocol setup may enable it later)
  digitalWrite(OE_LEFT_PORT, LOW);
  digitalWrite(OE_RIGHT_PORT, LOW);

  bitSet(PCICR, PCIE0);   // Enable pin change interrupts on pin B0-B7
  bitSet(PCMSK0, PCINT1); // Pin change interrupt on Clock pin (PCINT1 = PB1 Arduino Pin 9)

  int adcValue = analogRead(DIP_A_PIN);  // Read voltage of DIP-Switch block resistor ladder (0-1023)
  uint8_t dipConfig = map_adc_value(adcValue); 

  switch (dipConfig & 0b01) { // lower bit of dipConfig define keyboard layout
    case 0b01: keymap = &PS2Keymap_German;      break;
//    case 0b10: keymap = &PS2Keymap_French;      break;
    default: keymap = &PS2Keymap_US;            break;
  }

  uint8_t apId = (dipConfig >> 1) & 0b111;
  activeProtocol = protocols[apId];

  #if DEBUG
  Serial.println("Keyboard test");
  Serial.println(adcValue);
  Serial.println(dipConfig);
  #else
  activeProtocol->setup();
  #endif
}

volatile uint8_t curscan = 0;
volatile bool keyboard_action = false;

ISR(PCINT0_vect) {
  uint16_t newscan = 0;
  for(int i = 0; i<11; i++) {
    while(digitalRead(CLOCK));
    newscan |= digitalRead(DATA) << i;
    while(!digitalRead(CLOCK));
  }
  newscan >>= 1;
  newscan &= 0xFF;
  curscan = newscan;
  keyboard_action = true;
  bitSet(PCIFR, PCIF0);
}


ISR(PCINT2_vect) {
  // Pin change interrupts on pin D0-D7 are enabled in protocol setup!
  activeProtocol->pISR();
  // Delete interrupt-flag for port D
  bitSet(PCIFR, PCIF2);
}


void loop() {
 	static uint8_t keyboard_state = 0, lastscan = 0;
//  static InitState initState = INIT_IDLE;
  static unsigned long initTimer = 0;

  char c;

  if(keyboard_action){
    keyboard_action = false;
    if(curscan != 0xF0 && curscan != 0xE0){
      if (curscan < PS2_KEYMAP_SIZE){
        if (keyboard_state & SHIFT) {
          c = pgm_read_byte(keymap->shift + curscan);
        } else if ((keyboard_state & ALTGR) && keymap->uses_altgr) {
          c = pgm_read_byte(keymap->altgr + curscan);
        } else {
          c = pgm_read_byte(keymap->noshift + curscan);
        }
      }

      if(lastscan == 0xF0){
        if (curscan == 0x12 || curscan == 0x59) {
          keyboard_state &= ~SHIFT;
        } else if (curscan == 0x11 && (keyboard_state & MODIFIER)) {
          keyboard_state &= ~ALTGR;
        } else {
          // Key up
          #if DEBUG
          Serial.print((int)c);
          Serial.println(" up");
          #else
          activeProtocol->keyUp();
          #endif
        }
        // CTRL, ALT & WIN keys could be added
        // but is that really worth the overhead?
        keyboard_state &= ~MODIFIER;
      }else{
        if (curscan == 0x12 || curscan == 0x59) {
          keyboard_state |= SHIFT;
        } else if (curscan == 0x11 && (keyboard_state & MODIFIER)) {
          keyboard_state |= ALTGR;
        } else {
          if(lastscan == 0xE0){ // MODIFIER
            switch (curscan) {
              case 0x70: c = PS2_INSERT;      break;
              case 0x6C: c = PS2_HOME;        break;
              case 0x7D: c = PS2_PAGEUP;      break;
              case 0x71: c = PS2_DELETE;      break;
              case 0x69: c = PS2_END;         break;
              case 0x7A: c = PS2_PAGEDOWN;    break;
              case 0x75: c = PS2_UPARROW;     break;
              case 0x6B: c = PS2_LEFTARROW;   break;
              case 0x72: c = PS2_DOWNARROW;   break;
              case 0x74: c = PS2_RIGHTARROW;  break;
              case 0x4A: c = '/';             break;
              case 0x5A: c = PS2_ENTER;       break;
              default: break;
            }
          }
          #if DEBUG
          Serial.print((int)c);
          Serial.println(" down");
          #else
          activeProtocol->keyDown(c);
          #endif
        }
        keyboard_state &= ~MODIFIER;
      }
    }
    lastscan = curscan;
  }else{
    activeProtocol->loop();
/* // todo check active protocol is "soft" switchable
    uint8_t busState = PIND & 0x0F;
    switch (initState) {
      case INIT_IDLE:
        if (busState == 0) {
          initState = initState + 1;
          initTimer = millis();
        }
        break;

      case INIT_WAIT_FOR_FFFF:
        if (busState == 0b1111) {
          initState = initState + 1;
        }
        break;

      case INIT_WAIT_FOR_ZERO_AGAIN:
        if (busState == 0) {
          initState = initState + 1;
        }
        break;

      case INIT_WAIT_FOR_PROTOCOL:
        if (busState != 0) {
          apId = busState;
          initState = INIT_IDLE;

          delay(17);                        // wait one 60Hz-Frame
          set_right_nibble(apId); // return activeprotocol-Id for confirmation on the bus
          delay(34);                        // wait two more frames
          protocol_parallel_both_24char_keyUp();
        }
        break;
    }

    // Timeout protection
    if (initState != INIT_IDLE && (millis() - initTimer > 1000)) {
      initState = INIT_IDLE;
    }
*/
  }
}
