// Finite state machine robust parser.
#define PARSER

#include "../../funcs.h"

LogicGate *lparse(unsigned char **buffer, uint64_t lines) {

    LogicGate *arr = lcreate(buffer, lines, LUT); // init logic gate array
    unsigned char ascii; // get ascii from buffer
    uint8_t x = 1; // file row paring counter
    enum ParserState state = 0; // extracting exact portion from a file row
    LogicType gates[] = {not, and, or, xor, nand, nor, gen};
    int s = 0; // track buffer symbols
    unsigned char temp[20]; // temporary buffer to store data, that is longer than 1 symbol
    uint8_t ts = 0; //  track temp symbols
    // Loop file rows. 'a' is a symbol tracker for input gate names.
    for (int a = 0, line = 0; line < lines; line++, s = 0, x = 1, state = begin, a = 0) {
        // Each gate can have up to 64 pins.
        arr[line].in = (Boolean **) malloc(sizeof(Boolean *) * MODERN_PC_64BIT);
        // Loop single file row.
        while (state != endline) {
            ascii = LUT[buffer[line][s]]; // map symbol from buffer to lookup table
            // Portion of data in a file row.
            switch (x) {
                case STATE << 0: // logic gate name
                    state = name;
                    break;
                case STATE << 1: // logic gate type
                    state = gate;
                    break;
                case STATE << 2: // logic gate delay (reaction time to input change)
                    state = delays;
                    break;
                case STATE << 3: // logic gate inputs
                    state = values;
                    break;
                default: // undefined is considered as an error
                    panic('f');
            }
            if (state == name) {
                switch (ascii) {
                    case (STATE << 8) - 1: // 'space'
                        x = x << 1; // indicate next state
                        state = next; // set next state
                        break;
                    default: // unused
                        break;
                }
            } else if (state == gate) {
                switch (ascii) {
                    case STATE << 0: // A-Za-z.
                        temp[ts] = buffer[line][s]; // collect symbols to temp buffer
                        ts++;
                        break;
                    case (STATE << 8) - 1: // 'space'
                        temp[ts] = '\0'; // add string terminator
                        // After parse we have to be sure, that gate is valid.
                        uint64_t indexOfValidGate = lindex((size_t *) temp, (size_t *) BUILTIN,
                                                           KNOWN_LOGIC_GATES);
                        if (indexOfValidGate == KNOWN_LOGIC_GATES) {
                            panic('p'); // not found
                        } else {
                            arr[line].type = gates[indexOfValidGate];
                        }
                        x = x << 1; // next portion of a data in a given row
                        ts = 0; // refresh temp
                        memset(temp, 0, 20); // refresh temp
                        state = next; // next state
                        break;
                    default: // if we reach this point, this means, that we have erroneous data
                        panic('p');
                }
            } else if (state == delays) {
                switch (ascii) {
                    case STATE << 1: // 0-9
                        temp[ts] = buffer[line][s];
                        ts++;
                        break;
                    case (STATE << 8) - 1: // 'space'
                        temp[ts] = '\0';
                        arr[line].delay = atoi((char *) temp); // parse to number
                        x = x << 1;
                        state = next;
                        ts = 0;
                        memset(temp, 0, 20);
                        break;
                    default:
                        panic('p');
                }
            } else if (state == values) {
                switch (ascii) {
                    case STATE << 0: // A-Za-z
                        temp[ts] = buffer[line][s];
                        ts++;
                        break;
                    case STATE << 1: // 0-9
                        temp[ts] = buffer[line][s];
                        ts++;
                        if (arr[line].type == gen) { // type of gate is gen
                            arr[line].out.value = atoi((char *) temp); // in case of gate we have value not in pins
                            if (arr[line].out.value < 0 || arr[line].out.value > 1) { // only binary
                                panic('p');
                            }
                        }
                        break;
                    case (STATE << 8) - 1: // 'space'
                        temp[ts] = '\0';
                        uint64_t n = lname((size_t *) temp, arr, lines); // check that gate "n" is actually exists
                        if (n != lines) {
                            arr[line].in[a] = &arr[n].out;
                            arr[line].inPins = a + 1;
                            a++;
                        }
                        ts = 0;
                        memset(temp, 0, 20);
                        break;
                    case STATE << 4: // "carriage return", ASCII: 10 and 13
                        temp[ts] = '\0';
                        uint64_t m = lname((size_t *) temp, arr, lines);
                        if (m != lines) {
                            arr[line].in[a] = malloc(sizeof(Boolean));
                            arr[line].in[a] = &arr[m].out;
                            arr[line].inPins = a + 1;
                        }
                        a = 0;
                        ts = 0;
                        memset(temp, 0, 20);
                        state = endline; // next row
                        break;
                    default: // throw error if any other trash has happened
                        panic('f');
                }
            }
            s++; // next buffer symbol
        }
    }
    return arr;
}