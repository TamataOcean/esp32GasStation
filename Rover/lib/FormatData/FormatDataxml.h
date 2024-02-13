#ifndef FormatDataxml_H
#define FormatDataxml_H

#include <iostream>
#include "FormatData.h"

class FormatDataxml : public FormatData<SensorHub> {
public:
    String close(String json);
    String concatenate(String texts[]);
    String concatenate(String text1, String text2);
    String GetSensorData(SensorHub mySensorHub);
    String EncapsulateWithAttribute(String attribute, String json);
    String FormatFromData(Data<double> myDataObject);
private:
    // Add any private members if needed
    String xml, xmlString; 
};

// Implement the missing function definitions for "StringSensorInformation" and "GetSensorData"

#endif // FormatDataJxml_H 
