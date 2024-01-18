// ServerGasStation.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "DatabaseManager/DatabaseManager.h"
#include "Conf/Conf.h"

int main()
{
    Conf::Conf conf;
    DatabaseManager::DatabaseManager databaseManager(conf.MYSQLDB_SERVER, conf.MYSQLDB_USER, conf.MYSQLDB_PASSWORD, conf.MYSQLDB_NAME, conf.MYSQLDB_PORT);
    databaseManager.connection();
    //databaseManager.push();
    string jsonString = "{\"SystemInformation\":{\"Board\":\"esp32dev\",\"MAC\":\"2E:8F:4A:1B:9C:7D\",\"Time\":\"00:00:01\",\"mqtt_user\":\"SystemManagerTest\"},\"DataSensor\":{\"LecteurDePression\":{\"dataName\":\"Pression atmosphérique\",\"value\":18.5,\"unit\":\"bar\"},\"Thermometre\":{\"dataName\":\"Pression atmosphérique\",\"value\":19.5,\"unit\":\"bar\"}}}";

    databaseManager.deserializeJsonToObject(jsonString);
    std::cout << "\nHello World!\n";
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
