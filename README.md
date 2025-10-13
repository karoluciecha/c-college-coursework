# c-college-coursework

This repository contains C coursework for college, set up to be built and run using **Visual Studio 2022’s MSVC compiler** in **Visual Studio Code**.

---

## ⚙️ VS Code Setup for MSVC C Compiler

To compile and run C programs in this project, configure **VS Code** to use the Visual Studio Developer Command Prompt:

1. Open **`settings.json`** in VS Code (`Ctrl + ,` → click *Open Settings (JSON)*).
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

This sets up a terminal in VS Code that can access the `cl.exe` compiler.

---

## 🏗️ Compiling the Program

1. Open the terminal in VS Code (`Ctrl + ``)

2. Navigate to the project folder containing `Main.c`

3. Compile all C files (including those in the `Components` folder) and remove temporary `.obj` files:

```bash
cl Main.c Components\*.c && del *.obj
```

> This will produce a single executable file `Main.exe`.

---

## ▶️ Running the Program

Run the compiled executable directly in the terminal:

```bash
.\Main.exe
```

You should now see the program’s output.