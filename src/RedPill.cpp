#include <string>
#include <cstring>

#include "RedPill.h"

RedPill::RedPill(int argc, const char **argv) : argc_(argc), argv_(argv) {
}

RedPill::RedPill() : RedPill(0, 0) {
}

size_t
RedPill::check_args_have_flag(const std::string& flag) const {
    for (int i = 1; i < argc_; ++i) {
        if (strcmp(argv_[i], ("--" + flag).c_str()) == 0) {
            return i;
        }
    }
    return 0;
}