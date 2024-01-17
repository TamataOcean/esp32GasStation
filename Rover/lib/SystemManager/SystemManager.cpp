#include "SystemManager.h"
#include "conf.h"

void SystemManager::init(){
    this->board = boardConf;
    this->MAC = MACconf;
    this->mqttClient.begin();
    this->mqttClient.client = PubSubClient(this->espClient);
    this->mqttClient.setup_wifi();
}
void SystemManager::loop(){
    SystemManager::JSONgenerate();
    this->publishJson();
}
String SystemManager::getBoard(){
    return this->board;
}
String SystemManager::getMAC(){
    return this->MAC;
}
String SystemManager::getJsonInfo(){
    String json = this->jsonInfo;
    return json;
}
String SystemManager::JSONgenerate(){
    this->jsonInfo="";
    StaticJsonDocument<1024> doc;
    StaticJsonDocument<1024> doc2;
    JsonObject objectDoc = doc.createNestedObject("SystemInformation");
    JsonObject dataSensor = doc.createNestedObject("DataSensor");
    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP, "pool.ntp.org");
    timeClient.begin();
    timeClient.update();

    char buffer[80];
    snprintf(buffer, sizeof(buffer), "%s", timeClient.getFormattedTime().c_str());
    objectDoc["Board"] = this->board;
    objectDoc["MAC"] = this->MAC;
    objectDoc["Time"] = buffer;
    objectDoc["mqtt_user"] = this->mqttClient.mqtt_user;
    
    
    deserializeJson(doc2, "{\"LecteurDePression\":{\"dataName\":\"Pression atmosphérique\",\"value\":18.50,\"unit\":\"bar\"},\"Thermometre\":{\"dataName\":\"Pression atmosphérique\",\"value\":19.50,\"unit\":\"bar\"}}");
    
    this->merge(dataSensor, doc2.as<JsonObject>());

    serializeJson(doc, this->jsonInfo);
    //Serial.println(this->jsonInfo);
    return this->jsonInfo;

}

void SystemManager::merge(JsonObject &dest, JsonObjectConst src)
{
   for (JsonPairConst kvp : src)
   {
     dest[kvp.key()] = kvp.value();
   }
}


void SystemManager::publishJson(){
  if(!this->mqttClient.client.connected()){
    if(this->mqttClient.client.connect(this->mqttClient.mqtt_user)){
      Serial.println("Connected");
    }else {
      Serial.println("Reconnection");
      mqttClient.reconnect();
    }
  }
  
  String JsonInfo = this->getJsonInfo();
  Serial.println(this->getJsonInfo());
  this->mqttClient.client.publish(this->mqttClient.mqtt_output, JsonInfo.c_str());
  this->mqttClient.client.disconnect();
}