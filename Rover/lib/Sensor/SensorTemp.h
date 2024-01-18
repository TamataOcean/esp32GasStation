#include <Arduino.h>
#include <Sensor.h>
#include "SparkFunBME280.h"
#include <OneWire.h>
#include <Data.h>

#ifndef SENSORTEMP_H
#define SENSORTEMP_H
#define StartConvert 0
#define ReadTemperature 1

class SensorTemp:public Sensor
{
    public:
            SensorTemp(int pin);
            ~SensorTemp();            
            void setup(TwoWire& i2cBus);
            void update();
            void setValue(double value);
            double temperature;
            Data<double> getData();

    private:
            double valueTemp;
            int pinTemp;
            unsigned  long tempSampleInterval = 850 ;
	        unsigned  long tempSampleTime;

	        // Analyze temperature data
	        double TempProcess(bool ch);
        
};
#endif
