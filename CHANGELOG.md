## [0.1.0] - 2024-01-13

### Added

- **Initial Page Setup**: Implemented an initial page with a header and a data request button.
- **State Transition**: Added a state transition feature which shows a circular loading spinner during data loading, and an error snackbar for failed transitions.
- **Data Display**: Functionality to display data below the header with a button upon successful data loading.
- **Service Module**: Developed `DogBreedService.cpp` to fetch data from an external service.
- **Routing**: Established two routes in `ServerSetup.cpp`: one for rendering the initial site HTML template, and another for the list of dog breeds rendered as partial HTML.
- **Digital Signature**: Created `SignatureService.cpp` for signing responses, enabling clients to verify the authenticity of data from the server. (Note: functional but not yet in use)
- **Testing Framework**: 
  - Wrote tests for the server, including the service and routes.
  - Implemented end-to-end tests that combine `ServerSetup.cpp` and `DogBreedService.cpp`, mock the HTTP client, and verify the route responses.
- **Project documentation**: README.md as an entry point for the project.
- **License handling**: LICENSE file for the project, as well as THIRD_PARTY_LICENSES for crediting third party dependencies (some dependencies not part of version control, but linked/referenced as dependencies).

## [0.1.1] - 2024-01-14

### Added

- **Versioning:** This CHANGELOG.md added for documenting version control.
- **Fix changelog:** Added a few missing items from the v0.1.0 version.

## [0.1.2] - 2024-01-15

- **Maintain Versioning Integrity Across Project:**  Added a Python script that looks for files known to reference current project version and commits to testing them if they do contain that reference. The script then it validates whether all of the files in the project that reference curr_ver reference the same version, returns information on succesful matches and errors. Returns with exit code sys.exit(1) if errors are found.

## [0.1.3] - 2024-01-15

- **CI/CD test for Versioning Integrity:"** Added a lightweight CI/CD script that should reject commits that don't demonstrate integrity in how they express the current project version across different files and/or communincation paths ways. Expressing the same information across all fronts is important; it is not only a mark of diligence, but also a valuable indicator towards evaluating honesty.

- **Moved to staging:** Move to staging to guard the master/main branch against commits that haven't passed testing. Apparently github has blocked access to using workflows as a precommit guard for commits for non-enterprise repositories, so this is a viable workaround, at least for a non-collaborative repository.

## [0.1.4] - 2024-01-15

- **Added acknowledgements sections to README.md:** To ensure contributions are acknowledgeded.

## [0.1.5] - 2024-01-18

