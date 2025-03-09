# Assembly Calculator

## Overview

This is an x86_64 assembly program that implements a calculator with addition, subtraction, multiplication, division, and modulus operations. Each operation is implemented as a separate function (procedure), demonstrating modular assembly programming.

## Features

- Implements five basic arithmetic operations:
  - Addition
  - Subtraction
  - Multiplication
  - Division
  - Modulus
- Modular design with separate functions for each operation
- Interactive menu interface
- Input validation
- Error handling for division by zero
- Clear, well-commented assembly code

## Directory Structure

```
Q2_Calculator/
├── Makefile              # Build script
├── README.md             # This documentation
├── include/              # Header files directory (empty for assembly)
└── src/                  # Source files directory
    └── calculator.asm    # Assembly source code
```

## Requirements

- NASM assembler
- GCC compiler (for linking)
- x86_64 architecture
- Linux operating system

## Building

To build the calculator:

```bash
make
```

This will assemble the source file, link it, and create an executable named `calculator` in the bin directory.

## Usage

To run the calculator:

```bash
./bin/calculator
```

### Interactive Menu

The program displays a menu with options:
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulus
0. Exit

After selecting an operation, you'll be prompted to enter two numbers, and the result will be displayed.

### Example Session

```
Calculator Menu:
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulus
0. Exit
Enter choice (0-5): 1
Enter first number: 25
Enter second number: 17
Result: 42

Calculator Menu:
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulus
0. Exit
Enter choice (0-5): 4
Enter first number: 100
Enter second number: 5
Result: 20

Calculator Menu:
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Modulus
0. Exit
Enter choice (0-5): 0
```

## Implementation Details

The calculator is implemented using x86_64 assembly language with the following features:

1. **Main Menu Loop**: Continuously displays options and processes user input
2. **Function-Based Design**: Each arithmetic operation is implemented as a separate procedure
3. **Standard Function Calling**: Uses the x86_64 calling convention
4. **External C Functions**: Uses printf and scanf from the C library for I/O
5. **Error Handling**: Prevents division by zero and validates user input

## Code Structure

The assembly code is organized into the following sections:

- **Data Section**: Contains constant strings and message definitions
- **BSS Section**: Reserves space for variables
- **Text Section**: Contains the executable code:
  - `main`: Main program loop and menu handling
  - `addition`: Function for adding two numbers
  - `subtraction`: Function for subtracting two numbers
  - `multiplication`: Function for multiplying two numbers
  - `division`: Function for dividing two numbers
  - `modulus`: Function for calculating remainder

## Cleaning Up

To clean build artifacts:

```bash
make clean
```
