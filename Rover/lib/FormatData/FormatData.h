#ifndef FormatData_H
#define FormatData_H

#include <Arduino.h>
#include <FormatData.h>
#include <String.h>
#include <Sensor.h>
#include <SensorHub.h>
#include <SensorTemp.h>

template <typename T>

class FormatData {
    public:
    String StringSensorInformation(SensorHub mySensorHub);
    String FormatSensorData(SensorHub mySensorHub);
    String close(String json);
    String concatenate(String texts[]);
    String concatenate(String text1, String text2);
    String GetSensorData(SensorHub mySensorHub);
    String EncapsulateWithAttribute(String attribute, String json);
    String DataToJson(Data<double> data);
    String FormatFromData(Data<double> myDataObject);
    private:
};
#endif