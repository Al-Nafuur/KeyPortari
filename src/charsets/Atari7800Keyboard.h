#pragma once

#include "../../PS2Keymaps.h"
#include "../../global.h"
#include <Arduino.h>

// 7800 Keyboard 'special' key values
#define INPT_5     11

#define D_0        SWCHA_0
#define D_1        SWCHA_1
#define D_2        SWCHA_2
#define BCLK       SWCHA_3
#define KCLK       INPT_5

#define SHIFT_KEYCODE     0x40
#define CONTROL_KEYCODE   0x80

#define HELP      PS2_F1
#define FUNC_2    PS2_F2
#define FUNC_3    PS2_F3
#define FUNC_4    PS2_F4
#define FUNC_5    PS2_F5

#define ESC       PS2_ESC
#define TAB       PS2_TAB
#define BSPACE    PS2_BACKSPACE
#define EOL       PS2_ENTER  /* EOL == Return Key? */
/* todo check all these.. */
#define ATARI     PS2_HOME   /* todo check for PS2 Start-key (ASCII) */
#define CAPS      PS2_END    /* todo check for PS2 Caps-lock key (ASCII) */
#define BREAK     PS2_PAGEUP
#define CLR       PS2_PAGEDOWN
#define SET       PS2_F6

struct Atari7800KeyboardKeyEntry {
  char    ascii;
  uint8_t keycode;
};

/*
                  7800 FRO-SYSTEM KEYBOARD TRANSLATION MATRIX
KEYPRESS    |   KEYCODE |   ATASCII ||  KEYPRESS    |   KEYCODE |   ATASCII
            |           |           ||              |           |
  no key    |     $00   |     ---   ||     ';'      |     $20   |     $3B
   '6'      |     $01   |     $36   ||     '3'      |     $21   |     $33
   'u'      |     $02   |     $75   ||     'p'      |     $22   |     $70
   'y'      |     $03   |     $79   ||     'e'      |     $23   |     $65
   '7'      |     $04   |     $37   ||     '0'      |     $24   |     $30
  BREAK     |     $05   |     ---   ||     'd'      |     $25   |     $64
   'n'      |     $06   |     $6E   ||     '.'      |     $26   |     $2E
  no key    |     $07   |     ---   ||     'c'      |     $27   |     $63
   'j'      |     $08   |     $6A   ||     '+'      |     $28   |     $2B
  HELP      |     $09   |     ---   ||     '2'      |     $29   |     $32
  func 2    |     $0A   |     ---   ||     '-'      |     $2A   |     $2D
  func 3    |     $0B   |     ---   ||     'w'      |     $2B   |     $77
  func 4    |     $0C   |     ---   ||     '<'      |     $2C   |     $3C
   'h'      |     $0D   |     $68   ||     's'      |     $2D   |     $73
   ' '      |     $0E   |     $20   ||     '/'      |     $2E   |     $2F
  func 5    |     $0F   |     ---   ||     'x'      |     $2F   |     $78
   'k'      |     $10   |     $6B   ||     '*'      |     $30   |     $2A
   '5'      |     $11   |     $35   ||     '1'      |     $31   |     $31
   'i'      |     $12   |     $69   ||     '='      |     $32   |     $3D
   't'      |     $13   |     $74   ||     'q'      |     $33   |     $71
   '8'      |     $14   |     $38   ||     '>'      |     $34   |     $3E
   'g'      |     $15   |     $67   ||     'a'      |     $35   |     $61
   'm'      |     $16   |     $6D   ||     ATARI    |     $36   |     ---
   'b'      |     $17   |     $62   ||     'z'      |     $37   |     $7A
   'l'      |     $18   |     $6C   ||    no key    |     $38   |     ---
   '4'      |     $19   |     $34   ||     ESC      |     $39   |     $1B
   'o'      |     $1A   |     $6F   ||     EOL      |     $3A   |     $9B
   'r'      |     $1B   |     $72   ||     TAB      |     $3B   |     $7F
   '9'      |     $1C   |     $39   ||    BSPACE    |     $3C   |     $7E
   'f'      |     $1D   |     $66   ||     CAPS     |     $3D   |     ---
   ','      |     $1E   |     $2C   ||    no key    |     $3E   |     ---
   'v'      |     $1F   |     $76   ||    no key    |     $3F   |     ---

*/

