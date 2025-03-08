# ELF Binary Disassembler

## Overview

This program disassembles an executable C file and writes the disassembled content to a text file. It's a command-line tool that provides a user-friendly interface to the `objdump` utility for disassembling ELF binaries.

## Features

- Simple command-line interface for disassembling executable files
- Integrates with the standard `objdump` utility
- Error handling for file access and processing
- Verifies file existence before processing
- Clean, well-documented code structure

## Directory Structure

```
Q1_Disassembler/
├── Makefile              # Build script
├── README.md             # This documentation
├── include/              # Header files directory
└── src/                  # Source files directory
    └── disassembler.c    # Main source file
```

## Requirements

- GCC compiler
- objdump utility (part of binutils)
- Linux-based operating system

## Building

To build the disassembler:

```bash
make
```

This will compile the source files and generate the executable `disassembler` in the bin directory.

## Usage

```bash
./bin/disassembler <executable_file> <output_file>
```

### Command Line Arguments

- `<executable_file>`: The path to the executable file you want to disassemble
- `<output_file>`: The path where you want to save the disassembled content

### Example

```bash
./bin/disassembler /bin/ls disassembly.txt
```

This will create a file named `disassembly.txt` containing the disassembled code of the `/bin/ls` executable.

## Implementation Details

The program works by:

1. Validating the input arguments
2. Checking if the executable file exists
3. Creating a command to run objdump with appropriate options
4. Executing the command and redirecting output to the specified file
5. Providing success or error messages

## Error Handling

The program handles the following error scenarios:

- Missing command-line arguments
- Non-existent executable file
- Failed disassembly operation

## Sample Output

On successful execution:

```
Successfully disassembled '/bin/ls' to 'disassembly.txt'.
```

On error:

```
Error: Executable file '/bin/nonexistent' does not exist.
```

## Cleaning Up

To clean build artifacts:

```bash
make clean
```
