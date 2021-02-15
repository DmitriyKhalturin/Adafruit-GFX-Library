#ifndef _UTF8DECODER_H
#define _UTF8DECODER_H

#include "Arduino.h"

class Utf8Decoder {
public:
  Utf8Decoder() : state(0), buffer(0) {}

  // Serial UTF-8 decoder
  uint16_t decode(uint8_t c);

protected:
  uint8_t state = 0; /// UTF-8 decoder state
  uint16_t buffer;   /// Unicode code-point buffer
};

#endif // _UTF8DECODER_H
