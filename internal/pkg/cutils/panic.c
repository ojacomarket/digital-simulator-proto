#define CUTILS

#include "cutils.h"

void panic(unsigned char e) {
    switch (e) {
        case 'f':
            printf("\ncannot read a file\n");
            exit(1);
        case 'p':
            printf("\nunexpected characters were found in a file\n");
            exit(1);
        case 'w':
            printf("\ncannot write to the file\n");
            exit(1);
        case 'i':
            printf("\ncannot process user input\n");
            exit(1);
        default:
            printf("\ncannot handle error type -> [ %c ]\n", e);
            exit(1);
    }
}
