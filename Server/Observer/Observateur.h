#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

#include <iostream>
#include <list>
#include <string>
#include "../Conf/Conf.h"

class Observateur{
    private:
        string mqtt_server = "localhost:ibm-mqisdp";
        const int mqtt_port = 1883;
        string ssid;
        string password;

    public:
        virtual bool observer();
        virtual void extraire();
        virtual void changeFormat();
        virtual void push();

        Observateur(const char* ssid, const char* password) {
            Conf::Conf conf;
            this->ssid = conf.ssid;
            this->password = conf.password;
        }
};

#endif