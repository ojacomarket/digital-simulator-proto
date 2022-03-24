#define AUTHORIZED_1
#define AUTHORIZED_2

#include "funcs.h"

Gate *fillLogicGates(unsigned char **buffer, uint64_t lines) {

    // 1. First fill struct with logic gate names, it will help to parse in the future.
    Gate *logicGatesArray = createLogicGates(buffer, lines);


    // 1. Here we declare a variables, that will help us to perform control over raw data.
    unsigned char reading; // Get ASCII symbol from buffer.
    uint8_t current = 1; // Variable to control current portion of data we are parsing.
    enum PROGRAM_STATES_ENUM state = 0; // State is used to tell program, which datatype we are parsing.
    LogicGate gates[] = {not, and, or, xor, nand, nor, gen}; // Type of logic gates.
    int sym = 0; // Tracker of symbol inside a buffer.
    unsigned char temp[20]; // Temporary buffer, to store data, that might be longer than one symbol.
    uint8_t counter = 0; // Counter of symbols in temporary "temp" array.


    // 2. Loop all lines of file.
    for (int value = 0, line = 0; line < lines; line++, sym = 0, current = 1, state = begin, value = 0) {

        logicGatesArray[line].inputValues = (Boolean **) malloc(sizeof(Boolean *) * MODERN_PC);
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
                    panic('f');
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

                        // We check logic gate type from pre-defined list of logic gates.
                        uint64_t indexOfValidGate = isFound((size_t *) temp, (size_t *) LOGIC_GATES,
                                                            LOGIC_GATES_IN_USE);
                        if (indexOfValidGate == LOGIC_GATES_IN_USE) {
                            panic('f');

                        } else {
                            logicGatesArray[line].type = gates[indexOfValidGate];
                        }

                        current = current << 1; // Shift "current" to indicate new chunk of data to be parsed.
                        counter = 0; // Refresh counter of temp array.
                        memset(temp, 0, 20);//flush(temp, 20); // Clear data of temp array for future usage.
                        state = next; // Set state to next.
                        break;
                    default: // If we reach this point, this means, that we have erroneous data.
                        panic('f');
                }
            }
                // 10. If we are parsing a logic gate "turn on" delay.
            else if (state == time) {
                // 11. Which symbol was red from a buffer (for name, we don't control validity, since it has been already done).
                switch (reading) {
                    case STATE << 1: // If symbol is a type of 0-9.
                        temp[counter] = buffer[line][sym]; // Add symbol to temp array.
                        counter++;
                        break;
                    case (STATE << 8) - 1: // "Space" symbol is red.

                        temp[counter] = '\0'; // Add null terminator to the end of the parsed string.
                        logicGatesArray[line].delay = atoi((char *) temp); // Try to change string of delay into number.
                        current = current << 1; // Shift current variable to give a signal of new chunk of data,
                        state = next; // Change state.
                        counter = 0; // Refresh counter and temp array.
                        memset(temp, 0, 20);
                        break;
                    default: // Error in parsing, if reached here.
                        panic('f');
                }
            }
                // 12. If we are parsing a logic gate inputValues or just signal value in case of "gen" (generator).
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
                        if (logicGatesArray[line].type == gen_e) {
                            logicGatesArray[line].output.value = atoi((char *) temp);
                            if (logicGatesArray[line].output.value < 0 || logicGatesArray[line].output.value > 1) {
                                panic('p');
                            }
                        }
                        break;
                    case (STATE << 8) - 1: // "Space" is met.

                        temp[counter] = '\0'; // Terminate a string, that has been parsed.
                        // Check, that inputValues are actually valid logic gate names.
                        uint64_t index = isFoundLogicGate((size_t *) temp, logicGatesArray, lines);

                        if (index != lines) {

                            logicGatesArray[line].inputValues[value] = &logicGatesArray[index].output;
                            logicGatesArray[line].inputAmount = value + 1;
                            value++; // Get ready for next logic gate to input.
                        }


                        counter = 0; // Refresh "temp"'s buffer counter.
                        memset(temp, 0, 20);
                        break;
                    case STATE << 4: // If enter is met or "carriage return", ASCII: 10 and 13.
                        temp[counter] = '\0'; // If we are here, this means, that no further string will grow that's why we terminate it.

                        uint64_t index2 = isFoundLogicGate((size_t *) temp, logicGatesArray, lines);

                        if (index2 != lines) {

                            logicGatesArray[line].inputValues[value] = malloc(sizeof(Boolean));

                            logicGatesArray[line].inputValues[value] = &logicGatesArray[index2].output;
                            logicGatesArray[line].inputAmount = value + 1;
                        }

                        value = 0;
                        counter = 0;
                        memset(temp, 0, 20);
                        state = endline; // Change state, that will be used to exit "while" loop.
                        break;
                    default: // Throw error if any other trash has happened.
                        panic('f');
                }
            }

            sym++; // Increment counter for buffer symbols.
        }

    }

    return logicGatesArray;
}

