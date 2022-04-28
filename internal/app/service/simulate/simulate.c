#include "../../funcs.h"

void simulate (LogicGate *system, uint64_t systemElements, const uint64_t *lifetime) {

    FILE* ptr = output(system, systemElements);
    uint8_t fire = 0;
    for (int clock = 0; clock < *lifetime; ++clock) {
        printf("==== TIME: %d ====\n", clock);
     //   lrun(system, systemElements);
        lupdate(system, systemElements, clock, ptr);
     //   lchange(system, systemElements, clock, ptr);
        printf("\n");
    }
}

