# Makefile for System Monitoring Tool

# Python settings
PYTHON = python3

# Directories
SRC_DIR = src
SCRIPT_DIR = scripts
BIN_DIR = bin

# Make sure the output directories exist
$(shell mkdir -p $(BIN_DIR))

.PHONY: all build install clean test help

# Default target
all: build

# Build the C extension
build:
	@echo "Building System Monitoring C extension..."
	@cd $(SRC_DIR) && $(PYTHON) setup.py build_ext --inplace
	@cp $(SRC_DIR)/sysmonitor*.so .
	@echo "Build complete."

# Install the extension (for system-wide use)
install:
	@echo "Installing System Monitoring C extension..."
	@cd $(SRC_DIR) && $(PYTHON) setup.py install
	@echo "Installation complete."

# Run the visualization script
run: build
	@echo "Running System Monitoring visualization..."
	@$(PYTHON) $(SCRIPT_DIR)/visualize.py

# Test the system monitoring extension
test: build
	@echo "Testing System Monitoring extension..."
	@$(PYTHON) -c "import sysmonitor; print(sysmonitor.monitor_system())"

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf build/
	@rm -f sysmonitor*.so
	@rm -f *.pyc
	@rm -rf __pycache__
	@rm -rf $(SRC_DIR)/__pycache__
	@rm -rf $(SRC_DIR)/build
	@rm -rf $(SCRIPT_DIR)/__pycache__
	@echo "Clean complete."

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the system monitoring extension (default)"
	@echo "  build   - Same as 'all'"
	@echo "  install - Install the extension system-wide"
	@echo "  run     - Run the visualization tool"
	@echo "  test    - Test if the extension works properly"
	@echo "  clean   - Clean build artifacts"
	@echo "  help    - Display this help message"
