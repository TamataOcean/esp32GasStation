#ifndef SUJET_H
#define SUJET_H

class Sujet {
    private:
        char* ssid;
        char* password;
    public:
        virtual void connect();
};

#endif