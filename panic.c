#define CUTILS

#include "cutils.h"

void panic(unsigned char error) {

    switch (error) {
        case 'f': // reading a file.
            printf("\ncannot read a file\n");
            exit(1);
        case 'p': // parsing data from a file.
            printf("\nunexpected character found in a file\n");
            exit(1);
        case 'w':
            printf("\ncannot write to the file\n");
            exit(1);
        case 'i':
            printf("\ncannot process user input\n");
            exit(1);
        default:
            printf("\ncannot handle error type -> [ %c ]\n", error);
            exit(1);
    }
}
