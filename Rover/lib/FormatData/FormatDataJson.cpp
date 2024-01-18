#include "FormatDataJson.h"
#include <iostream>
#include <Arduino.h>
#include <String.h>
#include <Data.h>
#include <Sensor.h>
#include <SensorHub.h>

int countSensor = 0;

String FormatDataJson::FormatSensorData(SensorHub mySensorHub) {

      FormatDataJson* monFormat = new FormatDataJson();  


    // Data data = mySensorHub.get_Data();
    String name;
    String json = "{\"DataSensor\":[";

    std::vector<Sensor*>& sensors = mySensorHub.getSensors();

    for (size_t i = 0; i < sensors.size(); i++)
	{
		if (sensors[i])
		{
            name = sensors[i]->getName();
            Serial.println(sensors[i]->getNameData());
            Serial.print("\n");
            

            Data<double> data = sensors[i]->getData();
            countSensor++;
            json = json + "{\""+String(name)+"\":"+String(monFormat->FormatFromData(data))+"}";
            if(countSensor < sensors.size()){
                json = json + ",";
            }
		}
	}

    // String json = "\"DataSensor\":{\""+String(name)+"\":\"dataName\":\"" + String(dataname) + "\",\"value\":" + String(value) + ",\"unit\":\"" + String(unit) + "\"}}";
    return "";
}
String FormatDataJson::FormatFromData(Data<double> myDataObject){
    String json = "{\"dataName\":\"" + String(myDataObject.getDataName().c_str()) + "\",\"value\":\""+ String(myDataObject.getValue())+ " unit\":\"" + String(myDataObject.getUnit().c_str()) + "\"}";
    return json;
}
/*
String FormatDataJson::concatenate(String texts[]) {
    String json = "";
    for (int i = 0; i < sizeof(texts); i++) {
        String json = json +","+ String(texts[i]);
    }
    return json;
}

String FormatDataJson::GetSensorData(SensorHub mySensorHub) {
    String dataname = "";
    float value = "";
    String unit = "";
    String name = "";

    String json = "{\""+String(name)+"\":{\"dataName\":\"" + String(dataname) + "\",\"value\":" + String(value) + ",\"unit\":\"" + String(unit) + "\"}";
    return json;
}
String FormatDataJson::EncapsulateWithAttribute(String attribute, String json) {
    String jsonString = "{\"" + String(attribute) + "\":" + String(json) + "}";
    return jsonString;

}

String FormatDataJson::close(String json) {
    String jsonString = "{" + String(json) + "}";
    return jsonString;
}
*/

