#include "../../internal/app/funcs.h"

extern void usage();

/**
 * Check terminal params.
 * @param arguments amount
 * @param arguments
 * @return 0 if ok, 1 if error
 */
_Bool cliHandler(int args, char **cli) {

    if (args != 5) {
        usage();
        return 1;
    }
    if (strcmp("-f", cli[1]) != 0 || strcmp("--simulate", cli[3]) != 0) {
        usage();
        return 1;
    }
    return 0;
}

/**
 * Terminal output "how to".
 */
void usage() {

    printf("digisim: usage: \"digisim -f <file> --simulate <duration>\"\n");
}
