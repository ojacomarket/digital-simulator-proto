#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    not = 0, and, or, xor, nand, nor, gen
} LogicGate;

typedef struct {
    uint8_t value:1;
} Boolean;

void logicgate(const Boolean *input, Boolean *output, size_t pins, LogicGate type);

