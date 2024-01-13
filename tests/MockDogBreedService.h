#include <gmock/gmock.h>
#include "IDogBreedService.h"

class MockDogBreedService : public IDogBreedService {
public:
    MOCK_METHOD(nlohmann::json, get_breeds, (), (override));
};
