#include "funcs.h"


int main(int argc, char **argv) {

    uint64_t fileLines = 0;

    part1(&fileLines, argv);

    /** Debugger: Uncomment to see what is actually been parsed from a file. **/
    /*
    for (int i = 0; i < file_lines; ++i) {
        printf("First element is:\n");
        printf("Time is %d\n", logic_schema[i]->delay);
        printf("Value is %d\n", logic_schema[i]->value);
        printf("Value addr is %p\n", &logic_schema[i]->value);
        printf("Logic gate is %d\n", logic_schema[i]->type);
        printf("Pointer to %p.....%p\n", logic_schema[i]->inputValues[0], logic_schema[i]->inputValues[1]);
    }
    */
    return 0;
}

