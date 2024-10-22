#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h> // Use this for process management
#include <windows.h> // Include for Windows API

#define MAX_COMMAND_LENGTH 1024

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("myshell> ");  // Prompt
        if (!fgets(command, sizeof(command), stdin)) {
            break;  // Exit on Ctrl+D
        }
        
        command[strlen(command) - 1] = '\0';  // Remove newline

        // Handle "exit" command
        if (strcmp(command, "exit") == 0) {
            break;
        }

        char *args[100];  // Array to hold command arguments
        int i = 0;

        char *token = strtok(command, " ");  // Split command into tokens
        while (token != NULL) {
            args[i++] = token;  // Add tokens to args array
            token = strtok(NULL, " ");
        }
        args[i] = NULL;  // Null-terminate the arguments array

        // Create a new process to execute the command
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        ZeroMemory(&pi, sizeof(pi));

        // Start the child process
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
        } else {
            // Wait until child process exits
            WaitForSingleObject(pi.hProcess, INFINITE);
            // Close process and thread handles. 
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    }

    return 0;
}
