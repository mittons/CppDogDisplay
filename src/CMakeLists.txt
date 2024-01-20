add_executable(${PROJECT_NAME} main.cpp ServerSetup.cpp DogBreedService.cpp SignatureService.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ../include)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    pantor::inja
    nlohmann_json::nlohmann_json
    Crow::Crow
    cpr::cpr
)