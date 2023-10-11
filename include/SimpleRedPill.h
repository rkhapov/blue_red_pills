#pragma once

#include "RedPill.h"
#include "SimpleRedPill.h"
#include "Constants.h"

#include <cstring>
#include <string>
#include <cpuid.h>


class SimpleRedPill : public RedPill {
public:
    SimpleRedPill(int argc, const char **argv);

    SimpleRedPill();

    bool args_checker() override;

    std::string red_pill_caller() override;

    std::string red_pill_1();

    std::string red_pill_2();

    std::string red_pill_3();

protected:
    int argc_;
    const char **argv_;
};
