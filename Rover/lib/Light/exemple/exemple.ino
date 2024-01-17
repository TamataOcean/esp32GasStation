#include "Light.h"

Light capteur;

void setup() {
  Serial.begin(115200);
  capteur.begin();
}

void loop() {
  float lux = capteur.readLux();
  Serial.print("LUX:");
  Serial.print(lux);
  Serial.print("lx");
  Serial.print("\n");
  delay(500);
}
