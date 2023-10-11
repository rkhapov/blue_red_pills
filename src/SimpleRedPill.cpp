#include "RedPill.h"
#include "SimpleRedPill.h"
#include "Constants.h"

#include <cstring>
#include <string>
#include <cpuid.h>


SimpleRedPill::SimpleRedPill(int argc, const char **argv) : argc_(argc), argv_(argv) {
}

SimpleRedPill::SimpleRedPill() : SimpleRedPill(0, 0) {
}

bool
SimpleRedPill::args_checker() {
    if (argc_ == 2 && strcmp(argv_[1], kSimple.c_str()) == 0) {
        return 1;
    } else {
        return 0;
    }
}

std::string
SimpleRedPill::red_pill_caller() {
    unsigned int regs1[12];
    unsigned int regs2[3];
    char str[sizeof(regs1) + 1 + sizeof(regs2) + 1];

    __cpuid(0x80000000, regs1[0], regs1[1], regs1[2], regs1[3]);

    if (regs1[0] < 0x80000004)
        exit(-1);

    __cpuid(0x80000002, regs1[0], regs1[1], regs1[2], regs1[3]);
    __cpuid(0x80000003, regs1[4], regs1[5], regs1[6], regs1[7]);
    __cpuid(0x80000004, regs1[8], regs1[9], regs1[10], regs1[11]);

    memcpy(str, regs1, sizeof(regs1));
    str[sizeof(regs1)] = '\n';

    __cpuid(0x00000000, regs1[0], regs2[0], regs2[2], regs2[1]);

    memcpy(str + sizeof(regs1) + 1, regs2, sizeof(regs2));
    for(size_t i = 0; i < sizeof(str); i++) {
        if(str[i] == 0) {
            str[i] = 1;
        }
    }
    str[sizeof(regs1) + 1 + sizeof(regs2)] = '\0';

    return std::string(str);

    return 0;
}