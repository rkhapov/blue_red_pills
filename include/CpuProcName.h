#pragma once

#include "RedPill.h"

class CpuProcName : public RedPill {
public:
    CpuProcName(int argc, const char ** argv);
    CpuProcName();
    ~CpuProcName();

    RedPill::StatusForRun args_checker() const override;
    std::string red_pill_caller() const override;
private:
};
