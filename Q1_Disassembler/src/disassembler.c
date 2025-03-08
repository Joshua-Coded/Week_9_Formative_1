/**
 * File: disassembler.c
 * Description: A program that disassembles an executable C file and writes the
 *              disassembled content to a text file.
 * 
 * This tool provides a simple interface to objdump, allowing users to disassemble
 * ELF binaries and save the output to a text file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Disassembles an executable file and writes the output to a text file.
 * 
 * @param executable_file Name of the executable file to disassemble
 * @param output_file Name of the file to write the disassembled content to
 * @return 0 on success, non-zero on failure
 */
int disassemble_file(const char *executable_file, const char *output_file) {
    // Check if the executable file exists
    if (access(executable_file, F_OK) != 0) {
        fprintf(stderr, "Error: Executable file '%s' does not exist.\n", executable_file);
        return 1;
    }

    // Create the objdump command with proper escaping
    char command[512];
    snprintf(command, sizeof(command), "objdump -d \"%s\" > \"%s\"", 
             executable_file, output_file);
    
    // Execute the command
    int result = system(command);
    
    // Check if the command executed successfully
    if (result != 0) {
        fprintf(stderr, "Error: Failed to disassemble file '%s'.\n", executable_file);
        return 1;
    }
    
    printf("Successfully disassembled '%s' to '%s'.\n", executable_file, output_file);
    return 0;
}

/**
 * Main function - entry point of the program.
 * 
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 * @return 0 on success, non-zero on failure
 */
int main(int argc, char *argv[]) {
    // Check if correct number of arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <executable_file> <output_file>\n", argv[0]);
        return 1;
    }
    
    const char *executable_file = argv[1];
    const char *output_file = argv[2];
    
    // Perform the disassembly
    return disassemble_file(executable_file, output_file);
}
