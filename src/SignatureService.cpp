#include "SignatureService.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <cstdlib>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>


// Ensure we get a unique value each time we call random, even if calls happen at just about the same time.
unsigned long long generateUniqueSeed() {
    static std::atomic<unsigned long long> counter(0);
    auto time_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    auto process_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
    auto random_device_seed = std::random_device{}();

    return time_seed ^ (process_id << 1) ^ (static_cast<unsigned long long>(random_device_seed) << 1) ^ (counter++);
}

// Generate a unique static length (10 digit) string for the file we pass to the python script.
// - This is to guard against directory attacks.
std::string generateUniqueString() {
    unsigned long long seed = generateUniqueSeed();
    std::mt19937_64 generator(seed);


    // Define the range
    int digitCount = 10;
    int lower_bound = static_cast<int>(std::pow(10, digitCount - 1));
    int upper_bound = static_cast<int>(std::pow(10, digitCount) - 1);
    std::uniform_int_distribution<> distrib(lower_bound, upper_bound);

    // Generate the number
    int random_number = distrib(generator);

    return std::to_string(random_number);
}

// We use this function to save the html code to file.
// - We save the html code to file, we want to sign the all of the data, every character. Otherwise the signature doesnt work.
// - The data might contain js code, so we can't escape any characters, or pass it to base64 encoding funcitons that might escape characters.
//   - At the same time, we dont want to pass unsanitized data directly through a system process. We don't trust the system call, it might execute code if it gets into the data somehow.
//     - So we pass the data through a file, rather than directly through a system process argument.
std::string saveToTempFile(const std::string& htmlContent) {
    // Generate a unique temporary filename
    std::string tempFilename = "./tmp_" + generateUniqueString() + ".html";

    // Write the HTML content to the file
    std::ofstream outFile(tempFilename);
    if (outFile.is_open()) {
        outFile << htmlContent;
        outFile.close();
        return tempFilename;
    } else {
        throw std::runtime_error("Unable to create temp file");
    }
}


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    #ifdef _WIN32
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    #else
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    #endif
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    // Cast the buffer size to int, since it is within the range of int, and fgets expects an int argument for the buffer size.
    // The buffer size is known at compile time and does not exceed the maximum value of an int, making this cast safe.
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


// We sign the data, to ensure that clients that properly validate the data only recieve data from us.
std::string signDataWithPython(const std::string& data) {

    std::string tempFilePath = saveToTempFile(data);

    std::string command = "python ./sign.py " + tempFilePath;
    std::string signature = exec(command.c_str());

    // Delete the temporary file
    if (remove(tempFilePath.c_str()) != 0) {
        std::cerr << "Error deleting file: " << tempFilePath << std::endl;
    }

    if (signature.size() > 344) {
        std::string signatureStripped = signature.substr(0, 344);
        return signatureStripped;
    }
    return signature;
}


std::string SignatureService::sign_data(const std::string& data) {
    std::string signature = signDataWithPython(data);

    return signature;
}