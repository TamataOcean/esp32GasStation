#ifndef OBSMOSQUITO_H
#define OBSMOSQUITO_H

#include "Observateur.h"
#include "rapidjson.h"
#include "../rapidjson-master/include/rapidjson/document.h"

class ObsMosquito : public Observateur {
    public :
        void extraire();
        void changeFormat();
};

#endif