- **Updated CI/CD script:** With changes tested in isolated environment at the GitHub repository [TestMergeBranches](https://github.com/mittons/TestMergeBranches). The additions of, and changes to, the automated scripts that react to git push commands two days ago were a bit chaotic and not tested in an isolated environment, however the current changes should perform better, at the very least get a quick resolution if something goes wrong.
- **Fixed link error in README:** Removed additional parenthesis from README.md that was preventing correct hyperlink generation.

## [0.1.6] - 2024-01-18
- **Opt-out option for tests compilation:** Added an option for code users who want to skip test compilation, they can do so by passing -DBUILD_TESTS=OFF to CMake.
- **Changed build script to specify Release config during compilation and build steps:** There seemed to be issues with the Debug configuration.
- **Treeshaking of conanfile:** Removed unused parts from conanfile.py
- **Build and compilation updates:**    
	- Resolved issues related to build and compilation
	- Improved the CMake process to automatically copy directory locations accessed by code via relative paths into each build/compile target directory (src, src/Release, tests, tests/Release).
  - Updated path references in code files to align with the new file/folder locations, since all necessary resources are now available in each executable's directory.
- **Updated version integrity check script:** Can now discover conanfile.py and parse the version info, at least for our current set up.

## [0.1.7] - 2024-01-19

### Added
- **Moved closer to linux support:** Added support for using python3 when on other systems than Windows, python on Windows. (In `SignatureService.cpp`)


### Fixed
- **Added missing header:** `SignatureService.cpp` was not including the atomic header, while still referencing it in code.
- **Removed redundant class refrence:** Removed extra qualification of `SetupServer` class from the `ServerSetup` constructor in `ServerSetup.h`. (A class should not qualify its own member function inside its class definition.)
- **Updated the project name in the `CMakeLists.txt` file:** The `CMakeLists.txt` file now accurately reflects the name of the published project.

### Changed

- **Changed provided build script to reflect production environment:** Modified the build script to use the production flag when using CMake. Also simplified the script a bit.
  
- **Revisited the tests code:**
  - Added unit test for the output of renderBreeds route on empty response from the mocked service layer.
  - Fixed bad test code, and then fixed some more test code. 
  - Removed print statements from test code that cluttered the test output.

## [0.1.8] - 2024-01-19

### Fixed
- **Corrected invalid casing in `cmakelists.txt` files:** Two files in the project were named `CmakeLists.txt`, but correct casing for this filename is `CMakeLists.txt` - *(second letter: m vs M)*.

## [0.1.9] - 2024-01-20

### Fixed
- **Corrected invalid casing in `cmakelists.txt` files:** Two files in the project were named `CmakeLists.txt`, but correct casing for this filename is `CMakeLists.txt` - *(second letter: m vs M)*.
- The changes from [0.1.8] did not seem to connect. So as an alternate attempt we attempt to change the file over two version increments. In this version our `CMakeLists.txt` file have become the magical and adventurous (albeit ineffective purposes related to with CMAke) files: `Starwhisper.txt`.


## [0.1.10] - 2024-01-20

### Fixed
- **Corrected invalid casing in `cmakelists.txt` files:** Two files in the project were named `CmakeLists.txt`, but correct casing for this filename is `CMakeLists.txt` - *(second letter: m vs M)*.
- The changes from [0.1.8] did not seem to connect. So as an alternate attempt we attempt to change the file over two version increments. In this version our magical and adventurous `Starwhisper.txt` files have again become `CMakeLists.txt`.

## [0.1.11] - 2024-01-23

### Added

- **Build Script for Power Shell:** Added `build_script.ps1` to the root dir. 

  <details><summary>Does the same thing as `build_script.sh` does at this comment, three commands. Click to EXPAND/COLLAPSE details: </summary>

  - Install dependencies using conan. 
  - Configure project build system with CMape, 
  - Compile and build project with CMake. 

  <details>
- **The bash build_script should now now be executable:** chmod plus x bash_script.sh. For ease of use anyone who might want to use it. Remember, always check what is in the scripts and code that you run from unknown sources, especially if their intent and/or drives are not known or verfied.

- **Added showcase_scripts folder and test_server_endpoints.py:** While this is a massive learning experience for me, it is ultimately intented as a professional showcase of my skill, cabaility of learning, transferable knowledge, This is ultimately a showcase project, so I provide scripts to assist with showcasing the project, until a better method comes along.

- **Changed name of project:** from ~~CppDogDisplay~~ to DogDisplayForCpp. Safer for potential licensing issues. Places the focus on the functionaly developed in this source code. Shows that the project functions in conjuction with the language, while maintaining distinctiveness as an independent project.

- **Prepare for Showcase and Build from Source Instructions:** Added a script or two, that will at least for a while, be a used as part of showcasing and testing the project in the next few updates.

## [0.2.0] - 2024-01-29

### Added

- **Build Instructions:** Detailed instructions on how to set up the application from source added in BUILD.md

- **Showcase Instructions:** Instructions on how to run the application from source and showcase its functionality. Includes a GitHub Actions setup-build-test-run script.

- **Readme Sections for Installation and Showcase:** Added sections to README.md for the added build instructions and the showcase instructions.

### Changed

 - **Showcase_scripts:** - Made a change to the test_server_endpoints.py script, previous version worked on Ubuntu but apparently needed just a little touch, a bit of spice, to work on Windows.

## [0.2.1] - 2024-02-05

### Changed

- **Diversity Among the Current Batch of Apps:** I decided to give the current group of apps some diversity, to separate them and give each of them something unique and wonderful. Currently they all have the title "Dog Diversity Galore! 🐶". I will change the C++ app to "Dog Diversity Extravaganza! 🐶" and the PHP app to "Dog Diversity Abundance! 🐶", while keeping the Python app the same. (Python app is still getting this changelog message!). Diversity is neither a patch nor a feature. It is an inherent part of the world and should be celebrated as such.

## [0.2.2] - 2024-04-05

### Added

- **Changed default port settings to based on PRODUCTION variable at compile time:** 
 - Now runs on port 7777 by default if PRODUCTION is set to OFF at compile time, and 7778 if PRODUCTION is set to ON at compile time.
 - Changed the build script in the main project directory to take a -p or a -production flag, which affects the PRODUCTION flag setting it uses (OFF if flag is not provided, ON if flag is provided).

## [0.2.3] - 2024-04-05

### Fixed

- **Build script fixed:**
  - Was not making decisions based on the the production flag in build_script.sh, all builds were PRODUCTION=ON.


*Current version of the ChangeLog is powered by OpenAI, ChatGPT-4*
