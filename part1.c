#define AUTHORIZED_2

#include "funcs.h"

Gate *digitalSimulator(uint64_t *bufferLines, char **argv) {

    unsigned char **buffer = readFile(bufferLines, (unsigned char *) argv[2]);

    /** Debugger: Uncomment to see what is actually been red from a file. **/
    /*
    for (int i = 0; i < *buffer_content; ++i) {
        printf("%s\n", buf[i]);
    }
    */

    /** Debugger: Uncomment to see parsed logic gate names into struct. **/
    /*
    Gate *array = createLogicGates(buffer, *bufferLines);
    for (int i = 0; i < *bufferLines; ++i) {
        printf("%s\n", array[i].name);
    }
    */

    Gate *logicGateArray = fillLogicGates(buffer, *bufferLines);

    runSimulator(logicGateArray, *bufferLines);

    return logicGateArray;
}