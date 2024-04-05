#!/bin/bash

# Initialize PRODUCTION variable
PRODUCTION=OFF

# Parse command line arguments
for arg in "$@"
do
    case $arg in
        -p|--production)
        PRODUCTION=ON
        shift # Remove --production or -p from processing
        ;;
        *)
        # Unknown option
        ;;
    esac
done

# Navigate to the project root directory
# Ensure this script is run from the project root where conanfile.py or conanfile.txt is located
PROJECT_ROOT_DIR=$(readlink -f $(dirname "$0"))
cd "$PROJECT_ROOT_DIR"

# Install dependencies with Conan
conan install . --build=missing

# Configure the project with CMake, specifying the toolchain file
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DPRODUCTION=$PRODUCTION

# Build the project
cmake --build ./build --config Release