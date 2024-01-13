from conan import ConanFile

class CppDogDisplayConan(ConanFile):
    name = "CppDogDisplay"
    version = "0.1.0"
    
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

    def export(self):
        # logs that might be generated in the recipe folder at "export" time.
        # these would be associated with the recipe repo and original source of the recipe repo
        copy(self, "*.log", src=self.recipe_folder,
        dst=os.path.join(self.recipe_metadata_folder, "logs"))

    def source(self):
        # logs originated in the source() step, for example downloading files, patches or other stuff
        save(self, os.path.join(self.recipe_metadata_folder, "logs", "src.log"), "srclog!!")

    def build(self):
        # logs originated at build() step, the most common ones
        save(self, "mylogs.txt", "some logs!!!")
        copy(self, "mylogs.txt", src=self.build_folder,
        dst=os.path.join(self.package_metadata_folder, "logs"))
