/**
 * File: file_encryptor.c
 * Description: Program that uses the encryption library to encrypt and decrypt
 *              files in the current directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../include/encryption.h"

/**
 * Checks if a file exists
 * 
 * @param filename The name of the file to check
 * @return 1 if the file exists, 0 otherwise
 */
int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

/**
 * Creates the output filename by appending a suffix to the input filename
 * 
 * @param input_filename The input filename
 * @param suffix The suffix to append (e.g., "_enc" or "_dec")
 * @param output_filename Buffer to store the output filename
 * @param buffer_size Size of the output_filename buffer
 */
void create_output_filename(const char *input_filename, const char *suffix, 
                           char *output_filename, size_t buffer_size) {
    // Extract the base filename without extension
    char base_name[256] = {0};
    char extension[64] = {0};
    
    // Find the last dot to separate extension
    const char *last_dot = strrchr(input_filename, '.');
    const char *last_slash = strrchr(input_filename, '/');
    
    if (last_slash == NULL) {
        last_slash = input_filename;
    } else {
        last_slash++; // Skip the slash
    }
    
    if (last_dot == NULL || last_dot < last_slash) {
        // No extension or dot is part of the path
        strncpy(base_name, last_slash, sizeof(base_name) - 1);
        extension[0] = '\0';
    } else {
        // Copy the base name (without extension)
        size_t base_len = last_dot - last_slash;
        strncpy(base_name, last_slash, base_len);
        base_name[base_len] = '\0';
        
        // Copy the extension (including the dot)
        strncpy(extension, last_dot, sizeof(extension) - 1);
    }
    
    // Create the output filename
    snprintf(output_filename, buffer_size, "%s%s%s", base_name, suffix, extension);
}

/**
 * Processes files in the current directory for encryption or decryption
 * 
 * @param mode 1 for encryption, 2 for decryption
 * @param filenames Array of filenames to process
 * @param num_files Number of files in the array
 * @return 0 on success, non-zero on failure
 */
int process_files(int mode, char **filenames, int num_files) {
    if (num_files == 0) {
        fprintf(stderr, "Error: No files specified for processing.\n");
        return 1;
    }
    
    for (int i = 0; i < num_files; i++) {
        const char *input_filename = filenames[i];
        char output_filename[512];
        
        // Check if input file exists
        if (!file_exists(input_filename)) {
            fprintf(stderr, "Error: File '%s' does not exist.\n", input_filename);
            continue;
        }
        
        if (mode == 1) {
            // Encryption mode
            create_output_filename(input_filename, "_enc", output_filename, sizeof(output_filename));
            encrypt_file(input_filename, output_filename);
        } else {
            // Decryption mode
            create_output_filename(input_filename, "_dec", output_filename, sizeof(output_filename));
            decrypt_file(input_filename, output_filename);
        }
    }
    
    return 0;
}

/**
 * Displays usage information
 * 
 * @param program_name Name of the program
 */
void show_usage(const char *program_name) {
    printf("Usage: %s <mode> <file1> [file2] ...\n", program_name);
    printf("Modes:\n");
    printf("  encrypt    Encrypt the specified files\n");
    printf("  decrypt    Decrypt the specified files\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s encrypt file1.txt file2.txt\n", program_name);
    printf("  %s decrypt file1_enc.txt file2_enc.txt\n", program_name);
}

/**
 * Main function
 */
int main(int argc, char *argv[]) {
    // Check if enough arguments are provided
    if (argc < 3) {
        show_usage(argv[0]);
        return 1;
    }
    
    // Determine the operation mode
    int mode = 0;
    if (strcmp(argv[1], "encrypt") == 0) {
        mode = 1;
    } else if (strcmp(argv[1], "decrypt") == 0) {
        mode = 2;
    } else {
        fprintf(stderr, "Error: Invalid mode '%s'.\n", argv[1]);
        show_usage(argv[0]);
        return 1;
    }
    
    // Process the files
    return process_files(mode, &argv[2], argc - 2);
}
