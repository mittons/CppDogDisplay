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

- **Updated CI/CD script** With changes tested in isolated environment at the GitHub repository [TestMergeBranches](https://github.com/mittons/TestMergeBranches). The additions of, and changes to, the automated scripts that react to git push commands two days ago were a bit chaotic and not tested in an isolated environment, however the current changes should perform better, at the very least get a quick resolution if something goes wrong.
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

### Changed

### Fixed
- **Corrected invalid casing in `cmakelists.txt` files:** Two files in the project were named `CmakeLists.txt`, but correct casing for this filename is `CMakeLists.txt` - *(second letter: m vs M)*.
- The changes from [0.1.8] did not seem to connect. So as an alternate attempt we attempt to change the file over two version increments. In this version our `CMakeLists.txt` file have become the magical and adventurous (albeit ineffective purposes related to with CMAke) files: `Starwhisper.txt`.

*Current version of the ChangeLog is powered by OpenAI, ChatGPT-4*
