#include "RedPill.h"
#include "CpuNumOperation.h"
#include "Constants.h"

#include <string>
#include <cstring>
#include <cpuid.h>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

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

    const size_t quantile = 40;

    std::vector<uint64_t> ticks_counts;    
    uint64_t start_tick, end_tick;

    unsigned int empty[4];
    for (size_t i = 0; i < acc_; ++i) {
        start_tick = get_current_tick();
        __cpuid(0x80000001, empty[0], empty[1], empty[2], empty[3]);
        end_tick = get_current_tick();
        ticks_counts.push_back(end_tick - start_tick);
    }


    std::sort(ticks_counts.begin(), ticks_counts.end());


    uint64_t q_0025 = ticks_counts[acc_ / quantile], q_975 = ticks_counts[acc_ - acc_ / quantile];

    for (int i = 0; i < 10; ++i) {
        std::cout << ticks_counts[ticks_counts.size() -  i - 1] << "\n";
    }

    double mean =  static_cast<double>(std::accumulate(
                                       ticks_counts.begin(), 
                                       ticks_counts.end(), 
                                       0ULL
    )) / acc_;



    double std = static_cast<double>(std::accumulate(
                                         ticks_counts.begin(),
                                         ticks_counts.end(),
                                         0ULL,
                                         [&mean](uint64_t first, uint64_t second) {
                                             return first + (second - mean) * (second - mean);
                                         }
    )) / acc_;

    std::string confidence_interval = "(" + std::to_string(q_0025) + " : " + std::to_string(q_975) + ")"; 

    std::string command = "cpuid", number_call = std::to_string(acc_);   

    return "Command: "          + command + "\n" + 
           "Number of call: "   + number_call + + "\n" + 
           "95% interval: "     + confidence_interval + "\n" +
           "Mean: "             + std::to_string(mean) + "\n" + 
           "Std: "              + std::to_string(std::sqrt(std)) + "\n"
           "Last value: "       + std::to_string(ticks_counts.back());
}

uint64_t 
CpuNumOperation::get_current_tick() const {
    unsigned int lo, hi;
    asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );
    return (static_cast<uint64_t>(hi) << 32) | lo;
}