// move map to flash, if search is as fast as RAM? 
//const PROGMEM Atari7800KeyboardKeyEntry Atari7800KeyboardMap[] = {
static constexpr Atari7800KeyboardKeyEntry Atari7800KeyboardMap[] = {
  {  '6'      ,     0x01 },
  {  'u'      ,     0x02 },
  {  'y'      ,     0x03 },
  {  '7'      ,     0x04 },
  { BREAK     ,     0x05 },
  {  'n'      ,     0x06 },
  {  'j'      ,     0x08 },
  { HELP      ,     0x09 },
  { FUNC_2    ,     0x0A },
  { FUNC_3    ,     0x0B },
  { FUNC_4    ,     0x0C },
  {  'h'      ,     0x0D },
  {  ' '      ,     0x0E },
  { FUNC_5    ,     0x0F },
  {  'k'      ,     0x10 },
  {  '5'      ,     0x11 },
  {  'i'      ,     0x12 },
  {  't'      ,     0x13 },
  {  '8'      ,     0x14 },
  {  'g'      ,     0x15 },
  {  'm'      ,     0x16 },
  {  'b'      ,     0x17 },
  {  'l'      ,     0x18 },
  {  '4'      ,     0x19 },
  {  'o'      ,     0x1A },
  {  'r'      ,     0x1B },
  {  '9'      ,     0x1C },
  {  'f'      ,     0x1D },
  {  ','      ,     0x1E },
  {  'v'      ,     0x1F },
  {  ';'      ,     0x20 },
  {  '3'      ,     0x21 },
  {  'p'      ,     0x22 },
  {  'e'      ,     0x23 },
  {  '0'      ,     0x24 },
  {  'd'      ,     0x25 },
  {  '.'      ,     0x26 },
  {  'c'      ,     0x27 },
  {  '+'      ,     0x28 },
  {  '2'      ,     0x29 },
  {  '-'      ,     0x2A },
  {  'w'      ,     0x2B },
  {  '<'      ,     0x2C },
  {  's'      ,     0x2D },
  {  '/'      ,     0x2E },
  {  'x'      ,     0x2F },
  {  '*'      ,     0x30 },
  {  '1'      ,     0x31 },
  {  '='      ,     0x32 },
  {  'q'      ,     0x33 },
  {  '>'      ,     0x34 },
  {  'a'      ,     0x35 },
  {  ATARI    ,     0x36 },
  {  'z'      ,     0x37 },
  {  ESC      ,     0x39 },
  {  EOL      ,     0x3A },
  {  TAB      ,     0x3B },
  { BSPACE    ,     0x3C },
  {  CAPS     ,     0x3D },
// Uppercase is + SHIFT_KEYCODE set
  {  '&'      ,     0x01 + SHIFT_KEYCODE},
  {  'U'      ,     0x02 + SHIFT_KEYCODE},
  {  'Y'      ,     0x03 + SHIFT_KEYCODE},
  {  '\''     ,     0x04 + SHIFT_KEYCODE},
  {  'N'      ,     0x06 + SHIFT_KEYCODE},
  {  'J'      ,     0x08 + SHIFT_KEYCODE},
  {  'H'      ,     0x0D + SHIFT_KEYCODE},
  {  ' '      ,     0x0E + SHIFT_KEYCODE},
  {  'K'      ,     0x10 + SHIFT_KEYCODE},
  {  '%'      ,     0x11 + SHIFT_KEYCODE},
  {  'I'      ,     0x12 + SHIFT_KEYCODE},
  {  'T'      ,     0x13 + SHIFT_KEYCODE},
  {  '@'      ,     0x14 + SHIFT_KEYCODE},
  {  'G'      ,     0x15 + SHIFT_KEYCODE},
  {  'M'      ,     0x16 + SHIFT_KEYCODE},
  {  'B'      ,     0x17 + SHIFT_KEYCODE},
  {  'L'      ,     0x18 + SHIFT_KEYCODE},
  {  '$'      ,     0x19 + SHIFT_KEYCODE},
  {  'O'      ,     0x1A + SHIFT_KEYCODE},
  {  'R'      ,     0x1B + SHIFT_KEYCODE},
  {  'G'      ,     0x1C + SHIFT_KEYCODE},
  {  'F'      ,     0x1D + SHIFT_KEYCODE},
  {  '['      ,     0x1E + SHIFT_KEYCODE},
  {  'V'      ,     0x1F + SHIFT_KEYCODE},
  {  ':'      ,     0x20 + SHIFT_KEYCODE},
  {  '#'      ,     0x21 + SHIFT_KEYCODE},
  {  'P'      ,     0x22 + SHIFT_KEYCODE},
  {  'E'      ,     0x23 + SHIFT_KEYCODE},
  {  ')'      ,     0x24 + SHIFT_KEYCODE},
  {  'D'      ,     0x25 + SHIFT_KEYCODE},
  {  ']'      ,     0x26 + SHIFT_KEYCODE},
  {  'C'      ,     0x27 + SHIFT_KEYCODE},
  {  '\\'     ,     0x28 + SHIFT_KEYCODE},
  {  '"'      ,     0x29 + SHIFT_KEYCODE},
  {  '_'      ,     0x2A + SHIFT_KEYCODE},
  {  'W'      ,     0x2B + SHIFT_KEYCODE},
  {  '<'      ,     0x2C + SHIFT_KEYCODE},
  {  'S'      ,     0x2D + SHIFT_KEYCODE},
  {  '?'      ,     0x2E + SHIFT_KEYCODE},
  {  'X'      ,     0x2F + SHIFT_KEYCODE},
  {  '^'      ,     0x30 + SHIFT_KEYCODE},
  {  '!'      ,     0x31 + SHIFT_KEYCODE},
  {  '|'      ,     0x32 + SHIFT_KEYCODE},
  {  'Q'      ,     0x33 + SHIFT_KEYCODE},
  {  '>'      ,     0x34 + SHIFT_KEYCODE},
  {  'A'      ,     0x35 + SHIFT_KEYCODE},
  {  'Z'      ,     0x37 + SHIFT_KEYCODE},
  {  SET      ,     0x3B + SHIFT_KEYCODE},
// Special Control-Keys we can map:
  {  CLR              ,     0x3B + CONTROL_KEYCODE},
  {  PS2_UPARROW      ,     0x2A + CONTROL_KEYCODE},
  {  PS2_DOWNARROW    ,     0x32 + CONTROL_KEYCODE},
  {  PS2_LEFTARROW    ,     0x28 + CONTROL_KEYCODE},
  {  PS2_RIGHTARROW   ,     0x30 + CONTROL_KEYCODE}
};

/// Lookup function
inline const uint8_t getAtari7800KeyboardKeyEntry(char c) {
    for (const auto &e : Atari7800KeyboardMap) {
        if (e.ascii == c) {
            return e.keycode;
        }
    }
    return 0x00;
}
