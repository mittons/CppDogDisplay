# SHOWCASE_BUILD.md

## Introduction
This guide provides detailed instructions for setting up and showcasing the `DogDisplayForCpp` application. There are two primary paths to achieve this: 
1. [**GitHub Actions Environment Showcase:**](#github-actions-instructions) For users who want to use a GitHub Actions script to automatically clone and build the project in their own private repository. This is a streamlined method ideal for observing the automated build, test, and showcase execution processes in a secure and remote environment.
2. [**Docker Environment Showcase:**](#docker-instructions) For users who prefer to set up a Docker environment to build and run the project, especially useful for cross-platform compatibility and isolated testing.

## Index
1. [Introduction](#introduction)
2. [GitHub Actions Showcase Instructions](#github-actions-showcase-instructions)
   - [2.1. Setting up Your Repository for GitHub Actions](#21-setting-up-your-repository-for-github-actions)
   - [2.2. Using the GitHub Actions Script](#22-using-the-github-actions-script)
   - [2.3. Observing the Build and Showcase Process](#23-observing-the-build-and-showcase-process)
   - [2.4. Understanding Workflow Outputs](#24-understanding-workflow-outputs)
3. [Docker Showcase Instructions](#docker-showcase-instructions)
   - [3.1. Setting Up Docker](#31-setting-up-docker)
   - [3.2. Running Docker Images](#32-running-docker-images)
   - [3.3. Building and Showcasing in Docker](#33-building-and-showcasing-in-docker)
   - [3.4. Running the Application and Verifying Its Output](#34-running-the-application-and-verifying-its-output)
4. [Conclusions](#conclusions)
   - [4.1. Demonstrating Application Functionality](#41-demonstrating-application-functionality)
   - [4.2. Documentation: A Key Aspect of Software Development](#42-documentation-a-key-aspect-of-software-development)
   - [4.3. Reflection on the Process](#43-reflection-on-the-process)
   - [4.4. Invitation for Feedback](#44-invitation-for-feedback)
   - [4.5. Encouragement for Exploration](#45-encouragement-for-exploration)
   - [4.6. Acknowledgments](#46-acknowledgments)

## GitHub Actions Showcase Instructions
### 2.1. Setting up Your Repository for GitHub Actions
- Create a **new private repository** on your GitHub account.
- In your new repository, create a folder named `.github/workflows`.

### 2.2. Using the GitHub Actions Script
- Obtain the GitHub Actions script provided for the `DogDisplayForCpp` application.
   - You can choose between a script that runs on a Windows GitHub Actions runner and a Ubuntu GitHub Actions runner, the scripts are located in the [showcase_scripts](/showcase_scripts/) folder of this repository.
- Place the script you chose into the `.github/workflows` folder you just created.
- Commit and push these changes to the `main` branch of your new repository. 
    ```bash
    git add .github/workflows/*
    ```
    ```bash
    git commit -m "Add GitHub Actions script for DogDisplayForCpp showcase"
    ```
    
    ```bash
    git push origin main
    ```
- The script is designed to automatically clone the `DogDisplayForCpp` repository and perform all necessary build and setup steps.


### 2.3. Observing the Build and Showcase Process
After you have pushed the GitHub Actions script to your repository, the action will trigger automatically. Here's how you can observe the build and showcase process:

- Navigate to the **Actions** tab in your GitHub repository.
- A list of workflow runs will be displayed. Click on the name of the run you want to inspect.
- You will see the jobs within the workflow; click on the job named build-and-showcase (or the relevant job title) to view the run logs.
- The logs are organized into collapsible sections for each step of the workflow. Click on each step to expand and view its detailed logs and outputs.

By following these steps, you will be able to monitor the progress of each task within the workflow, verify the successful execution of steps, and ensure that the `DogDisplayForCpp` application is building and running as expected.

### 2.4. Understanding Workflow Outputs
After triggering the GitHub Actions workflows, you can observe the following steps and their purposes:

<details>
<summary><ins><b>Workflow Steps:</b></ins> Click here to EXPAND/COLLAPSE a description of the GitHub Actions workflow steps!</summary>

1. **Preparing the Project:** Checks out the code from the main repository for `DogDisplayForCpp`.

2. **Setup Dependencies**: Installs the necessary programs and sets up the dependencies required for the project.

3. **Configure Environment**: Configures the programs and dependencies installed in the previous step.

4. **Building the Application:** Builds the application from source.

5. **Server-Side Tests**: Executes server tests and captures the output in a log.

6. **Execute Showcase Run of Server**: Runs the `DogDisplayForCpp.exe` program, which should be part of the built project, and performs a series of predefined Python requests to test current server endpoints. Both the program and the Python requests output to log files, which are displayed in the next two steps for verification.

7. **Display Server Response Logs from Showcase Run (Caution: LARGE Log File)**: Outputs from the server responses captured by the Python requests executed for testing. The logs are expected to be quite lengthy, and expanding this section creates a very large scrollable section in your browser.

8. **Display Server Logs from Showcase Run**: Outputs the server logs that were generated during the `DogDisplayForCpp.exe` run.

</details>

<ins><b>Finally:</b></ins> Having examined the outputs of these steps, you will have validated the functionality of the application and its compliance with the expected behavior. 🎯!

## Docker Showcase Instructions
### 3.1. Setting Up Docker
<ins>**Install Docker**:</ins> Follow the official guides to install Docker on your system:
  - [Docker for Linux 🐧](https://docs.docker.com/engine/install/ubuntu/)
  - [Docker for Windows 🖥️](https://docs.docker.com/docker-for-windows/install/)
<details>
<summary><ins><b>Verify Installation Success:</b></ins> Click here to EXPAND/COLLAPSE a set of instructions on how to verify the success of your Docker installation process (optional)</summary>

- <ins>**Verify Docker Installation**:</ins>

  After installation, open a terminal or command prompt and run `docker --version` to ensure Docker has been installed correctly. You should see the Docker version number in the output.

- <ins>**Test Docker Functionality**:</ins>
  
  Run `docker run hello-world`. This command downloads a test image and runs it in a container. 
  
  If Docker is correctly installed and configured, you will receive a message indicating that your Docker installation appears to be working correctly.
</details>

### 3.2. Running Docker Images

#### Open up a console window on your os, then enter the following command based on your desired showcase:

#### 🖥️ <ins>For Windows Server Core Virtual Container:</ins>

```bash
docker run -it mcr.microsoft.com/windows/servercore:ltsc2019 powershell
```
#### 🐧 <ins>For running Ubuntu Virtual Container:</ins>

```bash
docker run -it ubuntu
```


### 3.3. Building and Showcasing in Docker
Once inside the Docker environment of your choice, refer to [BUILD.md](BUILD.md) for system-specific build instuctions. Follow the instructions up to, <ins><b>and including:</b></ins>
- [Step: 1.5 Running Tests (Optional) for Linux](SHOWCASE_BUILD.md#--15-running-tests-optional) 🐧
- [Step: 2.5 Running Tests (Optional) for Windows](SHOWCASE_BUILD.md#--25-running-tests-optional) 🖥️

After that refer to the following chapters in this document for instructions on how to perform automated testing, as well as to run and verify the output of the application through console yourself.


### 3.4. Running the Application and Verifying Its Output

Before running the application, choose the instructions for your operating system:

<details>
<summary>🐧 <ins><b>Linux:</b></ins> Click here to EXPAND/COLLAPSE instructions for Linux!</summary>

1. **Set Up the Environment - Move the test script for server endpoints:**
   ```bash
   mv ./showcase_scripts/test_server_endpoints.py ./build/src/
   ```

2. **Navigate to the Application Directory:**
   ```bash
   cd ./build/src
   ```

3. **Install Python Requests Module:**
   ```bash
   python -m pip install requests
   ```

4. **Run the Application:**
   ```bash
   ./DogDisplayForCpp > test_run_server_logs.log 2>&1 &
   ```

5. **Run the Test Script and Examine Outputs:**
   
   Execute the test script: 
   ```
   python test_server_endpoints.py
   ```
   Review the server logs and the server response data:
   
   *Careful, the server response data will flood your console if everything went well.*
   ```
   cat test_run_server_logs.log'
   ```
   ```
   cat server_response_data_out.txt
   ```
    <details>
    <summary><ins><b>Understanding the Server Response Data:</b></ins> Click here to EXPAND/COLLAPSE on details the structure of the <em><b>server_response_data_out.txt</b></em> file! 🔍</summary>

    <br>

    Utilize this section to validate whether the expected server response was received. The output in `server_response_data_out.txt` is divided into four parts, each separated by lines of equality signs (===):
    
   1. **Index Route Response Data:** The main portion of the text, showing data from the root (`\`) route.
   2. **RenderBreeds Route Response Data:** Data from the `\renderBreeds` route, not as extensive as the index route.
   3. **Index Route Headers:** Headers for the root (`\`) route response.
   4. **RenderBreeds Route Headers:** Headers for the `\renderBreeds` route response.        
    
    <br>
    </details>
</details>

<details>
<summary>🖥️ <ins><b>Windows:</b></ins> Click here to EXPAND/COLLAPSE instructions for Windows!</summary>

1. **Set Up the Environment - Move the test script for server endpoints:**
   ```powershell
   mv .\showcase_scripts\test_server_endpoints.py .\build\src\Release\
   ```

2. **Navigate to the Application Directory:**
   ```powershell
   cd .\build\src\Release
   ```

3. **Install Python Requests Module:**
   ```powershell
   python -m pip install requests
   ```

4. **Run the Application:**
   ```powershell
   Start-Process -FilePath .\DogDisplayForCpp.exe -RedirectStandardOutput test_run_server_stdout.log -RedirectStandardError test_run_server_logs.log -NoNewWindow
   ```

5. **Run the Test Script and Examine Outputs:**

    Execute the test script: 
   ```
   python test_server_endpoints.py
   ```
   Review the server logs and the server response data:
   
   *Careful, the server response data will flood your console if everything went well.*
   ```powershell
   Get-Content -Path .\test_run_server_logs.log
   ```
   ```powershell
   Get-Content -Path server_response_data_out.txt
   ```
    <details>
    <summary><ins><b>Understanding the Server Response Data:</b></ins> Click here to EXPAND/COLLAPSE on details the structure of the <em><b>server_response_data_out.txt</b></em> file! 🔍</summary>

    <br>

    Utilize this section to validate whether the expected server response was received. The output in `server_response_data_out.txt` is divided into four parts, each separated by lines of equality signs (===):

   1. **Index Route Response Data:** The main portion of the text, showing data from the root (`\`) route.
   2. **RenderBreeds Route Response Data:** Data from the `\renderBreeds` route, not as extensive as the index route.
   3. **Index Route Headers:** Headers for the root (`\`) route response.
   4. **RenderBreeds Route Headers:** Headers for the `\renderBreeds` route response.        
    
    <br>
    </details>
</details>



<ins><b>Finally:</b></ins> Having examined the outputs of these steps, you will have validated the functionality of the application and its compliance with the expected behavior. 🎯!

## Conclusions

### 4.1. Demonstrating Application Functionality
This guide has successfully demonstrated the process of building, testing, and running the application. The outputs from the scripted test actions serve as evidence of the application's functionality in different environments. This documentation highlights the practicality and capabilities of the application, showcasing the effectiveness of the setup and execution processes.

### 4.2. Documentation: A Key Aspect of Software Development
This guide is a reflection of my commitment to creating clear and user-friendly documentation. It's designed to facilitate an easy and comprehensive understanding of the application's setup and operation, demonstrating my approach to making complex processes accessible and manageable.

### 4.3. Reflection on the Process
This journey through the application's setup, testing, and execution is not just a demonstration of the app's capabilities but also a reflection of my methodical approach to software development. It highlights my commitment to quality, thorough testing, and an understanding of the importance of documentation in software engineering.

### 4.4. Invitation for Feedback
As this guide also serves as a portfolio piece, I warmly invite feedback on both the application and the documentation. Your insights and suggestions are invaluable for continuous improvement and learning.

### 4.5. Encouragement for Exploration
To potential employers and collaborators, this guide demonstrates my capability to handle complex software development tasks and produce clear, comprehensive documentation. I encourage you to delve deeper into the application and the documentation process, as it showcases my skills and dedication as a software developer and technical writer.

### 4.6. Acknowledgments
I extend my gratitude to those who have provided guidance and feedback throughout the development of this application and the creation of this guide. Your support has been instrumental in refining both the product and the accompanying documentation. Special thanks to OpenAI and ChatGPT-4 for their assistance in enhancing the documentation process.

*Current version of this documentation is powered by OpenAI, ChatGPT-4*
