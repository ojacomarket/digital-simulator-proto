#include "funcs.h"

int main(int argc, char **argv) {

    uint8_t file_lines = 0;
    struct gate **logic_schema = NULL;

    part1(&file_lines, &logic_schema, argv);

    /** Debugger: Uncomment to see what is actually been parsed from a file. **/
    /*
    for (int i = 0; i < file_lines; ++i) {
        printf("First element is:\n");
        printf("Time is %d\n", logic_schema[i]->time);
        printf("Value is %d\n", logic_schema[i]->value);
        printf("Value addr is %p\n", &logic_schema[i]->value);
        printf("Logic gate is %d\n", logic_schema[i]->logic_gate);
        printf("Pointer to %p.....%p\n", logic_schema[i]->inputs[0], logic_schema[i]->inputs[1]);
    }
    */
    return 0;
}
