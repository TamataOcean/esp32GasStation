#include <Arduino.h>

// SystemManager :
#include "SystemManager.h"
SystemManager systemManager;

// MQTT : 
#include "Mqtt.h"
Mqtt mqtt;
#include "PubSubClient.h"
WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  Serial.begin(9600);
  systemManager.init();
}

void loop() {
    client.loop();
    systemManager.loop();
    //Serial.println(systemManager.getJsonInfo());


    delay(20000);

}