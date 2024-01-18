// data.h
#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>

template <typename T>
class Data {
public:
    Data(const std::string& dataName, const std::string& unit, T value): dataName(dataName), unit(unit), value(value) {};

    // Getters
    std::string getDataName() const { return dataName; }
    std::string getUnit() const { return unit; }
    T getValue() const { return value; }

    // Setters
    void setDataName(const std::string& dataName) { this->dataName = dataName; }
    void setUnit(const std::string& unit) { this->unit = unit; }
    void setValue(T value) { this->value = value; }

private:
    std::string dataName;
    std::string unit;
    T value;
};

// Inclusion de la définition de la classe puisque le code est inclus dans l'en-tête
#include "data.cpp"

#endif // DATA_H
