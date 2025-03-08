# System Programming Toolkit

A comprehensive set of system-level programming tools implementing various low-level operations in C, Assembly, and Python. This project was developed as part of the ALU Linux Programming course.

## Project Components

### 1. ELF Binary Disassembler

A C program that disassembles executable files and outputs the assembly code to a text file for analysis.

**Features:**
- Command-line interface for easy usage
- Uses objdump for reliable disassembly
- Error handling for file access and processing
- Clear output formatting

**Usage:**
```bash
./disassembler <executable_file> <output_file>
```

### 2. Assembly Calculator

A modular calculator implemented in x86_64 assembly language that performs basic arithmetic operations.

**Operations:**
- Addition
- Subtraction
- Multiplication
- Division
- Modulus

**Features:**
- Modular design with separate procedures for each operation
- Interactive menu interface
- Input validation and error handling (e.g., division by zero)
- Clean code structure with comments

### 3. System Monitoring Tool

A real-time system resource monitoring tool built using a custom C extension for Python, providing accurate system metrics with minimal overhead.

**Monitored Resources:**
- CPU usage (%)
- Memory usage (%)
- Network traffic (upload/download speeds)

**Features:**
- C extension for efficient data collection
- 2-second sampling interval for accurate measurements
- Real-time graphical visualization using matplotlib
- Multi-threaded operation

**Dependencies:**
- Python 3.x
- matplotlib
- numpy

### 4. Secure File Encryption

A file encryption and decryption system using a symmetric key approach implemented as a shared library.

**Features:**
- Symmetric encryption with a fixed key (4)
- Works on any file type (binary or text)
- Implemented as a shared library (.so) for reuse
- Automated file naming convention (appends "_enc" or "_dec")

**Usage:**
```bash
./file_encryptor encrypt <filename>
./file_encryptor decrypt <encrypted_filename>
```

## Building and Installation

### Prerequisites
- GCC compiler
- NASM assembler
- Python 3.x with development headers
- make

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- African Leadership University (ALU) Linux Programming Course
- The GNU Project for the essential tools used in development
