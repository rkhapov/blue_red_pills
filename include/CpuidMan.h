#pragma once

#include "RedPill.h"

class CpuidMan : public RedPill {
public:
    CpuidMan(int argc, const char ** argv);
    CpuidMan();
    ~CpuidMan();

    RedPill::StatusForRun args_checker() const override;
    std::string red_pill_caller() const override;
private:
};
