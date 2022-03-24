#include "funcs.h"


int main(int argc, char **argv) {

    uint64_t fileLines = 0;

    Gate *logicGateArray = digitalSimulator(&fileLines, argv);

    return 0;
}

