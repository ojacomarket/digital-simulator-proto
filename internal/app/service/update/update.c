#include "../../funcs.h"

void lupdate(LogicGate *system, uint64_t systemElements, uint64_t timer, FILE* ptr) {

    uint64_t expires = 0;
    for (int i = 0; i < systemElements; ++i) {

        if (system[i].buffer.value != system[i].out.value && !system[i].isBufferChanged &&
            system[i].type != gen) {
            system[i].isBufferChanged = 1;
            system[i].changesAt = timer + system[i].delay;
        } else if (system[i].type == gen) {
            if ((system[i].changesAt + system[i].delay) == timer) {
                system[i].out.value = system[i].out.value + 1;
                system[i].changesAt = timer;
            }
        }

        run(*system[i].in, &system[i].buffer, system[i].inPins,
            system[i].type);
        if (system[i].changesAt == timer && timer > 0 && system[i].type != gen) {
            if (expires != timer) {
                fprintf(ptr, "\n#%lu\n", timer);
                expires = timer;
            }
            fprintf(ptr, "%d%s\n", system[i].out.value, system[i].name);
            system[i].out.value = system[i].buffer.value;
            system[i].isBufferChanged = 0;
        }
    }
}