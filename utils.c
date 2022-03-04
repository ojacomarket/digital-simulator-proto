#define AUTHORIZED_1
#define AUTHORIZED_2

#include "funcs.h"

_Bool fill(struct gate **logic_schema, char *buffer[MAX_FILE_LINES], uint8_t lines) {

    // 1. Here we declare a variables, that will help us to perform control over raw data.
    unsigned char reading; // Get ASCII symbol from buffer.
    uint8_t current = 1; // Variable to control current portion of data we are parsing.
    enum PROGRAM_STATES_ENUM state = 0; // State is used to tell program, which datatype we are parsing.
    enum LOGIC_GATES_ENUM gates[] = {not, and, or, xor, nand, nor, gen}; // Type of logic gates.
    int sym = 0; // Tracker of symbol inside a buffer.
    unsigned char temp[20]; // Temporary buffer, to store data, that might be longer than one symbol.
    uint8_t counter = 0; // Counter of symbols in temporary "temp" array.


    // 2. Loop all lines of file.
    for (int value = 0, line = 0; line < lines; line++, sym = 0, current = 1, state = begin, value = 0) {

        // 3. Loop each file line, until state is not defined as end of file line (ASCII: 10 or 13)
        while (state != endline) {

            // 4. Read symbol from buffer.
            reading = LUT[buffer[line][sym]];

            // 5. Check which portion of data we are parsing currently (name/logic gate/timing/values).
            switch (current) {

                case STATE << 0: // Logic gate name.
                    state = name;
                    break;
                case STATE << 1: // Logic gate type.
                    state = gate;
                    break;
                case STATE << 2: // Time reference of logic gate (when it should change its value).
                    state = time;
                    break;
                case STATE << 3: // Inputs of logic gates or just signal value in case of generator.
                    state = values;
                    break;
                default: // Error if anything else but above-mentioned.
                    panic(line, sym, 'f');
            }

            // 6. If we are parsing a logic gate name.
            if (state == name) {

                // 7. Which symbol was red from a buffer (for name, we don't control validity, since it has been already done).
                switch (reading) {

                    // When our name reaches a delimiter (Space).
                    case (STATE << 8) - 1:

                        // We shift current value into another state (i.e we tell program, that next data chunk is coming).
                        current = current << 1; // At start current = 00000001, now is 00000010 (left shift).
                        state = next; // Change a state to next (We wait for new data chunk).
                        break;
                    default: // Syntactically, have to be here, but practically useless statement.
                        break;
                }
            }
                // 8. If we are parsing a logic gate type.
            else if (state == gate) {
                // 9. Which symbol was red from a buffer (for name, we don't control validity, since it has been already done).
                switch (reading) {
                    // If symbol from buffer is type of A-Za-z.
                    case STATE << 0:
                        temp[counter] = buffer[line][sym]; // Add to temp buffer this symbol.
                        counter++;
                        break;
                        // If symbol from buffer is "Space" symbol.
                    case (STATE << 8) - 1:
                        temp[counter] = '\0'; // Add string terminator.
                        // Check that logic gate type is valid.
                        for (int coincidence, i = 0; i < 7; ++i) {
                            // We check logic gate type from pre-defined list of logic gates.
                            coincidence = strcmp((char *) temp, LOGIC_GATES[i]);
                            // If logic gate type is valid.
                            if (!coincidence) {
                                logic_schema[line]->logic_gate = gates[i]; // Add logic gate type to struct.
                                break;
                            }
                                // If we reach this point, it means, that logic gate type is invalid and we throw error.
                            else if (i == 6) {
                                panic(line, sym, 'f');
                            }
                        }
                        current = current << 1; // Shift "current" to indicate new chunk of data to be parsed.
                        counter = 0; // Refresh counter of temp array.
                        flush(temp, 20); // Clear data of temp array for future usage.
                        state = next; // Set state to next.
                        break;
                    default: // If we reach this point, this means, that we have erroneous data.
                        panic(line, sym, 'f');
                }
            }
                // 10. If we are parsing a logic gate "turn on" time.
            else if (state == time) {
                // 11. Which symbol was red from a buffer (for name, we don't control validity, since it has been already done).
                switch (reading) {
                    case STATE << 1: // If symbol is a type of 0-9.
                        temp[counter] = buffer[line][sym]; // Add symbol to temp array.
                        counter++;
                        break;
                    case (STATE << 8) - 1: // "Space" symbol is red.

                        temp[counter] = '\0'; // Add null terminator to the end of the parsed string.
                        logic_schema[line]->time = atoi((char *) temp); // Try to change string of time into number.
                        current = current << 1; // Shift current variable to give a signal of new chunk of data,
                        state = next; // Change state.
                        counter = 0; // Refresh counter and temp array.
                        flush(temp, 20);
                        break;
                    default: // Error in parsing, if reached here.
                        panic(line, sym, 'f');
                }
            }
                // 12. If we are parsing a logic gate inputs or just signal value in case of "gen" (generator).
            else if (state == values) {
                // 13. Which symbol was red from a buffer (for name, we don't control validity, since it has been already done).
                switch (reading) {
                    case STATE << 0: // Symbol "reading" is A-Za-z.
                        temp[counter] = buffer[line][sym]; // Add to temp array.
                        counter++;
                        break;
                    case STATE << 1: // Symbol is 0-9.
                        temp[counter] = buffer[line][sym]; // This characters are also allowed to be in logic gate name.
                        counter++;
                        // 14. If current logic gate type is generator.
                        if (logic_schema[line]->logic_gate == gen) {
                            logic_schema[line]->value = atoi((char *) temp); // Assign signal value to this generator.
                        }
                        break;
                    case (STATE << 8) - 1: // "Space" is met.
                        temp[counter] = '\0'; // Terminate a string, that has been parsed.
                        // Check, that inputs are actually valid logic gate names.
                        for (int coincidence, i = 0; i < lines; ++i) {
                            coincidence = strcmp((char *) temp, (char *) logic_schema[i]->name);
                            // If valid.
                            if (!coincidence) {
                                logic_schema[line]->inputs[value] = &logic_schema[i]->value;
                                break;
                            }
                                // If not valid.
                            else if (i == lines - 1) {
                                panic(line, sym, 'f');
                            }
                        }

                        value++; // Get ready for next logic gate to input.
                        counter = 0; // Refresh "temp"'s buffer counter.
                        flush(temp, 20); // Refresh array itself.
                        break;
                    case STATE << 4: // If enter is met or "carriage return", ASCII: 10 and 13.
                        temp[counter] = '\0'; // If we are here, this means, that no further string will grow that's why we terminate it.
                        for (int coincidence, i = 0; i < lines; ++i) {
                            // Look up for valid logic gate name.
                            coincidence = strcmp((char *) temp, (char *) logic_schema[i]->name);

                            // If logic gate name is, indeed, valid.
                            if (!coincidence) {
                                logic_schema[line]->inputs[value] = &logic_schema[i]->value;
                                break;
                            }
                                // Unfortunately, not correct data.

                            else if (i == lines) {
                                panic(line, sym, 'f');
                            }
                        }
                        // Reset all variables.
                        value = 0;
                        counter = 0;
                        flush(temp, 20);
                        state = endline; // Change state, that will be used to exit "while" loop.
                        break;
                    default: // Throw error if any other trash has happened.
                        panic(line, sym, 'f');
                }
            }

            sym++; // Increment counter for buffer symbols.
        }
    }
    return 0;
}

