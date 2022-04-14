#define CUTILS

#include "cutils.h"

unsigned char **readf(uint64_t *fileRows, const unsigned char *filename) {

    // 1. Rows tracker used to track, when file row is ended.
    int rowsTracker = 1;

    // 2. Open a file.
    FILE *file_p = fopen((char *) filename, "rt");

    // 3. Handle error, if cannot open a file.
    if (file_p == NULL) {
        panic('f');
    }

    // 4. Allocate memory for a buffer and sub-elements.
    unsigned char **buffer = (unsigned char **) malloc(sizeof(char *) * REALLOC_THRESHOLD);
    *buffer = (unsigned char *) malloc(sizeof(char) * SIMPLE_TXT);

    // 5. Loop until all data is red from a file (EOF).
    while (fgets((char *) buffer[*fileRows], (SIMPLE_TXT - 1), file_p)) {

        // 5.1. If we exceed our initial memory limit, then ask for extra.
        if (*fileRows == (SIMPLE_TXT - 1) * rowsTracker) {
            rowsTracker++;
            buffer = realloc(buffer, sizeof(unsigned char *) * REALLOC_THRESHOLD * rowsTracker);
        }

        // 5.2. Allocate memory for each row (dynamica array).
        *fileRows = *fileRows + 1;
        buffer[*fileRows] = (unsigned char *) malloc(sizeof(char) * SIMPLE_TXT);
    }

    return buffer;
}

