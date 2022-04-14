#define FILL
#include "../../funcs.h"

LogicGate *lparse(unsigned char **buffer, uint64_t lines) {

    // 1. First parse struct with logic gate names, it will help to parse in the future.
    LogicGate *logicGatesArray = lcreate(buffer, lines, LUT);
    // 1. Here we declare a variables, that will help us to perform control over raw data.
    unsigned char reading; // Get ASCII symbol from buffer.
    uint8_t current = 1; // Variable to control current portion of data we are parsing.
    enum ParserState state = 0; // State is used to tell program, which datatype we are parsing.
    LogicType gates[] = {not, and, or, xor, nand, nor, gen}; // Type of logic gates.
    int sym = 0; // Tracker of symbol inside a buffer.
    unsigned char temp[20]; // Temporary buffer, to store data, that might be longer than one symbol.
    uint8_t counter = 0; // Counter of symbols in temporary "temp" array.


    // 2. Loop all lines of file.
    for (int value = 0, line = 0; line < lines; line++, sym = 0, current = 1, state = begin, value = 0) {

        logicGatesArray[line].in = (Boolean **) malloc(sizeof(Boolean *) * MODERN_PC_64BIT);
        // 3. Loop each file line, until state is not defined as end of file line (ASCII: 10 or 13)
        while (state != endline) {

            // 4. Read symbol from buffer.
            reading = LUT[buffer[line][sym]];

            // 5. Check which portion of data we are parsing currently (name/logic gate/changesAt/values).
            switch (current) {

                case STATE << 0: // Logic gate name.
                state = name;
                break;
                case STATE << 1: // Logic gate type.
                state = gate;
                break;
                case STATE << 2: // Time reference of logic gate (when it should change its value).
                state = delays;
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
                            uint64_t indexOfValidGate = lindex((size_t *) temp, (size_t *) LOGIC_GATES,
                                                               KNOWN_LOGIC_GATES);
                            if (indexOfValidGate == KNOWN_LOGIC_GATES) {
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
            else if (state == delays) {
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
            // 12. If we are parsing a logic gate in or just signal value in case of "gen" (generator).
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
                    if (logicGatesArray[line].type == gen/*gen_e*/) {
                        logicGatesArray[line].out.value = atoi((char *) temp);
                        if (logicGatesArray[line].out.value < 0 || logicGatesArray[line].out.value > 1) {
                            panic('p');
                        }
                    }
                    break;
                    case (STATE << 8) - 1: // "Space" is met.

                    temp[counter] = '\0'; // Terminate a string, that has been parsed.
                    // Check, that in are actually valid logic gate names.
                    uint64_t index = lname((size_t *) temp, logicGatesArray, lines);

                    if (index != lines) {

                        logicGatesArray[line].in[value] = &logicGatesArray[index].out;
                        /*      printf("logic name: %s\n", logicGatesArray[line].name);
                              printf("Index name: %s\n", logicGatesArray[index].name);
                              printf("Index addr %p\n",&logicGatesArray[index].out);
                              printf("logic addr %p\n",logicGatesArray[line].in[value]);
  */
                        logicGatesArray[line].inPins = value + 1;
                        value++; // Get ready for next logic gate to input.
                    }


                    counter = 0; // Refresh "temp"'s buffer counter.
                    memset(temp, 0, 20);
                    break;
                    case STATE << 4: // If enter is met or "carriage return", ASCII: 10 and 13.
                    temp[counter] = '\0'; // If we are here, this means, that no further string will grow that's why we terminate it.

                    uint64_t index2 = lname((size_t *) temp, logicGatesArray, lines);

                    if (index2 != lines) {

                        logicGatesArray[line].in[value] = malloc(sizeof(Boolean));

                        logicGatesArray[line].in[value] = &logicGatesArray[index2].out;
                        logicGatesArray[line].inPins = value + 1;
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