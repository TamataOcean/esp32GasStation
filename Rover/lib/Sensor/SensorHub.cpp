#include <SensorTemp.h>
#include <SensorHub.h>
#include <Sensor.h>
#include <Data.h>
#include <Config.h>

bool validateSensor = false;
int countSensor = 0;

SensorHub::SensorHub() {
    Serial.println("Initialize SensorHub...");

    for (size_t i = 0; i < this->SensorCount; i++)
	{
		this->sensors[i] = NULL;
	}

    this->sensors[temperatureSensor] = new SensorTemp(TEMPPIN); // Create a new instance of SensorTemp with the necessary argument list
	// this->sensors[co2Sensor] = new SensorCO2();
	Serial.println("Initialize SensorHub Finish !");
}

SensorHub::~SensorHub() {
    for (size_t i = 0; i < SensorCount; i++)
	{
		if (this->sensors[i])
		{
			delete this->sensors[i];
		}
	}
}

void SensorHub::setup() {
	Wire.begin();
	for (size_t i = 0; i < SensorCount; i++)
	{
		if (this->sensors[i])
		{
			this->sensors[i]->setup(Wire);
		}
	}
}

std::vector<Sensor*>& SensorHub::getSensors() {
    return sensors;
}

void SensorHub::displayValues() {
	for (size_t i = 0; i < SensorCount; i++)
	{
		if (this->sensors[i])
		{
			if (sensors[i]->getState() != 0) {
				Serial.println(sensors[i]->getName());
				Serial.println(sensors[i]->getNameData());
				// Serial.println(sensors[i]->getValue());
				countSensor++;
			}
		}
	}
	
	//  Si il n'y a aucun capteur connecté
	if (countSensor == 0) {
		Serial.println("Aucun capteur");
		while(1);
	}
}

int SensorHub::getSensorCount() {
	return this->SensorCount;
}
