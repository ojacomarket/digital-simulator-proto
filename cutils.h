#ifdef CUTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/** readtxt **/
#define SIMPLE_TXT 100
#define SCIENTIFIC_TXT 500
#define REALLOC_THRESHOLD 1000
/*************/

/**
 * Error handler.
 * @param error 'f' - read a file, 'p' - parse a file, 'w' - write to a file
 */
void panic(unsigned char error);

/**
 * Read any sized txt file and store into buffer.
 * @param fileRows Pointer to the integer, that will store rows # from a file.
 * @param filename File name to read data from.
 * @return Buffer.
 */
unsigned char **readFile(uint64_t *fileRows, const unsigned char *filename);

#endif