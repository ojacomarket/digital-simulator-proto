#define BOOLEAN
#include "boolean.h"

void run(Boolean **in, Boolean *out, uint8_t pins, LogicType gate) {
    Boolean *buf = malloc(sizeof(Boolean));
    switch (gate) {
        case not:
            out->value = in[0]->value + 1;
            break;
        case and:
            buf->value = in[0]->value;
            for (int i = 1; i < pins; ++i) {
                buf->value &= in[i]->value;
            }
            out->value = buf->value;
            break;
        case or:
            buf->value = in[0]->value;
            for (int i = 1; i < pins; ++i) {
                buf->value |= in[i]->value;
            }
            out->value = buf->value;
            break;
        case xor:
            buf->value = in[0]->value;
            for (int i = 1; i < pins; ++i) {
                buf->value ^= in[i]->value;
            }
            out->value = buf->value;
            break;
        case nand:
            buf->value = in[0]->value;
            for (int i = 1; i < pins; ++i) {
                buf->value &= in[i]->value;
            }
            out->value = buf->value + 1;
            break;
        case nor:
            buf->value = in[0]->value;
            for (int i = 1; i < pins; ++i) {
                buf->value |= in[i]->value;
            }
            out->value = !buf->value;
            break;
        default:
            break;
    }
}