#ifndef Light_h
#define Light_h

#include "Arduino.h"
#include "Wire.h"


class Light {
public:
  void begin();
  float readLux();
  #define address 0x23

private:
  uint8_t buf[4] = {0};
  uint16_t data;
  float Lux;
  uint8_t readReg(uint8_t reg, const void* pBuf, size_t size);
};

#endif