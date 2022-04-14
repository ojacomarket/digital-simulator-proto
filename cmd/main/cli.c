#include "../../internal/app/funcs.h"

/**
 * Terminal output "how to".
 */
extern void usage();

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

void usage() {

    printf("digisim: usage: \"digisim -f <file> --simulate <duration>\"\n");
}
