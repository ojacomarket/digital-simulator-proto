#include "../../funcs.h"

FILE *output(LogicGate *gates, uint64_t size) {

    FILE *p = fopen("wave.vcd", "wt");
    time_t now = time(NULL); // get current time
    struct tm *s = gmtime(&now);
    fprintf(p, "$date\n"
               "     %d %d, %d       %d:%d:%d\n"
               "$end\n"
               "\n"
               "$version\n"
               "              Self-made Digital Simulator\n"
               "$end\n"
               "\n"
               "$timescale\n"
               "     1 ns\n"
               "$end\n"
               "\n"
               "$scope module Test $end\n", s->tm_mon, s->tm_mday, s->tm_year, s->tm_hour, s->tm_min, s->tm_sec);
    for (int i = 0; i < size; ++i) {
        fprintf(p, "$var wire    %hu  %s  %s       $end\n", gates[i].delay, gates[i].name, gates[i].name);
    }
    fprintf(p, "$upscope $end\n"
               "$enddefinitions  $end\n"
               "\n"
               "$comment\n"
               "All initial values are dumped below at delays 0 sec = 0 timescale units.\n"
               "$end\n"
               "\n"
               "$dumpvars\n");
    for (int i = 0; i < size; ++i) {
        fprintf(p, "%d%s\n", gates[i].out.value, gates[i].name);
    }
    fprintf(p, "$end\n\n");
    return p;
}