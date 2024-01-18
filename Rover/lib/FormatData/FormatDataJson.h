#ifndef FormatDataJson_H
#define FormatDataJson_H

#include <iostream>
#include "FormatData.h"
#include "SensorHub.h" // Include the header file for SensorHub

class FormatDataJson : public FormatData<SensorHub> {
public:
    String StringSensorInformation(SensorHub mySensorHub);
    String FormatSensorData(SensorHub mySensorHub);
    String close(String json);
    String concatenate(String texts[]);
    String concatenate(String text1, String text2);
    String GetSensorData(SensorHub mySensorHub);
    String EncapsulateWithAttribute(String attribute, String json);
    String FormatFromData(Data<double> myDataObject);
    
private:
    // Add any private members if needed
};

// Implement the missing function definitions for "StringSensorInformation" and "GetSensorData"

#endif // FormatDataJson_H
