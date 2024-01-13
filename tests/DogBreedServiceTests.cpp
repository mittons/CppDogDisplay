#include <gtest/gtest.h>
#include <iostream>
#include "DogBreedService.h"
#include "MockHttpClient.h"
#include <gmock/gmock.h>
#include <cpr/cpr.h>

class DogBreedServiceTests : public ::testing::Test {
protected:
    std::unique_ptr<MockHttpClient> mockHttpClient;
    DogBreedService *dogBreedService;
    std::string dummyUrl;

    void SetUp() override {
        std::cout << "Setting up DogBreedServiceTests" << std::endl;
        dummyUrl = "http://dummyurl";
        mockHttpClient = std::make_unique<MockHttpClient>();
        dogBreedService = new DogBreedService(dummyUrl, mockHttpClient.get());
    }
    
    void TearDown() override {
        delete dogBreedService;
    }
};

std::string getValidJsonDBSTests();
std::string getInvalidJsonDBSTests();
std::string createMockJsonWithUnsafeChar(char ch);
bool isSanitized(const nlohmann::json& data, char ch);


class CPRExceptionDBS : public std::exception {
public:
    CPRExceptionDBS(const cpr::Error& error, const std::string& exceptionName)
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


TEST_F(DogBreedServiceTests, TestGetDataSuccess) {
    // ---------------------------------------------------------------
    // | Return VALID result + 200 status
    // ---------------------------------------------------------------
    cpr::Response mockResponse;
    mockResponse.status_code = 200;
    mockResponse.text = getValidJsonDBSTests();

    // Set up the mockHttpClient to return our mockResponse
    EXPECT_CALL(*mockHttpClient, Get(dummyUrl + "/breeds"))
    .WillOnce(testing::Return(mockResponse));

    nlohmann::json serviceResult = dogBreedService->get_breeds();

    EXPECT_FALSE(serviceResult.is_null());
}

TEST_F(DogBreedServiceTests, TestGetDataInvalidJsonFailure) {
    // ---------------------------------------------------------------
    // | Return INVALID result + 200 status
    // ---------------------------------------------------------------
    cpr::Response mockResponse;
    mockResponse.status_code = 200;
    mockResponse.text = getInvalidJsonDBSTests();

    // Set up the mockHttpClient to return our mockResponse
    EXPECT_CALL(*mockHttpClient, Get(dummyUrl + "/breeds"))
    .WillOnce(testing::Return(mockResponse));

    nlohmann::json serviceResult = dogBreedService->get_breeds();

    EXPECT_TRUE(serviceResult.is_null());
}

TEST_F(DogBreedServiceTests, TestGetData404Failure) {
    // --------------------------------------------------------------- 
    // | Return 404 status
    // ---------------------------------------------------------------
    cpr::Response mockResponse;
    mockResponse.status_code = 404;
    mockResponse.text = "";

    // Set up the mockHttpClient to return our mockResponse
    EXPECT_CALL(*mockHttpClient, Get(dummyUrl + "/breeds"))
    .WillOnce(testing::Return(mockResponse));

    nlohmann::json serviceResult = dogBreedService->get_breeds();

    EXPECT_TRUE(serviceResult.is_null());
}

TEST_F(DogBreedServiceTests, TestGetDataConnectionError) {
    // --------------------------------------------------------------- 
    // | Throw CONNECTION_FAILURE
    // ---------------------------------------------------------------
    cpr::Error error;
    error.code = cpr::ErrorCode::CONNECTION_FAILURE;

    // Set up the mockHttpClient to throw our error
    EXPECT_CALL(*mockHttpClient, Get(dummyUrl + "/breeds"))
        .WillOnce(testing::Throw(CPRExceptionDBS(error, "CONNECTION_ERROR")));
        
    nlohmann::json serviceResult = dogBreedService->get_breeds();

    EXPECT_TRUE(serviceResult.is_null());
}

TEST_F(DogBreedServiceTests, TestGetDataOperationTimeoutError) {
    // --------------------------------------------------------------- 
    // | Throw OPERATION_TIMEOUT
    // ---------------------------------------------------------------
    cpr::Error error;
    error.code = cpr::ErrorCode::OPERATION_TIMEDOUT;

    // Set up the mockHttpClient to throw our error
    EXPECT_CALL(*mockHttpClient, Get(dummyUrl + "/breeds"))
        .WillOnce(testing::Throw(CPRExceptionDBS(error, "OPERATION_TIMEDOUT")));

    nlohmann::json serviceResult = dogBreedService->get_breeds();

    EXPECT_TRUE(serviceResult.is_null());
}

TEST_F(DogBreedServiceTests, SanitizesUnsafeCharacters) {
    // --------------------------------------------------------------- 
    // | Return fields containing unsafe characters
    // ---------------------------------------------------------------
    std::vector<char> unsafeChars = {'|', '&', ';', '<', '>', '$', '`', '\\', '"'};

    for (char ch : unsafeChars) {
        // Setup mock response with unsafe character
        std::string mockJson = createMockJsonWithUnsafeChar(ch);
        cpr::Response mockResponse;
        mockResponse.text = mockJson;

        // Set up the mockHttpClient to return our mockResponse
        EXPECT_CALL(*mockHttpClient, Get).WillOnce(testing::Return(mockResponse));

        // Call the service method
        auto breeds = dogBreedService->get_breeds();

        // Assert that the response is sanitized
        ASSERT_TRUE(isSanitized(breeds, ch));
    }
}

std::string getValidJsonDBSTests() {
    return R"customdelimiter([{"weight":{"imperial":"6 - 13","metric":"3 - 6"},"height":{"imperial":"9 - 11.5","metric":"23 - 29"},"id":1,"name":"Affenpinscher","bred_for":"Small rodent hunting, lapdog","breed_group":"Toy","life_span":"10 - 12 years","temperament":"Stubborn, Curious, Playful, Adventurous, Active, Fun-loving","origin":"Germany, France","reference_image_id":"BJa4kxc4X"},{"weight":{"imperial":"50 - 60","metric":"23 - 27"},"height":{"imperial":"25 - 27","metric":"64 - 69"},"id":2,"name":"Afghan Hound","country_code":"AG","bred_for":"Coursing and hunting","breed_group":"Hound","life_span":"10 - 13 years","temperament":"Aloof, Clownish, Dignified, Independent, Happy","origin":"Afghanistan, Iran, Pakistan","reference_image_id":"hMyT4CDXR"},{"weight":{"imperial":"44 - 66","metric":"20 - 30"},"height":{"imperial":"30","metric":"76"},"id":3,"name":"African Hunting Dog","bred_for":"A wild pack animal","life_span":"11 years","temperament":"Wild, Hardworking, Dutiful","reference_image_id":"rkiByec47"}])customdelimiter";
}

std::string getInvalidJsonDBSTests() {
    return "%$&SDF^^GJJKI";
}

bool isSanitized(const nlohmann::json& data, char ch) {
    // Check if data is sanitized
    for (auto& dog : data) {
        if (dog["name"].get<std::string>().find(ch) != std::string::npos ||
            dog["temperament"].get<std::string>().find(ch) != std::string::npos) {
            return false;
        }
    }
    return true;
}

std::string createMockJsonWithUnsafeChar(char ch) {
    return "{\"name\": \"Test" + std::string(1, ch) + "\", \"temperament\": \"Aggressive" + std::string(1, ch) + "\"}";
}

