# Main Makefile for Week_9_Formative_1
# This Makefile builds all four components of the Linux programming assignment

# Define directories
Q1_DIR = Q1_Disassembler
Q2_DIR = Q2_Calculator
Q3_DIR = Q3_SysMonitor
Q4_DIR = Q4_Encryption

.PHONY: all clean disassembler calculator sysmonitor encryption

# Default target - build all components
all: disassembler calculator sysmonitor encryption

# Build the disassembler component
disassembler:
	@echo "Building ELF Binary Disassembler..."
	@$(MAKE) -C $(Q1_DIR)
	@echo "Disassembler build complete."

# Build the calculator component
calculator:
	@echo "Building Assembly Calculator..."
	@$(MAKE) -C $(Q2_DIR)
	@echo "Calculator build complete."

# Build the system monitoring tool
sysmonitor:
	@echo "Building System Monitoring Tool..."
	@$(MAKE) -C $(Q3_DIR)
	@echo "System Monitor build complete."

# Build the encryption library and tool
encryption:
	@echo "Building File Encryption System..."
	@$(MAKE) -C $(Q4_DIR)
	@echo "Encryption system build complete."

# Clean all builds
clean:
	@echo "Cleaning all builds..."
	@$(MAKE) -C $(Q1_DIR) clean
	@$(MAKE) -C $(Q2_DIR) clean
	@$(MAKE) -C $(Q3_DIR) clean
	@$(MAKE) -C $(Q4_DIR) clean
	@echo "Clean complete."

# Help target
help:
	@echo "Available targets:"
	@echo "  all         - Build all components (default)"
	@echo "  disassembler - Build just the ELF Binary Disassembler"
	@echo "  calculator   - Build just the Assembly Calculator"
	@echo "  sysmonitor   - Build just the System Monitoring Tool"
	@echo "  encryption   - Build just the File Encryption System"
	@echo "  clean        - Clean all builds"
	@echo "  help         - Display this help message"
