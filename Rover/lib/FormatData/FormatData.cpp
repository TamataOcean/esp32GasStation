#include "FormatData.h"
#include <iostream>
#include <Arduino.h>
#include <String.h>
#include <Sensor.h>
#include <SensorHub.h>
#include <SensorTemp.h>


// String FormatData::StringSensorInformation(Sensor mycapteur) {

//     String dataname = mycapteur.get_DataName();
//     float value = mycapteur.Query();
//     String unit = mycapteur.get_Unit();
//     String json = String(dataname) + " : " + String(value) + String(unit);

//     return json.c_str();
// }