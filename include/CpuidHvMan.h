#pragma once

#include "RedPill.h"

class CpuidHvMan : public RedPill {
public:
    CpuidHvMan(int argc, const char ** argv);
    CpuidHvMan();

    ~CpuidHvMan();

    RedPill::StatusForRun args_checker() const override;
    std::string red_pill_caller() const override;
private:
};
