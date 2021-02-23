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
#include "SparkFunBME280.h"

BME280 sensorBME280;
Adafruit_CCS811 ccs;

// const char* ssid     = "OiO";
// const char* password = "oceanisopen";
// const char* mqtt_server = "172.24.1.1";

const char* ssid     = "WifiRaspi";
const char* password = "wifiraspi";
const char* mqtt_server = "172.24.1.1";
const char* mqtt_output = "esp32/update";
const char* mqtt_input = "esp32/input";
const char* mqtt_log = "esp32/log";
const char* mqtt_user = "ESP32_TEST";

const int ledPin = 4;
int timeInterval = 7500;

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
    Serial.begin(9600);
    delay(10);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);


    Serial.println("CCS811 begin");
    if(!ccs.begin(0x5A)){
      Serial.println("Failed to start sensor! Please check your wiring.");
      while(1);
    }
    else
    {
      Serial.println("CCS811 started");
    }


    Serial.println("BME280 begin");
    // I2C device found at address 0x76
    Wire.begin();
    if (sensorBME280.beginI2C() == false) //Begin communication over I2C
    {
      Serial.println("The sensor did not respond. Please check wiring.");
      while(1); //Freeze
    }
    else
    {
      Serial.println("BME280 started & configured");

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
      Serial.println("MessageTemp = on");
      client.publish(mqtt_log, "changing to ON" );
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "Message Temp = off"){
      Serial.println("off");
      client.publish(mqtt_log, "changing to OFF" );
      digitalWrite(ledPin, LOW);
    }
    else if(messageTemp == "timeInterval_1000") {
      Serial.println("Time Interval order received");
      timeInterval = 1000;
      client.publish(mqtt_log, "Interval set to 1000" );
    }
    else if(messageTemp == "timeInterval_5000") {
      Serial.println("Time Interval order received");
      timeInterval = 5000;
      client.publish(mqtt_log, "Interval set to 5000" );
    }

    else if(messageTemp == "reboot") {
      Serial.println("Reboot order received");
      String msg = "Reboot for : " + (String)mqtt_user;
      client.publish(mqtt_log, msg.c_str() );
      ESP.restart();
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
    delay(100);
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
      delay(3000);
    }
  }
}

/* 
 *  ------------------
 *  MAIN LOOP
 *  ------------------
 */
void loop() {
  
  long now = millis();
  if (now - lastMsg > timeInterval ) {
    lastMsg = now;
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
  
    Serial.print("Humidity: ");
    Serial.print(sensorBME280.readFloatHumidity(), 0);
    
    Serial.print(" Pressure: ");
    Serial.print(sensorBME280.readFloatPressure(), 0);
    
    Serial.print(" Alt: ");
    Serial.print(sensorBME280.readFloatAltitudeMeters(), 1);
    
    Serial.print(" Temp: ");
    Serial.print(sensorBME280.readTempC(), 2);
    
    Serial.println();

    if(ccs.available()){
      if(!ccs.readData()){
        Serial.print("CO2: ");
        Serial.print(ccs.geteCO2());
        Serial.print("ppm, TVOC: ");
        Serial.println(ccs.getTVOC());
        // String json = "{\"user\":\""+(String)mqtt_user+"\",\"Humidity\":\""+(String)sensorBME280.readFloatHumidity()+"\",\"Pressure\":\""+(String)sensorBME280.readFloatPressure()+"\",\"Altitude\":\""+(String)sensorBME280.readFloatAltitudeMeters()+"\",\"Temperature\":\""+(String)sensorBME280.readTempC()+"\"}";
        String json = "{\"user\":\""+(String)mqtt_user+"\",\"CO2\":\""+(String)ccs.geteCO2()+"\",\"TVOC\":\""+(String)ccs.getTVOC()+"\",\"Humidity\":\""+(String)sensorBME280.readFloatHumidity()+"\",\"Pressure\":\""+(String)sensorBME280.readFloatPressure()+"\",\"Altitude\":\""+(String)sensorBME280.readFloatAltitudeMeters()+"\",\"Temperature\":\""+(String)sensorBME280.readTempC()+"\"}";
        client.publish(mqtt_output, json.c_str() );
        //client.disconnect();

        Serial.println("Mqtt sent to : " + (String)mqtt_output );
        Serial.println(json);
      }
      else{
        String errorMsg = "ERROR on CCS811 !";
        String logType = "ERROR";
        String json = "{\"user\":\""+(String)mqtt_user +"\",\"logType\":\""+logType+"\",\"logMessage\":\""+errorMsg +"\"}";
        client.publish(mqtt_log, json.c_str() );
        //client.disconnect();

        // Serial.println("Mqtt sent to : " + (String)mqtt_log );
        // Serial.println(json);
        // //while(1);
        // Serial.println("Restarting... ");
        // //ESP.restart();
      }
    }
  delay(500);

  }
}
