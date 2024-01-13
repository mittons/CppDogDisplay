#ifndef SERVERSETUP_H
#define SERVERSETUP_H

#include "IDogBreedService.h"
#include "IHttpClient.h"
#include <crow.h>

class ServerSetup {
    IDogBreedService* dogBreedService;

public:
    explicit ServerSetup::ServerSetup(IDogBreedService* service);

    crow::SimpleApp app;

    crow::SimpleApp& getApp() {
        return app;
    }

    void run();

};

#endif // SERVERSETUP_H
