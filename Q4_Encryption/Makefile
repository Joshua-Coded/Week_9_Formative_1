# Makefile for File Encryption System

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC
LDFLAGS = -L. -lencryption -Wl,-rpath,.

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
OBJ_DIR = obj

# Files
LIB = libencryption.so
TARGET = $(BIN_DIR)/file_encryptor
LIB_SRC = $(SRC_DIR)/encryption.c
MAIN_SRC = $(SRC_DIR)/file_encryptor.c
LIB_OBJ = $(OBJ_DIR)/encryption.o
MAIN_OBJ = $(OBJ_DIR)/file_encryptor.o

# Make sure the output directories exist
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

.PHONY: all clean test help

# Default target
all: $(LIB) $(TARGET)

# Build the shared library
$(LIB): $(LIB_OBJ)
	@echo "Building shared library $@..."
	@$(CC) -shared -o $@ $<
	@echo "Shared library built."

# Build the main executable
$(TARGET): $(MAIN_OBJ) $(LIB)
	@echo "Building executable $@..."
	@$(CC) -o $@ $< $(LDFLAGS)
	@echo "Executable built."

# Compile library source
$(LIB_OBJ): $(LIB_SRC)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile main program source
$(MAIN_OBJ): $(MAIN_SRC)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Create test files
test_files:
	@echo "Creating test files..."
	@echo "This is a test file for encryption." > test1.txt
	@echo "This is another test file with different content." > test2.txt
	@echo "Test files created."

# Test encryption and decryption
test: all test_files
	@echo "Testing encryption..."
	@$(TARGET) encrypt test1.txt test2.txt
	@echo "Testing decryption..."
	@$(TARGET) decrypt test1_enc.txt test2_enc.txt
	@echo "Verifying decrypted files..."
	@echo "test1.txt compared to test1_dec.txt:"
	@diff test1.txt test1_dec.txt && echo "Files are identical."
	@echo "test2.txt compared to test2_dec.txt:"
	@diff test2.txt test2_dec.txt && echo "Files are identical."

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -f $(LIB) $(TARGET) $(LIB_OBJ) $(MAIN_OBJ)
	@echo "Clean complete."

# Clean test files
clean_test:
	@echo "Cleaning test files..."
	@rm -f test*.txt
	@echo "Test files cleaned."

# Help target
help:
	@echo "Available targets:"
	@echo "  all        - Build the shared library and executable (default)"
	@echo "  test_files - Create test files for encryption/decryption"
	@echo "  test       - Test encryption and decryption with sample files"
	@echo "  clean      - Clean build artifacts"
	@echo "  clean_test - Clean test files"
	@echo "  help       - Display this help message"
