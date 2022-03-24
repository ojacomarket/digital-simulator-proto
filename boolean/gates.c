#include "boolean.h"

void logicgate(const Boolean *input, Boolean *output, size_t pins, LogicGate type) {

    Boolean *temp = malloc(sizeof(Boolean));

    switch (type) {
        case not:
            output->value = !input->value;
            break;
        case and:
            temp->value = input[0].value;
            for (int i = 1; i < pins; ++i) {
                temp->value &= input[i].value;
            }
            output->value = temp->value;
            break;
        case or:
            temp->value = input[0].value;
            for (int i = 1; i < pins; ++i) {
                temp->value |= input[i].value;
            }
            output->value = temp->value;
            break;
        case xor:
            temp->value = input[0].value;
            for (int i = 1; i < pins; ++i) {
                temp->value ^= input[i].value;
            }
            output->value = temp->value;
            break;
        case nand:
            temp->value = input[0].value;
            for (int i = 1; i < pins; ++i) {
                temp->value &= input[i].value;
            }
            output->value = !temp->value;
            break;
        case nor:
            temp->value = input[0].value;
            for (int i = 1; i < pins; ++i) {
                temp->value |= input[i].value;
            }
            output->value = !temp->value;
            break;
        case gen:
         //   output->value = input->value;
            break;
        default:
            //error handler
            break;
    }
}