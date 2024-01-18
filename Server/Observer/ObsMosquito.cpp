#include "ObsMosquito.h"

void ObsMosquito::extraire() {

    std::string jsonStr = R"(
            {
                "mosquito": {
                    "species": "Aedes aegypti",
                    "location": "Tropical regions",
                    "dangerous": true,
                    "bite_intensity": 8
                }
            }
        )";

    // Convertir la chaîne JSON en objet JSON
    
    rapidjson::Document document;
    const char* json = jsonStr.c_str();
    document.Parse(json);

    // Extraire les valeurs du JSON
    const char* species = document["mosquito"]["species"].GetString();
    const char* location = document["mosquito"]["location"].GetString();
    bool isDangerous = document["mosquito"]["dangerous"].GetBool();
    int biteIntensity = document["mosquito"]["bite_intensity"].GetInt();

    // Afficher les valeurs extraites
    std::cout << "Species: " << species << std::endl;
    std::cout << "Location: " << location << std::endl;
    std::cout << "Is dangerous: " << std::boolalpha << isDangerous << std::endl;
    std::cout << "Bite intensity: " << biteIntensity << std::endl;

}