#define CUTILS
#define BOOLEAN

#include "../pkg/cutils/cutils.h"
#include "../pkg/boolean/boolean.h"
#include <time.h>

#define STATE 0b00000001 // Binary representation of FLAG, where we use bit shifting to alter program states.
#define KNOWN_LOGIC_GATES 7
#define MODERN_PC_64BIT 64
#define GATE_NAME_MAXLEN 10

/**
 * Enum that holds possible states of parsing process (FILE SHOULD HAVE DEFINITE STRUCTURE).
 */
enum ParserState {
    begin = 0, next, name, gate, delays, values, endline
};

/**
 * Logic gate format.
 */
#pragma push(1)
typedef struct {
    Boolean out; // pin out
    _Bool isBufferChanged; // tracks state of input pin's abs value
    Boolean **in; // pin in
    Boolean buffer; // abs value of input pins
    uint8_t inPins; // amount of input pins
    uint16_t delay; // reaction time of a logic gate
    uint64_t changesAt; // time, when logic gate changes its value
    unsigned char name[GATE_NAME_MAXLEN]; // logic gate unique name.
    LogicType type; // type of logic gate.
} LogicGate;
#pragma pop(0)

#ifdef DIGISIM
/**
 * Run digital simulator from an input file, write wave results to a file.
 * @param fileRows input file rows
 * @param filename input file name
 * @param duration duration of simulation
 * @return 0 of simulation went ok, 1 if not
 */
extern _Bool digisim(uint64_t *, char *, char *);
#endif
#ifdef FILL
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
#endif

/**
 * Refresh array.
 * @param [ unsigned char* ]: array to flush.
 * @param [ int ]: how many symbols we wish to flush.
 */
extern void flush(unsigned char *, int);

#include <stdlib.h>

/**
 * Fill data from a file into array of struct.
 * @param [ struct gate* ]: array of struct.
 * @param [ char*[] ]: buffer with raw data.
 * @param [ uint8_t ]: how many lines were red from a file.
 * @return [ _Bool ]: 0 if everything went good, 1 if error.
 */
extern LogicGate *lparse(unsigned char **buffer, uint64_t lines);


/**
 * Read logic gate names from buffer.
 * @param [ struct gate* ]: struct that will be parse particularly.
 * @param [ char** ]: buffer with raw data.
 * @param [ uint8_t ]: size of buffer's line length.
 * @return [ int ]: 0 if good, any other number = error.
 */
LogicGate *lcreate(unsigned char **buffer, uint64_t lines,
                   const unsigned char LUT[]);

uint64_t lindex(size_t *pattern, size_t *source, uint64_t size);

uint64_t lname(size_t *pattern, LogicGate *source, uint64_t size);


void simulate(LogicGate *, uint64_t, const uint64_t *);

void lupdate(LogicGate *system, uint64_t systemElements, uint64_t timer, FILE *);

/**
 * Write to file.
 * @param Logic gate array
 * @param Gates amount
 * @return Pointer to the opened file (use it in simulate.c to parse in values)
 */
FILE *output(LogicGate *, uint64_t);
