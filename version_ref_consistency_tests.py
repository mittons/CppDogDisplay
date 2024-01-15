import re
import sys
from pathlib import Path

#  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# | | The current version of this code is powered, at least in part, by OpenAI. Specifically ChatGPT-4.
#  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


# Updated version extraction for CMakeLists.txt based on the new information provided
def extract_version_from_cmake(cmake_path):
    """ Extracts version number from CMakeLists.txt. """
    with open(cmake_path, 'r') as file:
        major, minor, patch = None, None, None
        for line in file:
            if 'PROJECT_VERSION_MAJOR' in line:
                major = re.search(r'set\(PROJECT_VERSION_MAJOR (\d+)\)', line).group(1)
            elif 'PROJECT_VERSION_MINOR' in line:
                minor = re.search(r'set\(PROJECT_VERSION_MINOR (\d+)\)', line).group(1)
            elif 'PROJECT_VERSION_PATCH' in line:
                patch = re.search(r'set\(PROJECT_VERSION_PATCH (\d+)\)', line).group(1)
            if major and minor and patch:
                return f"{major}.{minor}.{patch}"
    return None

def extract_version_from_changelog(changelog_path):
    """ Extracts the latest version number from the CHANGELOG.md file. """
    try:
        latestVersionFound = None
        with open(changelog_path, 'r') as file:    
            for line in file:
                if line.startswith('## ['):
                    # Extract version number from the line
                    version_match = re.search(r'\[\d+\.\d+\.\d+\]', line)
                    if version_match:
                        latestVersionFound = version_match.group(0)[1:-1]  # Remove square brackets
        return latestVersionFound
    except FileNotFoundError:
        print(f"File not found: {changelog_path}")
        return None

def extract_version_from_file(file_path, file_type):
    """ Extracts version number from different file types based on predefined patterns. """
    try:
        with open(file_path, 'r') as file:
            content = file.read()

            if file_type == 'README.md':
                version_match = re.search(r'Current Version: v(\d+\.\d+\.\d+)', content)
            elif file_type == 'version.py':
                version_match = re.search(r'__version__ = ["\'](\d+\.\d+\.\d+)["\']', content)
            elif file_type == 'package.json':
                version_match = re.search(r'"version": ["\'](\d+\.\d+\.\d+)["\']', content)

            if version_match:
                return version_match.group(1)

        return None
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return None



# Update the main function to use the new CMakeLists.txt version extraction function
def main():
    root_folder = Path('.')

    # Check for CHANGELOG.md
    changelog_path = root_folder / 'CHANGELOG.md'
    if not changelog_path.exists():
        print("Error: CHANGELOG.md not found.")
        sys.exit(1)

    # Extract version from CHANGELOG.md
    changelog_version = extract_version_from_changelog(changelog_path)
    if not changelog_version:
        print("Error: Unable to extract version from CHANGELOG.md.")
        sys.exit(1)

    # Files to check
    files_to_check = [
        ('README.md', 'README.md'),
        ('version.py', 'version.py'),
        ('CMakeLists.txt', 'CMakeLists.txt'),
        ('package.json', 'package.json')
    ]

    version_mismatches = []
    successful_matches = []
    file_count = 0

    # Check versions in other files
    for file_name, file_type in files_to_check:
        file_path = root_folder / file_name
        if file_path.exists():
            version = None
            if file_type == 'CMakeLists.txt':
                version = extract_version_from_cmake(file_path)
            else:
                version = extract_version_from_file(file_path, file_type)

            # If there is no version data in the file, skip registering the file.
            if not version:
                continue
            
            file_count += 1

            if version != changelog_version:
                version_mismatches.append((file_name, version))
            else:
                successful_matches.append(file_name)


    print(f"Found CHANGELOG.md and {file_count} additional files containing version information")

    # Output result
    print("\nCHANGELOG.md version: v{}".format(changelog_version))

    # Log files with current version references that match the latest CHANGELOG.md entry
    if successful_matches:
        print("\nFiles with successful version matches:")
        for file_name in successful_matches:
            print(f"    {file_name}")
    
    # Log version mismatches
    if version_mismatches:
        print("\nERROR: Version mismatch(es) detected:")
        print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-")
        for file_name, version in version_mismatches:
            print(f'- File: "{file_name}" has a different version number than the latest version entry in CHANGELOG.md: Version {version} is not equal to {changelog_version}')
        print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-")
        sys.exit(1) # Exit with a non-zero status if any checks failed


if __name__ == '__main__':
    main()


