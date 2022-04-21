#include "../../funcs.h"

void lupdate(LogicGate *g, uint64_t s, uint64_t timer, FILE *f) {

    uint64_t expires = 0;
    for (int i = 0; i < s; ++i) {
        // Value have been changed and gate isn't a gen.
        if (g[i].buffer.value != g[i].out.value && !g[i].isBufferChanged &&
            g[i].type != gen) {
            g[i].isBufferChanged = 1;
            g[i].changesAt = timer + g[i].delay;
        }
            // Gate is gen.
        else if (g[i].type == gen) {
            if ((g[i].changesAt + g[i].delay) == timer) {
                if (expires != timer) {
                    fprintf(f, "\n#%lu\n", timer);
                    expires = timer;
                }
                fprintf(f, "%d%s\n", g[i].out.value, g[i].name);
                g[i].out.value = g[i].out.value + 1;
                g[i].changesAt = timer;
            }
        }
        // Calculate gate buffer.
        run(*g[i].in, &g[i].buffer, g[i].inPins,
            g[i].type);
        // If delay has expired and change had been occurred, then set output = buffer value.
        if (g[i].changesAt == timer && timer > 0 && g[i].type != gen) {
            if (expires != timer) {
                fprintf(f, "\n#%lu\n", timer);
                expires = timer;
            }
            fprintf(f, "%d%s\n", g[i].out.value, g[i].name);
            g[i].out.value = g[i].buffer.value;
            g[i].isBufferChanged = 0;
        }
    }
}