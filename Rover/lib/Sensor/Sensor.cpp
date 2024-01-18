#include "Sensor.h"

String Sensor::getName() {
    return this->name;
}

void Sensor::setName(String name) {
    this->name = name;
}

String Sensor::getNameData() {
    return this->nameData;
}

void Sensor::setNameData(String nameData) {
    this->nameData = nameData;
}

String Sensor::getUnit() {
    return this->unit;
}

void Sensor::setUnit(String unit) {
    this->unit = unit;
}

bool Sensor::getState() {
    return this->state;
}

void Sensor::setState(bool state) {
    this->state = state;
}

String Sensor::getModele() {
    return this->modele;
}

void Sensor::setModele(String modele) {
    this->modele = modele;
}

String Sensor::getMac() {
    return this->mac;
}

void Sensor::setMac(String mac) {
    this->mac = mac;
}

String Sensor::getReturnType() {
    return this->returnType;
}

void Sensor::setReturnType(String type) {
    this->returnType = type;
}
