#include "../../funcs.h"

uint64_t lname(size_t *p, LogicGate *g, uint64_t size) {

    uint8_t absent;
    for (int i = 0; i < size; ++i) {
        absent = strcmp((const char *) p, (const char *) g[i].name);
        if (!absent) {
            return i;
        }
    }
    return size;
}
