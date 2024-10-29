# C Shell Implementation - Code Explanation

This file explains each line of code in the C shell implementation. It describes keywords, functions, and important concepts to help understand the code's functionality.

# Code Explanation

## Header Files
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h> // Use this for process management
#include <windows.h> // Include for Windows API
```
- **`stdio.h`**: Standard I/O library, used here for functions like `printf` (to print text) and `fgets` (to read input).
- **`stdlib.h`**: Standard library, used for general functions like memory allocation, process control, etc. While it isn’t specifically used in this snippet, it’s often included for functions like `malloc` or `exit`.
- **`string.h`**: For string manipulation functions like `strlen` (finds string length) and `strtok` (tokenizes a string) which are used here to manage user commands and break them into arguments..
- **`process.h`**: Windows-specific library for process management (like creating and managing child processes).
- **`windows.h`**: The core Windows API library, giving access to Windows-specific functions and definitions, such as `CreateProcess`, `STARTUPINFO`, and `PROCESS_INFORMATION`.

## Defining Constants
```
#define MAX_COMMAND_LENGTH 1024
```
- Defines a constant `MAX_COMMAND_LENGTH` with a value of 1024. This acts as a buffer size limit for commands typed by the user. Defining it here makes the code easier to maintain and adapt, as any size adjustment only requires changing this value.

## Main Function and Command Input Loop
```
int main() {
    char command[MAX_COMMAND_LENGTH];
```
- int main(): Starts the main function, the entry point of every C program.
- char command[MAX_COMMAND_LENGTH];: Declares a `char` array named `command` with the size of `MAX_COMMAND_LENGTH`. This array holds the user-input command, giving space for the text the user types in.
```
    while (1) {
        printf("myshell> ");  // Prompt
```
- while(1): Starts an infinite loop, allowing the shell to continuously prompt for user commands until an exit command is given.
- printf("myshell> ");: Prints a prompt `myshell>` on the screen, signaling to the user that the shell is ready to accept a command.
```
        if (!fgets(command, sizeof(command), stdin)) {
            break;  // Exit on Ctrl+D
        }
```
- `if (!fgets(command, sizeof(command), stdin))`: Reads a line of input from the standard input (`stdin`) and stores it in `command`. `fgets` stops reading when it encounters a newline or fills the buffer. If `fgets` returns `NULL`, meaning there’s no input (e.g., if the user pressed `Ctrl+D`), the loop breaks.

## Handling Commands and Arguments

```
        command[strlen(command) - 1] = '\0';  // Remove newline
```
- `command[strlen(command) - 1] = '\0';`: Replaces the newline character at the end of the input with a null terminator (`'\0'`). `strlen(command) - 1` accesses the newline, which is always the last character from `fgets`. This prevents command execution issues by removing unwanted newline characters.
  
```
        if (strcmp(command, "exit") == 0) {
            break;
        }
```
- `if (strcmp(command, "exit") == 0)`: Compares the user command to the string `"exit"` using `strcmp`, which returns `0` if both strings are identical. If the command is `exit`, the shell stops by breaking out of the loop.

## Splitting the Command into Arguments
```
        char *args[100];  // Array to hold command arguments
        int i = 0;
```
- `char *args[100];`: Declares an array of pointers to `char`, which will store each argument of the command. This setup helps handle commands with multiple words (arguments) by separating each word as an individual string.
- `int i = 0;`: Initializes `i` to `0`, used to count and store each command argument into the `args` array.

```
char *token = strtok(command, " ");  // Split command into tokens
while (token != NULL) {
    args[i++] = token;  // Add tokens to args array
    token = strtok(NULL, " ");
}
args[i] = NULL;  // Null-terminate the arguments array
```
- `char *token = strtok(command, " ");`: Calls `strtok` to split command by spaces (`" "`), returning each segment of `command` as separate tokens.
- `while (token != NULL)`: Loops through each token until there are no more, i.e., `strtok` returns `NULL`.
- `args[i++] = token;`: Assigns each token to the `args` array and increments `i`.
- `args[i] = NULL;`: Null-terminates `args`, required by many command execution functions to know where the argument list ends.

## Creating a New Process for Execution
```
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        ZeroMemory(&pi, sizeof(pi));
```
- `STARTUPINFO si;`: Declares a S`TARTUPINFO` struct, which holds details about how the new process should appear when it starts.
- `PROCESS_INFORMATION pi;`: Declares a `PROCESS_INFORMATION` struct to receive and store details about the created process, including handles and process/thread IDs.
- `ZeroMemory(&si, sizeof(si));` and `ZeroMemory(&pi, sizeof(pi));`: Sets both structures to zero using `ZeroMemory`. It’s a Windows function to clear memory quickly, ensuring all fields in `si` and `pi` are initialized to zero.
  
```
  if (!CreateProcess(NULL,   // No module name (use command line)
                   command,        // Command line
                   NULL,           // Process handle not inheritable
                   NULL,           // Thread handle not inheritable
                   FALSE,          // Set handle inheritance to FALSE
                   0,              // No creation flags
                   NULL,           // Use parent's environment block
                   NULL,           // Use parent's starting directory 
                   &si,            // Pointer to STARTUPINFO structure
                   &pi)            // Pointer to PROCESS_INFORMATION structure
    ) {
    printf("Error executing command: %d\n", GetLastError());
}
```
`CreateProcess`: Attempts to start a new process with the command. Each parameter has a specific purpose:

- `NULL`: No module name is provided since `command` is a full command line.
- `command`: The actual command line to execute.
- `NULL`: No special permissions for the process handle.
- `NULL`: No special permissions for the thread handle.
- `FALSE`: Ensures the new process doesn’t inherit handles from this process.
- `0`: No additional creation flags are used.
- `NULL`: Uses the environment of the current process.
- `NULL`: Uses the current directory.
- `&si`: Pointer to `STARTUPINFO`, defining how the process window appears.
- `&pi`: Pointer to `PROCESS_INFORMATION`, receiving process information.

 ### If `CreateProcess` fails, `GetLastError()` captures the error code, and it’s printed.
 ```
else {
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
```
- `WaitForSingleObject(pi.hProcess, INFINITE);`: Pauses execution of the shell until the child process exits.
- `CloseHandle(pi.hProcess); CloseHandle(pi.hThread);`: Closes handles to the child process and thread to free system resources.
  
```
}
return 0;
}
```
- `return 0;`: Returns 0 to indicate successful completion of the program to the operating system.
