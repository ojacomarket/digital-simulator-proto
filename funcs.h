#define CUTILS

#include "cutils.h"
#include "boolean/boolean.h"

#define MAX_FILE_LINES 100 // Maximum length of each line in a file is 100 symbols.
#define MAX_INPUT 3 // Only 3 input wires are allowed for given logic gate.
#define STATE 0b00000001 // Binary representation of FLAG, where we use bit shifting to alter program states.
#define LOGIC_GATES_IN_USE 7
#define MODERN_PC 64
#define GATE_NAME 10

/**
 * Enum that holds possible logic gates for this program.
 */
enum LOGIC_GATES_ENUM {
    not_e = 0, and_e, or_e, xor_e, nand_e, nor_e, gen_e
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
#pragma push(1)
typedef struct {
    Boolean output;
    _Bool valuesHasBeenChanged;
    Boolean **inputValues;
    Boolean buffer;
    uint8_t inputAmount;
    uint16_t delay; // Timestamp, that will indicate the moment of changing a signal value (value of logic gate output).
    uint64_t timing;
    unsigned char name[GATE_NAME]; // Logic gate unique name.
    LogicGate type; // Type of logic gate.
} Gate;
#pragma pop(0)

/**
 * Read file, parse into struct.
 * @param [ uint64_t ]: variable, that will store how many lines were red from a file.
 * @param [ struct gate*** ]: custom data type, that will store parsed data.
 * @param [ char** ]: terminal arguments (file name).
 */
extern Gate *digitalSimulator(uint64_t *bufferLines, char **argv);

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
 * Refresh array.
 * @param [ unsigned char* ]: array to flush.
 * @param [ int ]: how many symbols we wish to flush.
 */
extern void flush(unsigned char *, int);

#endif

#ifdef AUTHORIZED_2 // New content for different authorized files.

/**
 * Read logic gate names from buffer.
 * @param [ struct gate* ]: struct that will be fill particularly.
 * @param [ char** ]: buffer with raw data.
 * @param [ uint8_t ]: size of buffer's line length.
 * @return [ int ]: 0 if good, any other number = error.
 */
extern Gate *createLogicGates(unsigned char **, uint64_t);

/**
 * Fill data from a file into array of struct.
 * @param [ struct gate* ]: array of struct.
 * @param [ char*[] ]: buffer with raw data.
 * @param [ uint8_t ]: how many lines were red from a file.
 * @return [ _Bool ]: 0 if everything went good, 1 if error.
 */
extern Gate *fillLogicGates(unsigned char **, uint64_t);

uint64_t isFound(size_t *, size_t *, uint64_t);

uint64_t isFoundLogicGate(size_t *pattern, Gate *source, uint64_t size);

#endif

void runSimulator(Gate *system, uint64_t systemElements);

void updateGates(Gate *system, uint64_t systemElements, uint64_t timer);

void fancyOutput(Gate *system, uint64_t systemElements);

void calculateGates(Gate *system, uint64_t systemElements, uint64_t timer);