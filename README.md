# Terminus Shell

This project is a **Terminus Shell** program written in **C** that simulates a command-line interface. The shell allows users to execute system commands, similar to the Windows Command Prompt.

## Features

- Basic shell functionality
- Execute any system command (e.g., `dir`, `cd`, `mkdir`, `ping`)
- Custom prompt (`myshell>`)
- Supports multiple arguments
- Gracefully exits with the `exit` command

## How It Works

The shell continuously runs in a loop, waiting for user input. When a command is entered, the shell parses the input and executes it using the Windows API's `CreateProcess()` function. The program waits for the command to complete before showing the next prompt.

### Key Functions:
- **`fgets()`**: Reads user input from the terminal.
- **`strtok()`**: Tokenizes the input into commands and arguments.
- **`CreateProcess()`**: Executes the input command as a new process.
- **`WaitForSingleObject()`**: Waits for the process to finish before returning control to the shell.

## Commands You Can Use

You can run most **Windows** commands in this shell. Some examples include:

- **Directory and File Navigation**:
  - `dir`: List files in the current directory.
  - `cd [directory]`: Change the current directory.
  - `mkdir [folder_name]`: Create a new folder.
  - `rmdir [folder_name]`: Remove an empty folder.

- **File Operations**:
  - `copy [source] [destination]`: Copy files.
  - `del [file_name]`: Delete a file.
  - `rename [old_name] [new_name]`: Rename a file or folder.
  - `move [source] [destination]`: Move a file to another directory.

- **System Information**:
  - `echo [text]`: Print text to the screen.
  - `systeminfo`: Display system information.
  - `tasklist`: List all running processes.
  - `taskkill /PID [process_id]`: Terminate a process.

- **Network Operations**:
  - `ping [hostname or IP]`: Test network connectivity.
  - `ipconfig`: Show network configuration.

### Built-in Commands:
- **`exit`**: Closes the shell.

### Commands Not Supported
Since this is a **Windows-based shell**, Linux/Unix commands like `ls`, `grep`, and `cat` won't work unless you use additional tools like **Git Bash** or **Cygwin**.

## Compilation and Execution

To compile and run the shell, follow these steps:

### Prerequisites:
- Install **TDM-GCC** or any other **GCC** compiler for Windows.
- Ensure **GCC** is in your system's PATH so it can be called from the terminal.

### Steps to Compile:

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/simple-shell.git
   cd simple-shell
   Compile the code:

bash
Copy code
gcc myshell.c -o myshell
Run the shell:

bash
Copy code
./myshell
If everything is set up correctly, you should see:

bash
Copy code
myshell>
You can now enter commands like dir, echo Hello, or exit to quit.

Using a Makefile (Optional):
To make compilation easier, you can use the included Makefile.

Compile the program by running:

bash
Copy code
make
Clean up the project (remove the compiled files):

bash
Copy code
make clean

License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgments
This shell was created as a learning project to practice C programming and system calls in Windows.
