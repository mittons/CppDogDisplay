cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0079 NEW)
project(DogDisplayForCpp)

option(PRODUCTION "Build for production" OFF)

if(PRODUCTION)
    add_definitions(-DPRODUCTION)
     add_definitions(-DDOG_SERVICE_BASE_URL=\"https://nodedogroute-38a170d08520.herokuapp.com\")
else()
    # Set development-specific settings
endif()


set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 1)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-D_WIN32_WINNT=0x0A00)
endif()

find_package(inja REQUIRED)
find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(GTest REQUIRED)

# This function copies specified files/directories (e.g., template folders, scripts) to the designated 
# build directory. It's used to ensure that runtime dependencies are correctly 
# located relative to the executable, particularly in different build configurations.
function(copy_exec_context_files source_dir dest_dir items)
    foreach(item IN LISTS items)
		#message("Copying ${item} from ${source_dir}/${item} to ${dest_dir}/")
        file(COPY "${source_dir}/${item}" DESTINATION "${dest_dir}")
    endforeach()
endfunction()



# -------------
# | Main exe
# -----------

# Add the main application directory
add_subdirectory(src)


# Set files to copy to paths relative to the built executables.
set(EXEC_RELATIVE_FILES_TO_COPY "templates" "src/sign.py" "static")

# Move/copy templates folder and signature script to build/src folder
copy_exec_context_files(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}/src "${EXEC_RELATIVE_FILES_TO_COPY}")

if(CMAKE_BUILD_TYPE STREQUAL "Release")	
	# Move/copy templates folder and signature script to build/src/Release folder
    copy_exec_context_files(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}/src/Release "${EXEC_RELATIVE_FILES_TO_COPY}")
endif()


# -----------
# | Tests
# ---------


# Add an option for users who want to skip test compilation, they can do so by passing -DBUILD_TESTS=OFF to CMake.
option(BUILD_TESTS "Build the tests" ON)

if(BUILD_TESTS)
    # Enable Google Test
    enable_testing()
    # Add the tests directory
    add_subdirectory(tests)
	
	# Move/copy templates folder and signature script to build/test folder
	copy_exec_context_files(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}/tests "${EXEC_RELATIVE_FILES_TO_COPY}")
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
		# Move/copy templates folder and signature script to build/test/Release folder
        copy_exec_context_files(${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}/tests/Release "${EXEC_RELATIVE_FILES_TO_COPY}")
    endif()
endif()
