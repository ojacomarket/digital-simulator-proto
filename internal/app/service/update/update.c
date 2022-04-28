#include "../../funcs.h"

void lrun(LogicGate *g, uint64_t s) {
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            run(g[j].in, &g[j].out, g[j].inPins,
                g[j].type);
        }
        run(g[i].in, &g[i].out, g[i].inPins,
            g[i].type);
        printf("Name: %s...Buffer: %d\n", g[i].name, g[i].out.value);
    }
}

void lupdate(LogicGate *g, uint64_t s, uint64_t timer, FILE *f) {
    uint8_t fire = 0;
    uint8_t changes = 1;
    while (changes) {
        printf("Changes made...%d\n", changes);
        changes = 0;
        for (int i = 0; i < s; ++i) {
            // Calculate gate buffer.
            // for (int j = 0; j < s; ++j) {
            run(g[i].in, &g[i].buffer, g[i].inPins,
                g[i].type);
           //  }
            //   printf("Timer: %lu\nGate: %s\nOut: %d\nBuf: %d\n", timer, g[i].name, g[i].out.value, g[i].buffer.value);
            // Value have been changed and gate isn't a gen.
            if (g[i].buffer.value != g[i].out.value && !g[i].isBufferChanged &&
                g[i].type != gen) {
                printf("ROUND!\n");
                g[i].isBufferChanged = 1;
                g[i].changesAt = timer + g[i].delay;
                //      printf("Timer: %lu\nGate: %s\nOut: %d\nBuf: %d\n", timer, g[i].name, g[i].out.value, g[i].buffer.value);
                //        printf("Changes at: %lu\nIsChanged? %d\n", g[i].changesAt, g[i].isBufferChanged);
            }
                /* if (g[i].changesAt == timer && g[i].isBufferChanged && g[i].type != gen) {
                     g[i].out.value = g[i].buffer.value;
                     g[i].isBufferChanged = 0;
                     if (fire == 0) {
                         fprintf(f, "\n#%lu\n", timer);
                         fire = 1;
                     }
                     fprintf(f, "%d%s\n", g[i].out.value, g[i].name);
                 }*/
                // Gate is gen.
            else if (g[i].type == gen) {
                if ((g[i].changesAt + g[i].delay) == timer) {
                    g[i].out.value = g[i].out.value + 1;
                    g[i].changesAt = timer;
                    changes++;
                    if (fire == 0) {
                        fprintf(f, "\n#%lu\n", timer);
                        fire = 1;
                    }
                    fprintf(f, "%d%s\n", g[i].out.value, g[i].name);
                }
            }

                if (g[i].changesAt == timer && g[i].isBufferChanged && g[i].type != gen) {
                    g[i].out.value = g[i].buffer.value;
                    g[i].isBufferChanged = 0;
                    printf("Name...%s...Out...%d...Buf...%d\n",g[i].name, g[i].out.value, g[i].buffer.value);
                    changes++;
                    if (fire == 0) {
                        fprintf(f, "\n#%lu\n", timer);
                        fire = 1;
                    }
                    fprintf(f, "%d%s\n", g[i].out.value, g[i].name);
                }
            //  printf("\nChanges at: %lu\nIsChanged? %d\n", g[i].changesAt, timer, g[i].isBufferChanged);
            // If delay has expired and change had been occurred, then set output = buffer value.
            //  printf("---------- END ---------\n");
        }
    }
    printf("---------------------------\n\n");
}

void lchange(LogicGate *g, uint64_t s, uint64_t timer, FILE *f) {
            // Gate is gen.
        /*else if (g[i].type == gen) {
            if ((g[i].changesAt + g[i].delay) == timer) {
                g[i].out.value = g[i].out.value + 1;
                g[i].changesAt = timer;
                if (fire == 0) {
                    fprintf(f, "\n#%lu\n", timer);
                    fire = 1;
                }
                fprintf(f, "%d%s\n", g[i].out.value, g[i].name);
            }
        }*/
    //}
}
//printf("\n---------- CHANGE ----------\n");
/*    for (int i = 0; i < s; ++i) {
        if (g[i].changesAt == timer && g[i].isBufferChanged && g[i].type != gen) {
            g[i].out.value = g[i].buffer.value;
            g[i].isBufferChanged = 0;
            if (*fire == 0) {
                fprintf(f, "\n#%lu\n", timer);
                *fire = 1;
            }
            fprintf(f, "%d%s\n", g[i].out.value, g[i].name);
        }
            // Gate is gen.
        else if (g[i].type == gen) {
            if ((g[i].changesAt + g[i].delay) == timer) {
                g[i].out.value = g[i].out.value + 1;
                g[i].changesAt = timer;
                if (*fire == 0) {
                    fprintf(f, "\n#%lu\n", timer);
                    *fire = 1;
                }
                fprintf(f, "%d%s\n", g[i].out.value, g[i].name);
            }
        }*/
//}
//printf("---------- END ----------\n");
