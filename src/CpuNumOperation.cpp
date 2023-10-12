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


#define get_current_tick(ticks)  { \
    unsigned int lo, hi;                                \
    asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi));   \
    *ticks = (static_cast<uint64_t>(hi) << 32) | lo;     \
    }

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
        get_current_tick(&start_tick);
        __cpuid(0x80000001, empty[0], empty[1], empty[2], empty[3]);

        get_current_tick(&end_tick);

        ticks_counts.push_back(end_tick - start_tick);
    }

    std::sort(ticks_counts.begin(), ticks_counts.end());

    uint64_t q_0025 = ticks_counts[acc_ / quantile], q_975 = ticks_counts[acc_ - acc_ / quantile - 1];

    double mean =  static_cast<double>(std::accumulate(
                                       ticks_counts.begin() +  acc_ / quantile, 
                                       ticks_counts.end() -  acc_ / quantile, 
                                       0ULL
    )) / acc_;

    double std = static_cast<double>(std::accumulate(
                                         ticks_counts.begin() + acc_ / quantile,
                                         ticks_counts.end() - acc_ / quantile,
                                         0ULL,
                                         [&mean](uint64_t first, uint64_t second) {
                                             return first + (second - mean) * (second - mean);
                                         }
    )) / acc_;

    std::string confidence_interval = "(" + std::to_string(q_0025) + " : " + std::to_string(q_975) + ")"; 

    std::string command = "cpuid", number_call = std::to_string(acc_);  

    size_t fib_num = 100;
    return "Command: "          + command + "\n" + 
           "Number of call: "   + number_call + + "\n" + 
           "95% interval: "     + confidence_interval + "\n" +
           "Mean: "             + std::to_string(mean) + "\n" + 
           "Std: "              + std::to_string(std::sqrt(std)) + "\n" + 
           "Fib take "          + std::to_string(get_mean_ticks_takes_fib(fib_num)) + " for " + std::to_string(fib_num) + " number";
}

double
CpuNumOperation::get_mean_ticks_takes_fib(size_t n) const {
    uint64_t start_time, end_time;

    std::vector<uint64_t> one_circ_take;

    for (size_t i = 0; i < acc_; ++i) {
        get_current_tick(&start_time);

        int64_t a0 = 0;
        int64_t a1 = 1;
        int64_t cur;
        
        for(size_t i = 2; i < n; i++) {
            cur = a0 + a1;
            a0 = a1;
            a1 = cur;
        }

        get_current_tick(&end_time);
        one_circ_take.push_back(end_time - start_time);
    }

    return static_cast<double>( std::accumulate(one_circ_take.begin(), one_circ_take.end(), 0ULL)) / acc_;
}
