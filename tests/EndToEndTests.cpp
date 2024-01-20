#include <gtest/gtest.h>
#include <crow.h>
#include "ServerSetup.h"
#include "DogBreedService.h"
#include "MockHttpClient.h"
#include <gmock/gmock.h>
#include <iostream>

class EndToEndTest : public ::testing::Test {
protected:
    std::unique_ptr<MockHttpClient> mockHttpClient;
    DogBreedService* dogBreedService;
    ServerSetup *serverSetup;
    std::string dummyUrl;

    void SetUp() override {
        // Still undecided on if this is too verbose and clutters test output.
        // std::cout << "Setting up EndToEndTests" << std::endl;
        dummyUrl = "http://dummyurl";
        
        mockHttpClient = std::make_unique<MockHttpClient>();
        dogBreedService = new DogBreedService(dummyUrl, mockHttpClient.get());
        serverSetup = new ServerSetup(dogBreedService);
    }

    void TearDown() override {
        delete serverSetup;
        delete dogBreedService;
    }
};

std::string getValidJsonE2ETests();

class CPRExceptionE2E : public std::exception {
public:
    CPRExceptionE2E(const cpr::Error& error, const std::string& exceptionName)
        : error_(error), fullMessage_("CPR Exception occurred: " + exceptionName) {}

    const char* what() const noexcept override {
        return fullMessage_.c_str();
    }

    cpr::Error GetError() const {
        return error_;
    }

private:
    cpr::Error error_;
    std::string exceptionName;
    std::string fullMessage_;
};

TEST_F(EndToEndTest, TestCompleteFlow) {
    // ---------------------------------------------------------------
    // | Complete successful e2e test of the main workflow
    // ---------------------------------------------------------------
    auto& app = serverSetup->getApp();

    app.validate();
    {
        crow::request req;
        crow::response res;

        req.url = "/";
        app.handle(req, res);

        std::string responseBody = res.body;
        //Verify our header element is in the html contained in the response body
        ASSERT_TRUE(responseBody.find("div class=\"header-bar\"") != std::string::npos);

        //Verify our dog breeds request button is in the html contained in the response body
        ASSERT_TRUE(responseBody.find("id=\"dog-breed-list-request-button\"") != std::string::npos);
    }

    // Set up the mockHttpClient to return our mockResponse
    cpr::Response mockResponse;
    mockResponse.status_code = 200;
    mockResponse.text = getValidJsonE2ETests();

    EXPECT_CALL(*mockHttpClient, Get(dummyUrl + "/breeds"))
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


TEST_F(EndToEndTest, TestGetData404Failure) {
    // --------------------------------------------------------------- 
    // | Return 404 status
    // ---------------------------------------------------------------
    auto& app = serverSetup->getApp();

    cpr::Response mockResponse;
    mockResponse.status_code = 404;
    mockResponse.text = "";

    // Set up the mockHttpClient to return our mockResponse
    EXPECT_CALL(*mockHttpClient, Get(dummyUrl + "/breeds"))
    .WillOnce(testing::Return(mockResponse));

    app.validate();
    {
        crow::request req;
        crow::response res;

        req.url = "/renderBreeds";
        app.handle(req, res);

        std::string responseBody = res.body;

        ASSERT_EQ(res.code, 500);
    }
}

TEST_F(EndToEndTest, TestGetConnectionError) {
    // --------------------------------------------------------------- 
    // | Throw CONNECTION_FAILURE
    // ---------------------------------------------------------------
    auto& app = serverSetup->getApp();

    cpr::Error error;
    error.code = cpr::ErrorCode::CONNECTION_FAILURE;

    // Set up the mockHttpClient to throw our error
    EXPECT_CALL(*mockHttpClient, Get(dummyUrl + "/breeds"))
        .WillOnce(testing::Throw(CPRExceptionE2E(error, "CONNECTION_ERROR")));
        
    app.validate();
    {
        crow::request req;
        crow::response res;

        req.url = "/renderBreeds";
        app.handle(req, res);

        std::string responseBody = res.body;

        ASSERT_EQ(res.code, 500);
    }
}

TEST_F(EndToEndTest, TestGetOperationTimeoutError) {
    // --------------------------------------------------------------- 
    // | Throw OPERATION_TIMEOUT
    // ---------------------------------------------------------------
    auto& app = serverSetup->getApp();

    cpr::Error error;
    error.code = cpr::ErrorCode::OPERATION_TIMEDOUT;

    // Set up the mockHttpClient to throw our error
    EXPECT_CALL(*mockHttpClient, Get(dummyUrl + "/breeds"))
        .WillOnce(testing::Throw(CPRExceptionE2E(error, "OPERATION_TIMEDOUT")));

    app.validate();
    {
        crow::request req;
        crow::response res;

        req.url = "/renderBreeds";
        app.handle(req, res);

        std::string responseBody = res.body;

        ASSERT_EQ(res.code, 500);
    }
}

std::string getValidJsonE2ETests() {
    return R"customdelimiter([{"weight":{"imperial":"6 - 13","metric":"3 - 6"},"height":{"imperial":"9 - 11.5","metric":"23 - 29"},"id":1,"name":"Affenpinscher","bred_for":"Small rodent hunting, lapdog","breed_group":"Toy","life_span":"10 - 12 years","temperament":"Stubborn, Curious, Playful, Adventurous, Active, Fun-loving","origin":"Germany, France","reference_image_id":"BJa4kxc4X"},{"weight":{"imperial":"50 - 60","metric":"23 - 27"},"height":{"imperial":"25 - 27","metric":"64 - 69"},"id":2,"name":"Afghan Hound","country_code":"AG","bred_for":"Coursing and hunting","breed_group":"Hound","life_span":"10 - 13 years","temperament":"Aloof, Clownish, Dignified, Independent, Happy","origin":"Afghanistan, Iran, Pakistan","reference_image_id":"hMyT4CDXR"},{"weight":{"imperial":"44 - 66","metric":"20 - 30"},"height":{"imperial":"30","metric":"76"},"id":3,"name":"African Hunting Dog","bred_for":"A wild pack animal","life_span":"11 years","temperament":"Wild, Hardworking, Dutiful","reference_image_id":"rkiByec47"}])customdelimiter";
}