#include <inja/inja.hpp>
#include "ServerSetup.h"
#include "DogBreedService.h"
#include "SignatureService.h"

#include <fstream>
#include <sstream>

#include <regex>

#include <string>
#include <algorithm>

inja::Environment env;

void setupRoutes(crow::SimpleApp& app, IDogBreedService& dogBreedService, inja::Environment& env);



ServerSetup::ServerSetup(IDogBreedService* service) : dogBreedService(service) {
    setupRoutes(app, *dogBreedService, env);
}

void ServerSetup::run() {
    #ifdef PRODUCTION
    app.port(7778).multithreaded().run();
    #else
    app.port(7777).multithreaded().run();
    #endif
}

std::string trimLineEndings(const std::string& input) {
    std::string result = input;
    // Remove CRLF
    if (result.length() >= 2 && result.substr(result.length() - 2) == "\r\n") {
        result.erase(result.length() - 2);
    }
    // Remove LF
    else if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    return result;
}


void setCORSHeaders(crow::response& res, const crow::request& req) {
    std::string origin = req.get_header_value("Origin");
       
    // TODO: Origin needs to be set for production env.

    //"http://localhost:*" where * is a digit
    std::regex localhostRegex("^http:\\/\\/localhost:\\d+$");

    if (std::regex_match(origin, localhostRegex)) {
        res.set_header("Access-Control-Allow-Origin", origin);
    }

    res.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Origin, Content-Type, X-Custom-Signature-Header");
    res.set_header("Access-Control-Expose-Headers", "X-Custom-Signature-Header");
}

void setupRoutes(crow::SimpleApp& app, IDogBreedService& dogBreedService, inja::Environment& env) {
    // -----------------------------------------------------------------------------------
    // | Route that serves the initial site, with a header and a request dog data button
    CROW_ROUTE(app, "/")([&env](const crow::request& req) {
        // Render the route template into a response variable
        crow::response resp{ env.render_file("./templates/initial_template.html", nlohmann::json{}) };

        // Set CORS headers for response
        setCORSHeaders(resp, req);

        // Set content type header to text/html, utf-8. (This was added because there are emojis in the html)
        resp.set_header("Content-Type", "text/html; charset=utf-8");

        // Sign the response body and set the signature header
        SignatureService sigService;
        std::string signature = sigService.sign_data(resp.body);
        signature = trimLineEndings(signature);
        resp.set_header("X-Custom-Signature-Header", signature);

        return resp;
    });

    // --------------------------------------------------------------------------
    // | Route that serves rendered dog breed data as partial html upon request
    CROW_ROUTE(app, "/renderBreeds")([&dogBreedService, &env](const crow::request& req) {
        auto data = dogBreedService.get_breeds();
        if (!data.is_null()) {

            // The template cant handle missing values for our fields. 
            // - So we set any missing fields to empty string.
            for (auto& dog : data) {
                if (!dog.contains("temperament") || dog["temperament"].is_null()) {
                    dog["temperament"] = "";
                }
            }

            // The data we receive is a json list [{"name": "x", ...}, {"name": "y", ...}, ...]
            // Inja seems to want named variables rather than lists. 
            // - So we wrap our data, the json list, in a kv-pair {"data": jsonList}
            nlohmann::json template_data = { {"data", data} };


            // Render the route template into a response variable
            crow::response resp{ env.render_file("./templates/breeds_template.html", template_data)};

            // Set CORS headers for response
            setCORSHeaders(resp, req);

            // Sign the response body and set the signature header
            SignatureService sigService;
            std::string signature = sigService.sign_data(resp.body);
            signature = trimLineEndings(signature);
            resp.set_header("X-Custom-Signature-Header", signature);

            return resp;
        }
        else {
            return crow::response{ 500, "{\"error\":\"Unable to fetch data from the external service\"}" };
        }
    });

    // ----------------------------------------------------------------------------------
    // | Route that serves the js file needed by the index and renderbreeds routes html
    CROW_ROUTE(app, "/static/js/bundle.js")([&env](const crow::request& req) {
        std::string filepath = "./static/js/bundle.js";
        std::ifstream file(filepath, std::ios::binary);

        if (file) {
            // Read the entire file
            std::ostringstream contents;
            contents << file.rdbuf();
            file.close();

            // Create a response with the file content
            crow::response resp(contents.str());

            // Set CORS headers for response
            setCORSHeaders(resp, req);

            // Set the appropriate MIME type
            resp.set_header("Content-Type", "application/javascript");

            return resp;
        }
        else {
            // File not found, return a 404 response
            return crow::response(404);
        }
    });
}