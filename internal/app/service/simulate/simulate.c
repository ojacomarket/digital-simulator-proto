#include "../../funcs.h"

void simulate (LogicGate *system, uint64_t systemElements, const uint64_t *lifetime) {
    FILE* ptr = output(system, systemElements);
    for (int clock = 0; clock < *lifetime; ++clock) {
        lupdate(system, systemElements, clock, ptr);
    }
}

