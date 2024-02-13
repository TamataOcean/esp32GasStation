#include "Sensor.h"
#include <Arduino.h>
#include <Data.h>
#include "SensorTemp.h"
// #include <string.h>


double i = 0;
BME280 sensorBME280;


void SensorTemp::setup(TwoWire& i2cBus) {
    Serial.println("BME280 begin");

    // I2C device found at address 0x76
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

void SensorTemp::setValue(double value) {
    this->valueTemp = value;
}

void SensorTemp::update()
{
	Serial.println("Update Temperature Sensor...");
    this->setValue(sensorBME280.readTempC());
}

Data<double> SensorTemp::getData() {
    this->update();
   
    // Créer une instance de la classe Data avec les informations nécessaires
    Data<double> temperatureData("Temperature","Celsius", this->valueTemp);

    return temperatureData;
}

SensorTemp::SensorTemp(int pin) {
    this->setName("BME280");
    this->setNameData("Temperature");
    this->setUnit("°C");
    this->setState(1);
    this->setMac("test");
    this->update();
}

SensorTemp::~SensorTemp() {
    
}

// Sensor::~Sensor() {

// }