Gate *createLogicGates(unsigned char **buffer, uint64_t lines) {

    // 1. Allocate and initialize memory for a dynamic struct array.
    Gate *logicGatesArray = calloc(lines, sizeof(Gate));

    // 2. Create a variable, that will track ASCII symbols in a logic gate name.
    uint8_t name_len = 0;

    // 3. Loop until all lines in a buffer are red.
    for (int i = 0; i < lines; ++i, name_len = 0) {

        // 3.1 Loop until "Space" character is met.
        for (int j = 0; buffer[i][j] != 32; ++j) {

            // 3.1.1 Match symbol from buffer to the Lookup table.
            switch (LUT[buffer[i][j]]) {

                case STATE << 0: // A-Za-z.
                    logicGatesArray[i].name[j] = buffer[i][j]; // Write name into struct array.
                    name_len++; // Go to next symbol.
                    break;

                case STATE << 1: // 0-9.
                    logicGatesArray[i].name[j] = buffer[i][j]; // Write name into struct array.
                    name_len++; // Go to next symbol.
                    break;

                default: // If wrong symbol is met (prohibited).
                    panic('f');
            }
        }

        // 4. Add line terminator to the end of a logic gate name.
        logicGatesArray[i].name[name_len] = '\0';
    }

    return logicGatesArray;
}

uint64_t isFound(size_t *pattern, size_t *source, uint64_t size) {

    uint8_t coincidence;
    for (int i = 0; i < size; ++i) {

        // We check logic gate type from pre-defined list of logic gates.
        coincidence = strcmp((const char *) pattern, (const char *) source[i]);

        // If logic gate type is valid.
        if (!coincidence) {
            return i;
        }
    }
    return size;
}

uint64_t isFoundLogicGate(size_t *pattern, Gate *source, uint64_t size) {

    uint8_t coincidence;
    for (int i = 0; i < size; ++i) {

        // We check logic gate type from pre-defined list of logic gates.
        coincidence = strcmp((const char *) pattern, (const char *) source[i].name);

        // If logic gate type is valid.
        if (!coincidence) {
            return i;
        }
    }
    return size;
}

void updateGates(Gate *system, uint64_t systemElements, uint64_t timer) {

    for (int i = 0; i < systemElements; ++i) {

        if (system[i].buffer.value != system[i].output.value && !system[i].valuesHasBeenChanged &&
            system[i].type != gen) {
            system[i].valuesHasBeenChanged = 1;
            system[i].timing = timer;
            system[i].timing = system[i].timing + system[i].delay;
        }

        if (system[i].type == gen) {
            if ((system[i].timing + system[i].delay) == timer) {
                system[i].output.value = system[i].output.value + 1;
                system[i].timing = timer;
            }
        }
        if (!system[i].valuesHasBeenChanged) {
            logicgate((const Boolean *) system[i].inputValues, &system[i].buffer, system[i].inputAmount,
                      system[i].type);
        }
    }
}

void calculateGates(Gate *system, uint64_t systemElements, uint64_t timer) {

    for (int i = 0; i < systemElements; ++i) {

        if (system[i].timing == timer && timer > 0 && system[i].type != gen) {
            system[i].output.value = system[i].buffer.value;
            system[i].valuesHasBeenChanged = 0;
        }
    }
}

void runSimulator(Gate *system, uint64_t systemElements) {

    for (int clock = 0; clock < 15; ++clock) {
        printf("Processor clock: ==========> %d\n", clock);
        updateGates(system, systemElements, clock);
        calculateGates(system, systemElements, clock);
        fancyOutput(system, systemElements);
        printf("\n\n");
    }
}


void fancyOutput(Gate *system, uint64_t systemElements) {

    for (int index = 0; index < systemElements; ++index) {

        printf("{Name: %3s, Type: %3d, Output: %3d, Buffer: %3d, Timing: %3lu, Delay: %d, Inputs: %3d}\n",
               system[index].name,
               system[index].type, system[index].output.value,
               system[index].buffer.value,
               system[index].timing,
               system[index].delay,
               system[index].inputAmount);
    }
}