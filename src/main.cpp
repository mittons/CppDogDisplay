#include "ServerSetup.h"
#include "CprHttpClient.h"
#include "DogBreedService.h"

#ifndef DOG_SERVICE_BASE_URL
#define DOG_SERVICE_BASE_URL "http://localhost:3019" // Default URL if not set at compile time
#endif

int main() {
    CprHttpClient httpClient; // Create an HTTP client instance
    DogBreedService dogBreedService(DOG_SERVICE_BASE_URL, &httpClient); //Inject HTTP client and base url into service
    ServerSetup serverSetup(&dogBreedService); // Inject service into server setup class
    serverSetup.run(); // Run the server setup
    return 0;
}
