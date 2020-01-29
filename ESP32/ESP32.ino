/*
* Description:
* This sample code is mainly used to monitor sensorHub and sending through Mqtt Json data
* temperature, dissolved oxygen, ec and orp,etc.
*
* Software Environment: Arduino IDE 1.8.9
* Software download link: https://www.arduino.cc/en/Main/Software
*
* Install the library file：
* Copy the files from the github repository folder libraries to the libraries
* in the Arduino IDE 1.8.9 installation directory
*
* Hardware platform   : ESP32
*
* author  :  Rominco(rtourte@yahoo.fr)
* version :  V1.0
* date    :  2019-09-23
**********************************************************************
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

const char* ssid     = "OiO";
const char* password = "oceanisopen";
const char* mqtt_server = "172.24.1.1";
const char* mqtt_output = "esp32/update";
const char* mqtt_input = "esp32/input";
const char* mqtt_log = "esp32/log";

const int ledPin = 4;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

/* ------------------------
 *  MAIN SETUP 
 *  -----------------------
 */
void setup()
{
    Serial.begin(115200);
    delay(10);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    Serial.println("CCS811 begin");

    if(!ccs.begin()){
      Serial.println("Failed to start sensor! Please check your wiring.");
      //while(1);
  }
}

/* ------------------------
 *  MQTT CALLBACK
 *  -----------------------
 */
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/input, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == mqtt_input ) {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      client.publish(mqtt_log, "changing to ON" );
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      client.publish(mqtt_log, "changing to OFF" );
      digitalWrite(ledPin, LOW);
    }
  }
}

/* ----------------------
 *  WIFI SETUP 
 *  ---------------------
 */
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/* 
 *  ------------------
 *  RECONNECT MQTT
 *  ------------------
 */
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(mqtt_input);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/* 
 *  ------------------
 *  MAIN LOOP
 *  ------------------
 */
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    
    
    if(ccs.available()){
      if(!ccs.readData()){
        Serial.print("CO2: ");
        Serial.print(ccs.geteCO2());
        Serial.print("ppm, TVOC: ");
        Serial.println(ccs.getTVOC());

        String json = "{\"user\":\"GasStation\",\"CO2\":"+(String)ccs.geteCO2()+"\",\"TVOC\":\""+(String)ccs.getTVOC()+"\"}";

        client.publish(mqtt_output, json.c_str() );

      }
      else{
        Serial.println("ERROR!");
        //while(1);
      }
    }
  delay(500);

  }
}
