# Secure File Encryption

## Overview

This project implements a file encryption and decryption system using a symmetric encryption approach with a fixed key of 4. The encryption and decryption functionality is provided through a dynamically shared library, and a command-line tool allows users to encrypt and decrypt files with simple commands.

## Features

- Symmetric encryption with a fixed key (key value = 4)
- Dynamically shared library (.so) for encryption/decryption functions
- Command-line interface for encrypting and decrypting files
- File naming conventions:
  - Appends "_enc" to encrypted files
  - Appends "_dec" to decrypted files
- Support for processing multiple files at once
- Comprehensive error handling
- Binary file support (can encrypt any file type)

## Directory Structure

```
Q4_Encryption/
├── Makefile              # Build script
├── README.md             # This documentation
├── include/              # Header files directory
│   └── encryption.h      # Encryption library API declaration
├── src/                  # Source files directory
│   ├── encryption.c      # Encryption library implementation
│   └── file_encryptor.c  # Main program that uses the library
└── bin/                  # Binary output directory (created during build)
    └── file_encryptor    # Executable tool (after building)
```

## Requirements

- GCC compiler
- Linux/Unix environment

## Building

To build the encryption library and executable:

```bash
make
```

This will:
1. Compile the encryption library (`libencryption.so`)
2. Compile the file encryptor program
3. Link them together to create the final executable in the `bin` directory

## Usage

### Encrypting Files

```bash
./bin/file_encryptor encrypt <file1> [file2] ...
```

This will create encrypted versions of the specified files with "_enc" appended to their names.

### Decrypting Files

```bash
./bin/file_encryptor decrypt <file1_enc> [file2_enc] ...
```

This will create decrypted versions of the specified files with "_dec" appended to their names.

## Examples

```bash
# Encrypt two files
./bin/file_encryptor encrypt document.txt image.jpg

# This creates document_enc.txt and image_enc.jpg

# Decrypt the encrypted files
./bin/file_encryptor decrypt document_enc.txt image_enc.jpg

# This creates document_enc_dec.txt and image_enc_dec.jpg
```

## Testing

The Makefile includes a test target that:
1. Creates two test files with different content
2. Encrypts them
3. Decrypts them
4. Verifies that the decrypted files match the originals

To run the test:

```bash
make test
```

## Implementation Details

### Encryption Algorithm

The encryption uses a simple substitution cipher with a key value of 4:
- Each byte in the file is increased by 4 during encryption
- Each byte is decreased by 4 during decryption

This is a basic symmetric encryption approach designed for educational purposes.

### Library Design

The encryption functionality is implemented as a dynamically shared library (`libencryption.so`) that provides two main functions:
- `encrypt_file()`: Encrypts an input file and writes the result to an output file
- `decrypt_file()`: Decrypts an input file and writes the result to an output file

### Command-Line Tool

The `file_encryptor` program provides a user-friendly interface to the library functions, handling file operations, error checking, and output filename generation.

## Cleaning Up

To remove compiled files:

```bash
make clean
```

To remove test files:

```bash
make clean_test
```
