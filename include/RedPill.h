#pragma once

#include <cstring>
#include <string>

class RedPill {
public:

    enum class StatusForRun {kCould, kNeed, kCannot};
    RedPill();
    RedPill(int argc, const char **argv);
    /*
    результат kCould    - нельзя запустить, т.к. аргументы не подходят
    результат kNeed     - можно запустить
    результат kCannot   - требуется запустить
    */
    virtual StatusForRun args_checker() const = 0;

    virtual std::string red_pill_caller() const = 0;

    bool check_args_have_flag(const std::string& flag_name) const;

    virtual ~RedPill() = default;

protected:
    int argc_;
    const char **argv_;
private:
};
