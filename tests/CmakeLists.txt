# ------------------------
# | DogBreedServiceTests
# ----
# Setup code
add_executable(DogBreedServiceTests DogBreedServiceTests.cpp ../src/DogBreedService.cpp)
target_include_directories(DogBreedServiceTests PRIVATE ../include)
target_link_libraries(DogBreedServiceTests 
	GTest::GTest 
	GTest::Main 
	GTest::gmock
	pantor::inja
    nlohmann_json::nlohmann_json
    Crow::Crow
    cpr::cpr
)
# Define test
add_test(NAME DogBreedServiceTests COMMAND DogBreedServiceTests)


# ---------------
# | RoutesTests
# ----
# Setup code
add_executable(RoutesTests RoutesTests.cpp ../src/DogBreedService.cpp ../src/ServerSetup.cpp ../src/SignatureService.cpp )
target_include_directories(RoutesTests PRIVATE ../include)
target_link_libraries(RoutesTests 
	GTest::GTest 
	GTest::Main 
	GTest::gmock
	pantor::inja
    nlohmann_json::nlohmann_json
    Crow::Crow
    cpr::cpr
)
# Define test
add_test(NAME RoutesTest COMMAND RoutesTests)


# -----------------
# | EndToEndTests
# ----
# Setup code
add_executable(EndToEndTests EndToEndTests.cpp ../src/DogBreedService.cpp ../src/ServerSetup.cpp ../src/SignatureService.cpp )
target_include_directories(EndToEndTests PRIVATE ../include)
target_link_libraries(EndToEndTests 
	GTest::GTest 
	GTest::Main 
	GTest::gmock
	pantor::inja
    nlohmann_json::nlohmann_json
    Crow::Crow
    cpr::cpr
)
# Define test
add_test(NAME EndToEndTest COMMAND EndToEndTests)


# ----------------------
# | Run all tests code
# ----
# Setup code
add_executable(AllTests 
	test_main.cpp
    DogBreedServiceTests.cpp
	../src/DogBreedService.cpp
    RoutesTests.cpp
	../src/ServerSetup.cpp 
	../src/SignatureService.cpp
    EndToEndTests.cpp
)
target_include_directories(AllTests PRIVATE ../include)
target_link_libraries(AllTests 
    GTest::GTest 
    GTest::Main 
    GTest::gmock
	pantor::inja
    nlohmann_json::nlohmann_json
    Crow::Crow
    cpr::cpr
)