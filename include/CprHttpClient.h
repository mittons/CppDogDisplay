#ifndef CPRHTTPCLIENT_H
#define CPRHTTPCLIENT_H

#include "IHttpClient.h"

class CprHttpClient : public IHttpClient {
public:
    cpr::Response Get(const std::string& url) override {
        return cpr::Get(cpr::Url{url});
    }
};

#endif // CPRHTTPCLIENT_H
