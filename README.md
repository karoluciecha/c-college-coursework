# C Coursework Projects - Atlantic Technological University

This repository contains a collection of **C programs** developed as part of my coursework at **ATU Galway City**. These projects represent my progress throughout the semesters, demonstrating both foundational and applied C programming concepts.

## 📂 Project Structure

The repository is divided into two main folders - **YearTwoSemesterOne** and **YearTwoSemesterTwo** - each representing a separate semester of coursework.

Every semester folder follows the same structure:

* **`Main.c`** - the main entry point that runs the program and displays the main menu
* **`Components/`** - contains modular `.c` source files that define additional program functionality
* **`ResourceFiles/`** - includes `.txt` helper resources used for data storage or configuration

## 🧭 Program Overview

Each semester’s project launches with a **Main Menu** that lists all available programs completed during the course.
The menu allows you to explore various assignments and programming exercises.

Some of the **most significant programs** are clearly marked as:

* **Exam**
* **Project**

These entries represent the major assessment-based projects demonstrating a deeper application of C programming concepts.

## 🛠 System Requirements

To successfully build and run these projects, ensure you meet the following requirements:

* **Operating System:** Windows (x64 architecture)
* **Compiler:** MSVC (Microsoft Visual C++)
* **Development Environment:** Visual Studio Code (configured for MSVC)

### ✅ Tested Environment

These projects were tested on the following setup:

* **Operating System:** Windows 11 (x64)
* **Development Environment:** Visual Studio Code
* **Compiler:** Visual Studio 2022 MSVC (via Developer Command Prompt)

## ⚙️ Configuration Instructions

Before compiling, set up **Visual Studio Code** to use the **Visual Studio 2022 Developer Command Prompt**.

1. Open **`settings.json`** in VS Code (`Ctrl + ,` → *Open Settings (JSON)*)
2. Add or update with the following configuration:

```json
{
    "git.autofetch": true,
    "security.workspace.trust.untrustedFiles": "open",

    "terminal.integrated.profiles.windows": {
        "VS2022 Developer Command Prompt": {
            "path": "C:\\Windows\\System32\\cmd.exe",
            "args": [
                "/k",
                "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat"
            ],
            "icon": "terminal-cmd"
        }
    },
    "terminal.integrated.defaultProfile.windows": "VS2022 Developer Command Prompt"
}
```

This ensures the terminal inside VS Code has access to the `cl.exe` compiler.

## 🏗️ Building and Running the Programs

To compile and run a semester project:

1. Open the **terminal** in VS Code (`` Ctrl + ` ``).
2. Navigate to either the **YearTwoSemesterOne** or **YearTwoSemesterTwo** folder.
3. Compile all C files (including those in the `Components` folder) using:

```bash
cl Main.c Components\*.c && del *.obj
```

> This will produce a single executable file named **Main.exe** in the same directory.

4. Run the program by entering:

```bash
.\Main.exe
```

## 📜 License

This project is intended for educational purposes.
You are welcome to explore, modify, and learn from the code.

## 🙏 Acknowledgments

Thank you for checking out my C++ coursework repository!
If you have any feedback or suggestions, feel free to reach out.
