//
// Created by Goura on 16/01/2024.
//

#ifndef GASSTATION_DATABASEMANAGER_H
#define GASSTATION_DATABASEMANAGER_H
#include <iostream>
#include "mysql_connection.h"
#include "../mysql-connector-c++-8.3.0-winx64/include/jdbc/cppconn/driver.h"
#include "../mysql-connector-c++-8.3.0-winx64/include/jdbc/cppconn/exception.h"
#include "../mysql-connector-c++-8.3.0-winx64/include/jdbc/cppconn/prepared_statement.h"
#include "rapidjson.h"
#include "../rapidjson-master/include/rapidjson/document.h"
#include <list>


using namespace std;
using namespace rapidjson;

namespace DatabaseManager {

    class DatabaseManager {
    private:
        string nom;
        string user;
        string password;
        string server;
        int port;
        sql::Connection* conn;
    public:
        DatabaseManager(const string server, const string user, const string password, const string nom, int port){
            this->nom = nom;
            this->user = user;
            this->password = password;
            this->server = server;
            this->port = port;
            this->conn = get_driver_instance()->connect("tcp://" + this->server + ":" + std::to_string(this->port), this->user, this->password);
        }
        sql::Connection* connection();
        bool push();
        void deserializeJsonToObject(string json);
    };

} // DatabaseManager

#endif //GASSTATION_DATABASEMANAGER_H
