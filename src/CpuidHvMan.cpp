#include "RedPill.h"
#include "CpuidHvMan.h"
#include "Constants.h"

#include <cstring>
#include <cpuid.h>

CpuidHvMan::CpuidHvMan(int argc, const char ** argv) : RedPill(argc, argv) {
}

CpuidHvMan::CpuidHvMan() : RedPill() {
}

CpuidHvMan::~CpuidHvMan() {
}

RedPill::StatusForRun 
CpuidHvMan::args_checker() const {
    if (argc_ == 1) {
        return RedPill::StatusForRun::kCould;
    }
    if (check_args_have_flag(kCpuidHvMan)) {
        return RedPill::StatusForRun::kNeed;
    }
    return RedPill::StatusForRun::kCannot;
}

std::string 
CpuidHvMan::red_pill_caller() const {
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