#include <Arduino.h>
#include <stdint.h>

namespace BM {
  #define BM_Satellite_H (9)
  #define BM_Satellite_W (9)

  static const uint8_t PROGMEM Satellite[] = {
    0b01110000, 0b00000000,
    0b10000010, 0b00000000,
    0b10110101, 0b00000000,
    0b10100010, 0b10000000,
    0b00001101, 0b00000000,
    0b00101100, 0b00000000,
    0b01010000, 0b00000000,
    0b00101000, 0b00000000,
    0b00010000, 0b00000000
  };
}

