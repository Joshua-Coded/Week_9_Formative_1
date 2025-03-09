/**
 * File: encryption.h
 * Description: Header file for the encryption/decryption library.
 */

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

/**
 * Encrypts a file using a symmetric key of 4.
 * 
 * @param input_filename The name of the file to encrypt
 * @param output_filename The name of the file to write the encrypted content to
 * @return 0 on success, non-zero on failure
 */
int encrypt_file(const char *input_filename, const char *output_filename);

/**
 * Decrypts a file that was encrypted using the encrypt_file function.
 * 
 * @param input_filename The name of the encrypted file
 * @param output_filename The name of the file to write the decrypted content to
 * @return 0 on success, non-zero on failure
 */
int decrypt_file(const char *input_filename, const char *output_filename);

#endif /* ENCRYPTION_H */
