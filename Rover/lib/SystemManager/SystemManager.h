#ifndef SystemManager_h
#define SystemManager_h

#include <Arduino.h>
#include <ctime>
#include <ArduinoJson.h>
#include "Mqtt.h"
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DallasTemperature.h>
#include <string>
#include <iostream>
#include <NTPClient.h>
#include <WiFiUdp.h>

class SystemManager
{
    public:
        void init();
        void loop();
        String getBoard();
        String getMAC();
        String getJsonInfo();
        String JSONgenerate();
        void publishJson();
        WiFiClient espClient;


    private:
        String board;
        String MAC;
        String jsonInfo;
        Mqtt mqttClient;
        void merge(JsonObject &dest, JsonObjectConst src);
};
#endif