#ifndef DOGBREEDSERVICE_H
#define DOGBREEDSERVICE_H

#include "IDogBreedService.h"
#include <string>
#include <nlohmann/json.hpp>
#include "IHttpClient.h"

class DogBreedService : public IDogBreedService {
private:
    std::string base_url;  // Base URL for the service
    IHttpClient* httpClient;  // HTTP client for dependency injection

public:
    DogBreedService(const std::string& url, IHttpClient* client);

    nlohmann::json get_breeds() override;
};

#endif // DOGBREEDSERVICE_H
