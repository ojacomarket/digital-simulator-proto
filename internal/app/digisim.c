#include "funcs.h"

_Bool digisim(uint64_t *rows, char *file, char *duration) {

    // Parse duration into number.
    char *e = NULL;
    uint64_t lifetime = strtol(duration, &e, 10);
    if (e == NULL || lifetime < 1 || lifetime > 1000) {
        return 1;
    }
    // Read a file, then simulate with exported data.
    unsigned char **buffer = readf(rows, (unsigned char *) file);
    LogicGate *allGates = lparse(buffer, *rows);
    simulate(allGates, *rows, &lifetime);
    return 0;
}