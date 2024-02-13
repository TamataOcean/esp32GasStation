#include "FormatData.h"
#include "FormatDataJson.h"
#include <iostream>
#include <Arduino.h>
#include <String.h>
#include <Data.h>
#include <Sensor.h>
#include <SensorHub.h>

int countSensor = 0;


String FormatDataJson::FormatFromData(Data<double> myDataObject){
    String json = "{\"dataName\":\"" + String(myDataObject.getDataName().c_str()) + "\",\"value\":\""+ String(myDataObject.getValue())+ " unit\":\"" + String(myDataObject.getUnit().c_str()) + "\"}";
    return json;
}

String FormatDataJson::concatenate(String texts[]) {
    String json = "";
    for (int i = 0; i < sizeof(texts); i++) {
        String json = json +","+ String(texts[i]);
    }
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


