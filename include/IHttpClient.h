#ifndef IHTTPCLIENT_H
#define IHTTPCLIENT_H

#include <cpr/cpr.h>
#include <string>

class IHttpClient {
public:
    virtual ~IHttpClient() = default;
    virtual cpr::Response Get(const std::string& url) = 0;
};

#endif // IHTTPCLIENT_H