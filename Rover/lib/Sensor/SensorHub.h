#include <Arduino.h>
#include <Sensor.h>
#include <vector>

#ifndef SENSORHUB_H
#define SENSORHUB_H

class SensorHub {
    private:
        static const int SensorCount = 4;
        std::vector<Sensor*> sensors;

    public:
        SensorHub();
        ~SensorHub();
        void setup();
        std::vector<Sensor*>& getSensors();
        int getSensorCount();
        void displayValues();
};

#endif // SENSORHUB_H
