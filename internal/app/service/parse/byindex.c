#include "../../funcs.h"

uint64_t lindex(size_t *pattern, size_t *source, uint64_t size) {

    uint8_t coincidence;
    for (int i = 0; i < size; ++i) {

        // We check logic gate type from pre-defined list of logic gates.
        coincidence = strcmp((const char *) pattern, (const char *) source[i]);

        // If logic gate type is valid.
        if (!coincidence) {
            return i;
        }
    }
    return size;
}