uint8_t read(char **buffer, char **argv) {

    // 1. Open a file, if fails abort program execution.
    FILE *file = fopen(argv[2], "r");
    if (file == NULL)
        panic(0, 0, 'r');

    // 2. Declare a variable, that will store amount of line we read from a file.
    uint8_t line = 0;

    // 3. Points to the array, that we will create dynamically.
    char *ptr = NULL;

    // 4. Dynamically created array and assigned to a pointer.
    ptr = malloc(sizeof(char) * MAX_FILE_LINES);

    // 5. Read a file line by line and store into buffer only pointers to the red content.
    while (fgets(ptr, MAX_FILE_LINES - 1, file)) {
        buffer[line] = ptr;
        ++line;
        // 6. Same pointer is being re-initialized and flushed with completely new memory.
        ptr = malloc(sizeof(char) * MAX_FILE_LINES);
    }

    // 7. Free assigned memory and return how many line of a file were red.
    free(ptr);
    return line;
}


void panic(uint8_t line, uint8_t sym, char problem) {
    switch (problem) {
        case 'r':
            printf("\ncannot read a file.\n");
            exit(1);
        case 'f':
            printf("\nerror at line [%d] at symbol location [%d]\n", line, sym);
            exit(1);
        default:
            exit(1);
    }
}

void flush(unsigned char *array, int flush_size) {
    for (int i = 0; i < flush_size; ++i) {
        array[i] = 0;
    }
}

int read_logic_gate_names(struct gate **array, char **buffer, uint8_t lines) {

    char *ptr = NULL; // Will be pointing to the buffer's file line as whole.
    uint8_t name_len = 0; // Variable to track logic gate's name.

    // Loop until all line files are investigated.
    for (int i = 0; i < lines; ++i, name_len = 0) {
        // Pointer to the buffer file line is going to the next line.
        ptr = *(buffer + i);

        // Loop until "Space" character is met.
        for (int j = 0; *ptr != 32; ++j, ptr++) {
            // Check what symbol is currently is.
            switch (LUT[*ptr]) {
                case STATE << 0: // A-Za-z.
                    array[i]->name[j] = buffer[i][j]; // Write name into logic_schema array.
                    name_len++; // Go to next symbol.
                    break;
                case STATE << 1: // 0-9.
                    array[i]->name[j] = buffer[i][j]; // Write name into logic_schema array.
                    name_len++;
                    break;
                default: // If wrong symbols are met (prohibited).
                    panic(i, j, 'f');
            }
        }
        array[i]->name[name_len] = '\0'; // Add line terminator to logic gate type's name.
    }
    return 0;
}