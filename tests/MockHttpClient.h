#include <gmock/gmock.h>
#include "IHttpClient.h"

class MockHttpClient : public IHttpClient {
public:
    // Mock the Get method
    MOCK_METHOD(cpr::Response, Get, (const std::string& url), (override));
};