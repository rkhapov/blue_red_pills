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
    return red_pill_1() + "\n" + red_pill_2() + "\n" + red_pill_3() + "\n";
}

std::string
SimpleRedPill::red_pill_1() {
    unsigned int regs[12];
    char str[sizeof(regs) + 1];

    __cpuid(0x80000000, regs[0], regs[1], regs[2], regs[3]);

    if (regs[0] < 0x80000004)
        exit(-1);

    __cpuid(0x80000002, regs[0], regs[1], regs[2], regs[3]);
    __cpuid(0x80000003, regs[4], regs[5], regs[6], regs[7]);
    __cpuid(0x80000004, regs[8], regs[9], regs[10], regs[11]);

    memcpy(str, regs, sizeof(regs));

    for(size_t i = 0; i < sizeof(str); i++) {
        if(str[i] == 0) {
            str[i] = 1;
        }
    }
    str[sizeof(regs)] = '\0';

    return std::string(str);
}


std::string
SimpleRedPill::red_pill_2() {
    unsigned int regs[4];
    char str[sizeof(regs) + 1];

    __cpuid(0x00000000, regs[3], regs[0], regs[2], regs[1]);

    memcpy(str, regs, sizeof(regs));

    for(size_t i = 0; i < sizeof(str); i++) {
        if(str[i] == 0) {
            str[i] = 1;
        }
    }
    str[sizeof(regs)] = '\0';

    return std::string(str);
}


std::string
SimpleRedPill::red_pill_3() {
    unsigned int empty[0];
    unsigned int regs[3];
    char str[sizeof(regs) + 1];

    __cpuid(0x40000000, empty[0], regs[0], regs[1], regs[2]);

    memcpy(str, regs, sizeof(regs));

    for(size_t i = 0; i < sizeof(str); i++) {
        if(str[i] == 0) {
            str[i] = 1;
        }
    }
    str[sizeof(regs)] = '\0';

    return std::string(str);
}

