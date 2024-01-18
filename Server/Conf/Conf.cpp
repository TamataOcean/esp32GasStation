//
// Created by Goura on 15/01/2024.
//

#include "Conf.h"

namespace Conf {
        const string Conf::ssid = "WifiRaspi";
        const string Conf::password = "wifiraspi";
        const string Conf::mqtt_server = "172.24.1.1";
        const string Conf::mqtt_output = "esp32/update";
        const string Conf::mqtt_input = "esp32/input";
        const string Conf::mqtt_log = "esp32/log";
        const string Conf::mqtt_user = "ESP32_Proto_Exemple";
        const int Conf::ledPin = 4;
        int Conf::timeInterval = 7500;

        /// Mysql configuration
        const string Conf::MYSQLDB_SERVER = "127.0.0.1";
        const string Conf::MYSQLDB_NAME = "gasstation";
        int Conf::MYSQLDB_PORT = 3306;
        const string Conf::MYSQLDB_USER = "root";
        const string Conf::MYSQLDB_PASSWORD = "root";
} // Conf