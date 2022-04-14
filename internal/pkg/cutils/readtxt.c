#define CUTILS

#include "cutils.h"

unsigned char **readf(uint64_t *rows, const unsigned char *file) {

    uint64_t r = 1; // track rows
    FILE *f = fopen((char *) file, "rt"); // read file
    if (f == NULL) {
        panic('f');
    }
    // Allocate memory for a buffer "b" and sub-elements.
    unsigned char **b = (unsigned char **) malloc(sizeof(char *) * REALLOC_THRESHOLD);
    *b = (unsigned char *) malloc(sizeof(char) * SIMPLE_TXT);
    // Loop until EOF.
    while (fgets((char *) b[*rows], (SIMPLE_TXT - 1), f)) {
        if (*rows == (SIMPLE_TXT - 1) * r) {  // need extra memory for entire "b"
            r++;
            b = realloc(b, sizeof(unsigned char *) * REALLOC_THRESHOLD * r);
        }
        *rows = *rows + 1;
        b[*rows] = (unsigned char *) malloc(sizeof(char) * SIMPLE_TXT); // memory alloc for next row
    }
    return b;
}