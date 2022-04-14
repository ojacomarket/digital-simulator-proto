#define DIGISIM

#include "../../internal/app/funcs.h"

/**
 * Check terminal params.
 * @param args # of terminal arguments
 * @param cli terminal arguments
 * @return 0 if ok, 1 if error
 */
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
    return digisim(&fileRows, argv[2], argv[4]);;
}

