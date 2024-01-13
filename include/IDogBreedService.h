// IDogBreedService.h
#ifndef IDOGBREEDSERVICE_H
#define IDOGBREEDSERVICE_H

#include <nlohmann/json.hpp>

class IDogBreedService {
public:
    virtual ~IDogBreedService() = default;
    virtual nlohmann::json get_breeds() = 0;
};

#endif // IDOGBREEDSERVICE_H
