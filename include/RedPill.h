#pragma once

#include <string>

class RedPill {
public:

    RedPill() = default;
    virtual bool args_checker() = 0;
    virtual std::string red_pill_caller() = 0;

    virtual ~RedPill() = default;

protected:
private:
};
