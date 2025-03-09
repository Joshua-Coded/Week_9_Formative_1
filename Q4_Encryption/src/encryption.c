/**
 * File: encryption.c
 * Description: Shared library that provides symmetric encryption and decryption
 *              functions for files using a fixed key of 4.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/encryption.h"

/**
 * Encrypts a file using a symmetric key of 4.
 * 
 * @param input_filename The name of the file to encrypt
 * @param output_filename The name of the file to write the encrypted content to
 * @return 0 on success, non-zero on failure
 */
int encrypt_file(const char *input_filename, const char *output_filename) {
    FILE *input_file, *output_file;
    char buffer[1024];
    size_t bytes_read;
    const int KEY = 4;  // Symmetric key
    
    // Open the input file for reading
    input_file = fopen(input_filename, "rb");
    if (!input_file) {
        fprintf(stderr, "Error: Unable to open input file '%s'.\n", input_filename);
        return 1;
    }
    
    // Open the output file for writing
    output_file = fopen(output_filename, "wb");
    if (!output_file) {
        fprintf(stderr, "Error: Unable to create output file '%s'.\n", output_filename);
        fclose(input_file);
        return 1;
    }
    
    // Read and encrypt the file in chunks
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
        // Encrypt each byte using the key
        for (size_t i = 0; i < bytes_read; i++) {
            buffer[i] = buffer[i] + KEY;
        }
        
        // Write the encrypted data to the output file
        if (fwrite(buffer, 1, bytes_read, output_file) != bytes_read) {
            fprintf(stderr, "Error: Failed to write to output file.\n");
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
    }
    
    // Close the files
    fclose(input_file);
    fclose(output_file);
    
    printf("File '%s' encrypted successfully to '%s'.\n", input_filename, output_filename);
    return 0;
}

/**
 * Decrypts a file that was encrypted using the encrypt_file function.
 * 
 * @param input_filename The name of the encrypted file
 * @param output_filename The name of the file to write the decrypted content to
 * @return 0 on success, non-zero on failure
 */
int decrypt_file(const char *input_filename, const char *output_filename) {
    FILE *input_file, *output_file;
    char buffer[1024];
    size_t bytes_read;
    const int KEY = 4;  // Symmetric key
    
    // Open the input file for reading
    input_file = fopen(input_filename, "rb");
    if (!input_file) {
        fprintf(stderr, "Error: Unable to open input file '%s'.\n", input_filename);
        return 1;
    }
    
    // Open the output file for writing
    output_file = fopen(output_filename, "wb");
    if (!output_file) {
        fprintf(stderr, "Error: Unable to create output file '%s'.\n", output_filename);
        fclose(input_file);
        return 1;
    }
    
    // Read and decrypt the file in chunks
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
        // Decrypt each byte using the key
        for (size_t i = 0; i < bytes_read; i++) {
            buffer[i] = buffer[i] - KEY;
        }
        
        // Write the decrypted data to the output file
        if (fwrite(buffer, 1, bytes_read, output_file) != bytes_read) {
            fprintf(stderr, "Error: Failed to write to output file.\n");
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
    }
    
    // Close the files
    fclose(input_file);
    fclose(output_file);
    
    printf("File '%s' decrypted successfully to '%s'.\n", input_filename, output_filename);
    return 0;
}
