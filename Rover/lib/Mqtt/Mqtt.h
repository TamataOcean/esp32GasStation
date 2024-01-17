#ifndef Mqtt_h
#define Mqtt_h

#include "Arduino.h"
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DallasTemperature.h>
#include <string>
#include <iostream>

using namespace std;


class Mqtt {
private:
    const char* ssid     = "GasStationAP";
    const char* password = "tamata50";
    const char* mqtt_input = "esp32/input";
    const char* mqtt_log = "esp32/log";
    const int ledPin = 4;
    WiFiClient espClient;


public:
  Mqtt();
  const char* mqtt_server = "172.24.1.1";
  const char* mqtt_output = "esp32/update";
  const char* mqtt_user = "SystemManagerTest";
  int timeInterval = 7500;
  void begin();
  void printAddress(DeviceAddress deviceAddress);
  void setup_wifi();
  void reconnect();
  void callback(char* topic, byte* message, unsigned int length);
  function<void(char*, byte*, unsigned int)> callbackFunction();
  PubSubClient client;
};

#endif