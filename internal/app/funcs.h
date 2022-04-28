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
    unsigned char name[GATE_NAME_MAXLEN]; // logic gate unique name
    LogicType type; // type of logic gate
} LogicGate;
#pragma pop(0)

#ifdef DIGISIM
/**
 * Run digital simulator from an input file, write wave results to a file.
 * @param i input file rows
 * @param f input file name
 * @param t duration of simulation
 * @return 0 of simulation went ok, 1 if not
 */
extern _Bool digisim(uint64_t *i, char *f, char *t);
#endif
#ifdef PARSER
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
const char *BUILTIN[] = {
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
 * Parse data from a buffer.
 * @param buffer raw data
 * @param lines file rows
 * @return complete logic gates in a form of C struct array
 */
extern LogicGate *lparse(unsigned char **buffer, uint64_t lines);

/**
 * Initialize logic gates as a C struct array (fill logic gate names).
 * @param buffer raw data
 * @param lines  file rows
 * @param LUT  lookup table for ascii symbols
 * @return logic gates in a form of C struct array with only names filled
 */
extern LogicGate *lcreate(unsigned char **buffer, uint64_t lines,
                   const unsigned char LUT[]);

/**
 * Get index of pattern "p" from a source "s".
 * @param p pattern (size < unsigned long)
 * @param s source (size < unsigned long)
 * @param size size of source
 * @return index
 */
extern uint64_t lindex(size_t *p, size_t *s, uint64_t size);

/**
 * Get index of pattern "p" from a logic gates "g".
 * @param p pattern (size < unsigned long)
 * @param g logic gates
 * @param size size of gate
 * @return index
 */
uint64_t lname(size_t *p, LogicGate *g, uint64_t size);

/**
 * Run simulator.
 * @param g logic gates array
 * @param r file rows
 * @param t current timer value
 */
extern void simulate(LogicGate *g, uint64_t r, const uint64_t * t);

/**
 *
 * @param g logic gates array
 * @param r file rows
 * @param t current timer value
 * @param f pointer to the file we write output into
 */
extern void lupdate(LogicGate *g, uint64_t r, uint64_t t, FILE *f);

//extern void lchange(LogicGate *g, uint64_t s, uint64_t timer, FILE *f, uint8_t *fire);
extern void lchange(LogicGate *g, uint64_t s, uint64_t timer, FILE *f);
extern void lrun(LogicGate *g, uint64_t s);
/**
 * Write to file.
 * @param g logic gate array
 * @param r file rows
 * @return pointer to the file we write output into
 */
extern FILE *output(LogicGate *g, uint64_t r);
