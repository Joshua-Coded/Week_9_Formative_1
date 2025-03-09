# Makefile for Assembly Calculator

# Tools and flags
ASM = nasm
ASMFLAGS = -f elf64
CC = gcc
LDFLAGS = -no-pie  # Added -no-pie to fix linking issues

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
OBJ_DIR = obj

# Files
TARGET = $(BIN_DIR)/calculator
ASM_SRC = $(wildcard $(SRC_DIR)/*.asm)
OBJ = $(patsubst $(SRC_DIR)/%.asm,$(OBJ_DIR)/%.o,$(ASM_SRC))

# Make sure the output directories exist
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

.PHONY: all clean

# Default target
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJ)
	@echo "Linking $@..."
	@$(CC) $(LDFLAGS) -o $@ $^

# Assemble source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	@echo "Assembling $<..."
	@$(ASM) $(ASMFLAGS) -I$(INCLUDE_DIR) $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BIN_DIR) $(OBJ_DIR)
	@echo "Clean complete."

# Help target
help:
	@echo "Available targets:"
	@echo "  all   - Build the calculator (default)"
	@echo "  clean - Clean build artifacts"
	@echo "  help  - Display this help message"
