#define AUTHORIZED_2

#include "funcs.h"

void part1(uint8_t *buffer_content, struct gate ***ptr, char **argv) {

    char *buffer[MAX_FILE_LINES];
    *buffer_content = read(buffer, argv);

    /** Debugger: Uncomment to see what is actually been red from a file. **/

    for (int i = 0; i < *buffer_content; ++i) {
        printf("%s\n", buffer[i]);
    }

    // Allocate memory for struct array.
    struct gate **logic_schema = malloc(sizeof(struct gate *) * (*buffer_content));
    *ptr = logic_schema;
    for (int i = 0; i < *buffer_content; ++i) {
        logic_schema[i] = malloc(sizeof(struct gate));
    }

    // Init all structs inside array.
    for (int i = 0; i < *buffer_content; ++i) {
        logic_schema[i]->value = 0;
        logic_schema[i]->time = 0;
        for (int j = 0; j < 3; ++j) {
            logic_schema[i]->inputs[j] = NULL;
        }
    }

    read_logic_gate_names(logic_schema, buffer, *buffer_content);

    /** Debugger: Uncomment to see parsed logic gate names into struct. **/
/*
    for (int i = 0; i < *buffer_content; ++i) {
        printf("%s\n", logic_schema[i]->name);
    }
*/

    fill(logic_schema, buffer, *buffer_content);

    /** Debugger: Uncomment to see parsed struct. **/

/*
     for (int i = 0; i < *buffer_content; ++i) {
         printf("First element is:\n");
         printf("Time is %d\n", logic_schema[i]->time);
         printf("Value is %d\n", logic_schema[i]->value);
         printf("Value addr is %p\n", &logic_schema[i]->value);
         printf("Logic gate is %d\n", logic_schema[i]->logic_gate);
         if (i < *buffer_content - 2) {
             printf("Pointer to %p.....%p\n", logic_schema[i]->inputs[0], logic_schema[i]->inputs[1]);
         }
     }*/
}