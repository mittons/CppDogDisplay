#include <gtest/gtest.h>
#include <crow.h>
#include "ServerSetup.h"
#include "MockDogBreedService.h"
#include <gmock/gmock.h>
#include <iostream>
#include <nlohmann/json.hpp>

class RoutesTests : public ::testing::Test {
protected:
    std::unique_ptr<MockDogBreedService> mockDogBreedService;
    ServerSetup *serverSetup;


    void SetUp() override {
        // Still undecided on if this is too verbose and clutters test output.
        // std::cout << "Setting up DogBreedServiceTests" << std::endl;
        mockDogBreedService = std::make_unique<MockDogBreedService>();
        serverSetup = new ServerSetup(mockDogBreedService.get());
    }

    void TearDown() override {
        delete serverSetup;
    }
};


std::string getValidJsonRoutesTest();
std::string getInvalidJsonRoutesTest();

TEST_F(RoutesTests, TestIndexRoute) {
    // ---------------------------------------------------------------
    // | Index Route - Default
    // ---------------------------------------------------------------
    auto& app = serverSetup->getApp();

    app.validate();
    {
        crow::request req;
        crow::response res;

        req.url = "/";
        app.handle(req, res);
        
        std::string responseBody = res.body;
        // Verify our header element is in the html contained in the response body
        ASSERT_TRUE(responseBody.find("div class=\"header-bar\"") != std::string::npos);

        // Verify our dog breeds request button is in the html contained in the response body
        ASSERT_TRUE(responseBody.find("id=\"dog-breed-list-request-button\"") != std::string::npos);
    }
}

TEST_F(RoutesTests, TestRenderBreedsRouteSuccess) {
    // ---------------------------------------------------------------
    // | RenderBreeds Route - Return SUCCESSFUL service result
    // ---------------------------------------------------------------
    auto& app = serverSetup->getApp();

    nlohmann::json mockResponse = nlohmann::json::parse(getValidJsonRoutesTest());

    // Set up the mockService to return our mockResponse
    EXPECT_CALL(*mockDogBreedService, get_breeds())
    .WillOnce(testing::Return(mockResponse));

    app.validate();
    {        
        std::vector<std::map<std::string, std::string>> mockData = {
            {{"name", "Affenpinscher"}, {"temperament", "Stubborn, Curious, Playful, Adventurous, Active, Fun-loving"}},
            {{"name", "Afghan Hound"}, {"temperament", "Aloof, Clownish, Dignified, Independent, Happy"}},
            {{"name", "African Hunting Dog"}, {"temperament", "Wild, Hardworking, Dutiful"}}
        };

        crow::request req;
        crow::response res;

        req.url = "/renderBreeds";
        app.handle(req, res);

        std::string responseBody = res.body;
        for (const auto& breed : mockData) {
            ASSERT_TRUE(responseBody.find(breed.at("name")) != std::string::npos);
            ASSERT_TRUE(responseBody.find(breed.at("temperament")) != std::string::npos);
        }
    }
}

TEST_F(RoutesTests, TestRenderBreedsRouteFailure) {
    // ---------------------------------------------------------------
    // | RenderBreeds Route - Return UNSUCCESFUL service result
    // ---------------------------------------------------------------
    auto& app = serverSetup->getApp();

    nlohmann::json mockResponse = nullptr;

    // Set up the mockService to return our mockResponse
    EXPECT_CALL(*mockDogBreedService, get_breeds())
    .WillOnce(testing::Return(mockResponse));

    app.validate();
    {
        crow::request req;
        crow::response res;

        req.url = "/renderBreeds";
        app.handle(req, res);

        ASSERT_EQ(res.code, 500);
        // Test for the exact error message here, but not necessarily in integration/e2e tests to avoid coupling code too much to this implementation.
        ASSERT_EQ(res.body, "{\"error\":\"Unable to fetch data from the external service\"}");

    }

}

std::string getValidJsonRoutesTest() {
    return R"customdelimiter([{"weight":{"imperial":"6 - 13","metric":"3 - 6"},"height":{"imperial":"9 - 11.5","metric":"23 - 29"},"id":1,"name":"Affenpinscher","bred_for":"Small rodent hunting, lapdog","breed_group":"Toy","life_span":"10 - 12 years","temperament":"Stubborn, Curious, Playful, Adventurous, Active, Fun-loving","origin":"Germany, France","reference_image_id":"BJa4kxc4X"},{"weight":{"imperial":"50 - 60","metric":"23 - 27"},"height":{"imperial":"25 - 27","metric":"64 - 69"},"id":2,"name":"Afghan Hound","country_code":"AG","bred_for":"Coursing and hunting","breed_group":"Hound","life_span":"10 - 13 years","temperament":"Aloof, Clownish, Dignified, Independent, Happy","origin":"Afghanistan, Iran, Pakistan","reference_image_id":"hMyT4CDXR"},{"weight":{"imperial":"44 - 66","metric":"20 - 30"},"height":{"imperial":"30","metric":"76"},"id":3,"name":"African Hunting Dog","bred_for":"A wild pack animal","life_span":"11 years","temperament":"Wild, Hardworking, Dutiful","reference_image_id":"rkiByec47"}])customdelimiter";
}
