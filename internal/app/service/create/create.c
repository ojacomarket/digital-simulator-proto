#include "../../funcs.h"

LogicGate *lcreate(unsigned char **buffer, uint64_t r, const unsigned char LUT[]) {

    // Allocate and initialize memory for a dynamic struct array.
    LogicGate *arr = calloc(r, sizeof(LogicGate));
    uint8_t ascii = 0; // gate name tracker as an ASCII symbol
    // Loop rows.
    for (int i = 0; i < r; ++i, ascii = 0) {
        // Loop until 'space' is met.
        for (int j = 0; buffer[i][j] != 32; ++j) {
            // Match symbol from buffer to the Lookup table.
            switch (LUT[buffer[i][j]]) {
                case STATE << 0: // A-Za-z.
                    arr[i].name[j] = buffer[i][j];
                    ascii++; // next symbol.
                    break;
                case STATE << 1: // 0-9.
                    arr[i].name[j] = buffer[i][j];
                    ascii++;
                    break;
                default:
                    panic('f'); // undefined symbol
            }
        }
        arr[i].name[ascii] = '\0'; // string terminator
    }
    return arr;
}