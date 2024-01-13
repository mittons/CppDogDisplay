#include "DogBreedService.h"
#include <iostream>
#include <string>
#include <regex>

std::string sanitize_string(const std::string& input);

DogBreedService::DogBreedService(const std::string& url, IHttpClient* client)
    : base_url(url), httpClient(client) {}

nlohmann::json DogBreedService::get_breeds() {
    cpr::Response response;
    try {
        response = httpClient->Get(base_url + "/breeds");
    } catch (const std::exception& e) {
        std::cerr << "Error fetching data from external service: " << e.what() << std::endl;
        return nullptr;
    }

    if (response.status_code != 200) {
        std::cerr << "Error fetching data - Invalid status code: " << response.status_code << std::endl;
        return nullptr;
    }

    try {
        nlohmann::json data = nlohmann::json::parse(response.text);
        
        for (auto& dog : data) {
            // Sanitize the 'name' and 'temperament' fields
            dog["name"] = sanitize_string(dog["name"]);
            if (dog.contains("temperament") && !dog["temperament"].is_null()) {
                dog["temperament"] = sanitize_string(dog["temperament"]);
            } else {
                dog["temperament"] = "";
            }
        }


        return data;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON response: " << e.what() << std::endl;
        return nullptr;
    }
}

// Helper function to sanitize strings
std::string sanitize_string(const std::string& input) {
    // Define a regular expression for allowed characters
    std::regex allowedCharsPattern("[^a-zA-Z0-9\\(\\)\\-\\,\\.\\!\\ ]");

    // Replace disallowed characters with an empty string
    std::string sanitized = std::regex_replace(input, allowedCharsPattern, "");

    return sanitized;
}