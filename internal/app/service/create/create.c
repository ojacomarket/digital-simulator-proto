#include "../../funcs.h"
LogicGate *lcreate(unsigned char **buffer, uint64_t lines,
                   const unsigned char LUT[]) {

    // 1. Allocate and initialize memory for a dynamic struct array.
    LogicGate *logicGatesArray = calloc(lines, sizeof(LogicGate));

    // 2. Create a variable, that will track ASCII symbols in a logic gate name.
    uint8_t name_len = 0;

    // 3. Loop until all lines in a buffer are red.
    for (int i = 0; i < lines; ++i, name_len = 0) {

        // 3.1 Loop until "Space" character is met.
        for (int j = 0; buffer[i][j] != 32; ++j) {

            // 3.1.1 Match symbol from buffer to the Lookup table.
            switch (LUT[buffer[i][j]]) {

                case STATE << 0: // A-Za-z.
                logicGatesArray[i].name[j] = buffer[i][j]; // Write name into struct array.
                name_len++; // Go to next symbol.
                break;

                case STATE << 1: // 0-9.
                logicGatesArray[i].name[j] = buffer[i][j]; // Write name into struct array.
                name_len++; // Go to next symbol.
                break;

                default: // If wrong symbol is met (prohibited).
                panic('f');
            }
        }

        // 4. Add line terminator to the end of a logic gate name.
        logicGatesArray[i].name[name_len] = '\0';
    }

    return logicGatesArray;
}