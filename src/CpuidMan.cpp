#include "RedPill.h"
#include "CpuidMan.h"
#include "Constants.h"

#include <cstring>
#include <cpuid.h>

CpuidMan::CpuidMan(int argc, const char ** argv) : RedPill(argc, argv) {
}

CpuidMan::~CpuidMan() {
}

CpuidMan::CpuidMan() {
}


RedPill::StatusForRun 
CpuidMan::args_checker() const {
    if (argc_ == 1) {
        return RedPill::StatusForRun::kCould;
    }

    if (check_args_have_flag(kCpuidMan)) {
        return RedPill::StatusForRun::kNeed;
    }
    return RedPill::StatusForRun::kCannot;
}

std::string 
CpuidMan::red_pill_caller() const {
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