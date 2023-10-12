#pragma once

#pragma once

#include "RedPill.h"

#include <memory>

class CpuNumOperation : public RedPill {
public:
    CpuNumOperation(int argc, const char ** argv);
    CpuNumOperation();
    ~CpuNumOperation();

    RedPill::StatusForRun args_checker() const override;
    std::string red_pill_caller() const override;
protected:
    uint64_t get_current_tick() const;
    mutable size_t acc_;
};
