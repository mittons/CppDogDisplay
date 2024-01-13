#!/bin/bash

# Navigate to the project root directory
# Ensure this script is run from the project root where conanfile.py or conanfile.txt is located

# Install dependencies with Conan
conan install . --build=missing

# Create a build directory if it doesn't exist and navigate into it
mkdir -p build
cd build

# Configure the project with CMake, specifying the toolchain file
cmake .. -DCMAKE_TOOLCHAIN_FILE=./generators/conan_toolchain.cmake

# Build the project
cmake --build .
