#ifdef BOOLEAN
#include <stdint.h>
#include <stdlib.h>

typedef enum {
    not = 0, and, or, xor, nand, nor, gen
} LogicType;

#pragma push(1)
typedef struct {
    uint8_t value:1;
} Boolean;
#pragma pop(0)

/**
 * Generate logic gate output.
 * @param input array of input pins values
 * @param output value of logic gate
 * @param pins amount of inputs into gate
 * @param type gate type
 */
void run(Boolean *input, Boolean *output, size_t pins, LogicType type);
#endif
