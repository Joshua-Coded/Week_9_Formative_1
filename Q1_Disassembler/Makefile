# Makefile for ELF Binary Disassembler

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS =

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
OBJ_DIR = obj

# Files
TARGET = $(BIN_DIR)/disassembler
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Make sure the output directories exist
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

.PHONY: all clean

# Default target
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJ)
	@echo "Linking $@..."
	@$(CC) $(LDFLAGS) -o $@ $^

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BIN_DIR) $(OBJ_DIR)
	@echo "Clean complete."

# Help target
help:
	@echo "Available targets:"
	@echo "  all   - Build the disassembler (default)"
	@echo "  clean - Clean build artifacts"
	@echo "  help  - Display this help message"
