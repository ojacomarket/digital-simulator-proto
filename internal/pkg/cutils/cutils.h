// Allows you to perform common tasks, such as reading a file, error handling.
#ifdef CUTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SIMPLE_TXT 100
#define REALLOC_THRESHOLD 1000

/**
 * Error handler.
 * @param e error type:'f' - read a file, 'p' - parse a file, 'w' - write to a file, 'i' - terminal input error
 */
extern void panic(unsigned char e);

/**
 * Read any sized txt file and store into buffer.
 * @param rows is a pointer to the integer, that will store rows # from a file
 * @param file name to read data from
 * @return buffer
 */
extern unsigned char **readf(uint64_t *rows, const unsigned char *file);

#endif