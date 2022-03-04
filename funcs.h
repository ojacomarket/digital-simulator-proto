#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LINES 100 // Maximum length of each line in a file is 100 symbols.
#define MAX_INPUT 3 // Only 3 input wires are allowed for given logic gate.
#define STATE 0b00000001 // Binary representation of FLAG, where we use bit shifting to alter program states.

/**
 * Enum that holds possible logic gates for this program.
 */
enum LOGIC_GATES_ENUM {
    not = 0, and, or, xor, nand, nor, gen
};

/**
 * Enum that holds possible states of parsing process (FILE SHOULD HAVE DEFINITE STRUCTURE).
 */
enum PROGRAM_STATES_ENUM {
    begin = 0, next, name, gate, time, values, endline
};

/**
 * Template for storing parsed data, any other format is prohibited.
 */
struct gate {
    int value; // Current value of a logic gate output.
    unsigned char name[10]; // Logic gate unique name.
    int time; // Timestamp, that will indicate the moment of changing a signal value (value of logic gate output).
    enum LOGIC_GATES_ENUM logic_gate; // Type of logic gate.
    int *inputs[MAX_INPUT]; // Logic gate dependencies, we restrict it to have MAX 3 input wires for given logic gate.
};

/**
 * Read file, parse into struct.
 * @param [ uint8_t ]: variable, that will store how many lines were red from a file.
 * @param [ struct gate*** ]: custom data type, that will store parsed data.
 * @param [ char** ]: terminal arguments (file name).
 */
extern void part1(uint8_t *, struct gate ***, char **);

// If you find "#define AUTHORIZED" in some file's head, then know, that it can "see" following contents.
#ifdef AUTHORIZED_1

/**
 * Lookup table has 256 numbers in it, where we match ASCII symbol to some number:
 * a) A-Za-z: 1
 * b) 0-9: 2
 * c) '\n': 16
 * d) ' ' (Space): 255
 * e) Other symbols: 0 (in our program any other than a) - d) symbols are PROHIBITED and will force program to stop.
 */
unsigned char LUT[] = {
        0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 16,
        0, 0, 16, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 255, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
};

/**
 * All possible logic gates we can use in our program (only used to COMPARE contents from parsed file).
 */
const char *LOGIC_GATES[] = {
        "not",
        "and",
        "or",
        "xor",
        "nand",
        "nor",
        "gen"
};

/**
 * Error indicator.
 * @param [ uint8_t ]: file line.
 * @param [ uint8_t ]: file column.
 * @param [ char ]: what type of problem 'r' = reading file, 'f' = parsing a file.
 */
extern void panic(uint8_t, uint8_t, char );

/**
 * Refresh array.
 * @param [ unsigned char* ]: array to flush.
 * @param [ int ]: how many symbols we wish to flush.
 */
extern void flush(unsigned char *, int);

#endif

#ifdef AUTHORIZED_2 // New content for different authorized files.

/**
 * Read a file.
 * @param [ char** ]: buffer with raw data.
 * @param [ char** ]: arguments from command line.
 * @return [ uint8_t ]: How many lines of file were actually red.
 */
extern uint8_t read(char **, char **);

/**
 * Read logic gate names from buffer.
 * @param [ struct gate* ]: struct that will be fill particularly.
 * @param [ char** ]: buffer with raw data.
 * @param [ uint8_t ]: size of buffer's line length.
 * @return [ int ]: 0 if good, any other number = error.
 */
extern int read_logic_gate_names(struct gate **, char **, uint8_t);

/**
 * Fill data from a file into array of struct.
 * @param [ struct gate* ]: array of struct.
 * @param [ char*[] ]: buffer with raw data.
 * @param [ uint8_t ]: how many lines were red from a file.
 * @return [ _Bool ]: 0 if everything went good, 1 if error.
 */
extern _Bool fill(struct gate **, char *[MAX_FILE_LINES], uint8_t);

#endif