#include "Light.h"

void Light::begin() {
  Wire.begin();
}

float Light::readLux() {
  readReg(0x10, buf, 2);
  data = buf[0] << 8 | buf[1];
  Lux = static_cast<float>(data) / 1.2;
  return Lux;
}

uint8_t Light::readReg(uint8_t reg, const void* pBuf, size_t size) {
  if (pBuf == NULL) {
    Serial.println("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  Wire.beginTransmission(address);
  Wire.write(&reg, 1);
  if (Wire.endTransmission() != 0) {
    return 0;
  }
  delay(20);
  Wire.requestFrom(address, (uint8_t)size);
  for (uint16_t i = 0; i < size; i++) {
    _pBuf[i] = Wire.read();
  }
  return size;
}