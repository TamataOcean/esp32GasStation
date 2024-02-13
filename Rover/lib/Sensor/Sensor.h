#include <Arduino.h>
#include <OneWire.h> 
#include <SensirionCore.h>
#include <Data.h>

#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
    public:
            // Virtuals (Surcharge)
            virtual void setup(TwoWire& i2cBus) = 0;
            virtual void update() = 0;
            virtual Data<double> getData() = 0;
            virtual ~Sensor() = 0;
            
            // Globals
            String getName();
            void setName(String name);
            String getNameData();
            void setNameData(String nameData);
            String getUnit();
            void setUnit(String unit);
            bool getState();
            void setState(bool state);
            String getModele();
            void setModele(String modele);
            String getMac();
            void setMac(String mac);
            String getReturnType();
            void setReturnType(String returnType);
    private:
            String name;
            String nameData;
            String unit;
            bool state;
            String returnType; // A voir à quoi ça peut servir
            String mac;
            String modele;

};
#endif
