#!/bin/bash

# Navigate to the project root directory
# Ensure this script is run from the project root where conanfile.py or conanfile.txt is located

# Install dependencies with Conan
conan install . --build=missing

# Configure the project with CMake, specifying the toolchain file
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DPRODUCTION=ON

# Build the project
cmake --build ./build --config Release