//
// Created by Goura on 15/01/2024.
//

#ifndef GASSTATION_CONF_H
#define GASSTATION_CONF_H
#pragma once

#include <iostream>
using namespace std;

namespace Conf {

    class Conf {
    public:
        static const string ssid;
        static const string password;
        static const string mqtt_server;
        static const string mqtt_output;
        static const string mqtt_input;
        static const string mqtt_log;
        static const string mqtt_user;
        static const int ledPin;
        static int timeInterval;
        static const string MYSQLDB_SERVER;
        static const string MYSQLDB_NAME;
        static int MYSQLDB_PORT;
        static const string MYSQLDB_USER;
        static const string MYSQLDB_PASSWORD;
    };

} // Conf

#endif //GASSTATION_CONF_H
