//
// Created by Goura on 16/01/2024.
//

#include "DatabaseManager.h"

namespace DatabaseManager {
    sql::Connection* DatabaseManager::connection() {

        conn->setSchema(this->nom);
        return conn;
    }

    // fonction de déserialisation JSON
    void DatabaseManager::deserializeJsonToObject(string json) {
        // On déclare un objet JSON
        Document document;
        const char* js = json.c_str();
        document.Parse(js);
        int size = document.Size();
        int capacity = document.Capacity();
        string strcap = std::to_string(capacity);
        string str = std::to_string(size);
        printf("capacity : ");
        printf(strcap.c_str());
        printf("\nsize : ");
        printf(str.c_str());
        printf("\n");
        printf(document["SystemInformation"]["MAC"].GetString());
    }

    bool DatabaseManager::push() {
        bool res = false;
        try {
            sql::PreparedStatement* pstmt = conn->prepareStatement("INSERT INTO `test` (`name`) VALUES(?)");
            pstmt->setString(1, "Temperature");
            res = pstmt->execute();
        }
        catch (sql::SQLException& e) {
            std::cout << e.what() << std::endl;
        }
        

        return res;
    }
} // DatabaseManager