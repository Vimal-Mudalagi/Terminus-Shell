# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Target executable
TARGET = myshell

# Default rule to build the program
all: $(TARGET)

# Rule to build the executable
$(TARGET): myshell.c
	$(CC) $(CFLAGS) myshell.c -o $(TARGET)

# Rule to clean up compiled files
clean:
	rm -f $(TARGET)
