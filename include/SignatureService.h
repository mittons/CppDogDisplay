#ifndef SIGNATURESERVICE_H
#define SIGNATURESERVICE_H

#include <string>

class SignatureService {
public:
    SignatureService() {}

    std::string sign_data(const std::string& data);
};

#endif // SIGNATURESERVICE_H