#include "../../funcs.h"

uint64_t lindex(size_t *p, size_t *s, uint64_t size) {

    uint8_t absent;
    for (int i = 0; i < size; ++i) {
        absent = strcmp((const char *) p, (const char *) s[i]);
        if (!absent) {
            return i;
        }
    }
    return size;
}
