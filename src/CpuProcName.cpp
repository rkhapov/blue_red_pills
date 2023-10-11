#include "RedPill.h"
#include "Constants.h"
#include "CpuProcName.h"

#include <cstring>
#include <cpuid.h>

CpuProcName::CpuProcName(int argc, const char ** argv) : RedPill(argc, argv) {
}

CpuProcName::CpuProcName() : RedPill() {
}

CpuProcName::~CpuProcName() {
}

RedPill::StatusForRun 
CpuProcName::args_checker() const {
    if (argc_ == 1) {
        return RedPill::StatusForRun::kCould;
    }
    if (check_args_have_flag(kCpuProcName)) {
        return RedPill::StatusForRun::kNeed;
    }
    return RedPill::StatusForRun::kCannot;
}

std::string 
CpuProcName::red_pill_caller() const {
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