#include "funcs.h"

_Bool digisim(uint64_t *fileRows, char *filename, char *duration) {

    char *e = NULL;
    uint64_t lifetime = strtol(duration, &e, 10);
    if (e == NULL || lifetime < 1 || lifetime > 1000) {
        return 1;
    }
    unsigned char **buffer = readf(fileRows, (unsigned char *) filename);
    LogicGate *allGates = lparse(buffer, *fileRows);
    simulate(allGates, *fileRows, &lifetime);
    return 0;
}