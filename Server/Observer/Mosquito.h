#ifndef MOSQUITO_H
#define MOSQUITO_H

#include "Sujet.h"

class Mosquito : public Sujet {
    private:
        const char* ssid;
        const char* password;
    public :
        void connect();
        Mosquito(const char* ssid, const char* password) {
            this->ssid = ssid;
            this->password = password;
        }
};

#endif