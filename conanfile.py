from conan import ConanFile

class DogDisplayForCppConan(ConanFile):
    name = "DogDisplayForCpp"
    version = "0.2.0"
    
    settings = "os", "compiler", "build_type"
    requires = (
        "crowcpp-crow/1.0+5",
        "nlohmann_json/3.11.3",
        "cpr/1.10.5",
        "inja/3.4.0",
        "gtest/1.14.0"
    )
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        self.folders.source = "src"
        self.folders.build = "build"
        self.folders.generators = "build/generators"
        self.cpp.source.includedirs = ["include"]
        self.cpp.build.bindirs = ["bin"]
        self.cpp.build.libdirs = ["lib"]
