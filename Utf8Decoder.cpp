#include "Utf8Decoder.h"

/**************************************************************************/
/*!
    @brief  Serial UTF-8 decoder
    @param  c  8 bit value from encoded stream
    @returns   0 if decoding is not complete yet, 16 bit code point
               otherwise. Can cast to 8 bits for ASCII range (0-255)
*/
/**************************************************************************/
uint16_t Utf8Decoder::decode(uint8_t c) {
  if (state > 0) {
    if ((c >> 6) == 0x2) {  // 10XX'XXXX
      buffer = (buffer << 6) | (c & ((1 << 6) - 1));
      --state;
      return (state == 0) ? 1 : 0;
    }
  } else {
    if ((c >> 7) == 0x0) {  // 0XXX'XXXX
      buffer = c;
      return 1;
    }
    if ((c >> 5) == 0x6) {  // 110X'XXXX
      buffer = (c & ((1 << 5) - 1));
      state = 1;
      return 0;
    }
    if ((c >> 4) == 0xE) {  // 1110'XXXX
      buffer = (c & ((1 << 4) - 1));
      state = 2;
      return 0;
    }
  }

  // error, but retain buffer 'c'
  state = 0;
  buffer = c;
  return -1;
}
