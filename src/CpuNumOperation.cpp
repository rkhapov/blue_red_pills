#include "RedPill.h"
#include "CpuNumOperation.h"
#include "Constants.h"

#include <string>
#include <cstring>
#include <cpuid.h>
#include <stdexcept>

CpuNumOperation::CpuNumOperation(int argc, const char ** argv) : RedPill(argc, argv) {
}

CpuNumOperation::~CpuNumOperation() {
}

CpuNumOperation::CpuNumOperation() {
}



#include <iostream>
RedPill::StatusForRun 
CpuNumOperation::args_checker() const {
    size_t get_acc = check_args_have_flag(kCpuNumOperation);
    if (get_acc && static_cast<size_t>(argc_) >= get_acc + 1) {
        acc_ = std::stoull(argv_[get_acc + 1]);
        return RedPill::StatusForRun::kNeed;
    }
    return RedPill::StatusForRun::kCannot;
}


std::string
CpuNumOperation::red_pill_caller() const {

    uint64_t start_tick = get_current_tick();

    unsigned int empty[4];
    for (size_t i = 0; i < acc_; ++i) {
        __cpuid(0x80000001, empty[0], empty[1], empty[2], empty[3]);
    }

    uint64_t end_tick = get_current_tick();

    double mean_num_ticks = static_cast<double>(end_tick - start_tick) / acc_;

    return "Call " + std::to_string(acc_) + " times command 'cpuid' takes " + 
           std::to_string(end_tick - start_tick) + " ticks" + "( mean ~ " + 
           std::to_string(mean_num_ticks) + "ticks )";
}

uint64_t 
CpuNumOperation::get_current_tick() const {
    unsigned int lo, hi;
    asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );
    return (static_cast<uint64_t>(hi) << 32) | lo;
}