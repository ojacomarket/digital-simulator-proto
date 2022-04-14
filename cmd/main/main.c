#define DIGISIM
#include "../../internal/app/funcs.h"

extern _Bool cliHandler(int, char **);

/**
 * Digital simulator entry point.
 * @param argc terminal params amount
 * @param argv terminal params
 * @return 0 if file written, 1 if not (consider an error)
 */
int main(int argc, char **argv) {

    uint64_t fileRows = 0;
    if (cliHandler(argc, argv))
        return 1;
    digisim(&fileRows, argv[2], argv[4]);
    return 0;
}

