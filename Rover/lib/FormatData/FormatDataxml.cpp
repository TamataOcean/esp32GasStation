#include "FormatData.h"
#include "FormatDataxml.h"
#include <iostream>
#include <Arduino.h>
#include <Data.h>
// #include <Sensor.h>
#include <SensorHub.h>

String FormatDataxml::FormatFromData(Data<double> myDataObject){
    this->xml = "<data><dataName>"+String(myDataObject.getDataName().c_str())+"</dataName>+<value>"+String(myDataObject.getValue())+"</value>+<unit>"+String(myDataObject.getUnit().c_str())+"</value></data>";
    return this->xml;
}

String FormatDataxml::concatenate(String texts[]) {
    this->xml = "";
    for (int i = 0; i < sizeof(texts); i++) {
        this->xml = xml + String(texts[i]);
    }
    return this->xml;
}

String FormatDataxml::concatenate(String text1, String text2) {
    this->xml = "";
        this->xml = text1 + text2;
    return this->xml;
}

String FormatDataxml::EncapsulateWithAttribute(String attribute, String xml) {
    this->xmlString = String(attribute) + String(xml);
    return this->xmlString;
}

String FormatDataxml::close(String xml) {
    this->xmlString = String(xml);
    return this->xmlString;
}


 