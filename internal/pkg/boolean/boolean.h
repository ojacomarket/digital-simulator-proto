// Allows you to safely implement Boolean algebra for well-known gates.
#ifdef BOOLEAN

#include <stdint.h>
#include <stdlib.h>

typedef enum {
    not = 0, and, or, xor, nand, nor, gen
} LogicType;

#pragma push(1)
typedef struct {
    uint8_t value: 1;
} Boolean;
#pragma pop(0)

/**
 * Generate logic gate output.
 * @param in array of input pins values
 * @param out output of a logic gate
 * @param s amount of input pins into gate
 * @param type logic gate type
 */
extern void run(Boolean *in, Boolean *out, size_t s, LogicType type);

#endif
