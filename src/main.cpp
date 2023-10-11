#include <stdio.h>
#include <string.h>
#include <cpuid.h>
#include <string>
#include <cstring>
#include <map>
#include <iostream>

const std::string kSimple = "Simple";
std::map<bool (*)(int argc, const char** argv), 
         std::string(*)(int argc, const char** argv)> all_red_pills;


bool check_args_for_simply_call(int argc, const char** argv) {
    if (argc == 2 && strcmp(argv[1], kSimple.c_str()) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}


std::string simply_red_pill(int argc, const char** argv)
{
    unsigned int regs[12];
    char str[sizeof(regs)+1];

    __cpuid(0x80000000, regs[0], regs[1], regs[2], regs[3]);

    if (regs[0] < 0x80000004)
        exit(-1);

    __cpuid(0x80000002, regs[0], regs[1], regs[2], regs[3]);
    __cpuid(0x80000003, regs[4], regs[5], regs[6], regs[7]);
    __cpuid(0x80000004, regs[8], regs[9], regs[10], regs[11]);

    memcpy(str, regs, sizeof(regs));
    str[sizeof(regs)] = '\0';

    return std::string(str);

    return 0;
}


int main(int argc, char** argv) {
    all_red_pills[check_args_for_simply_call] = simply_red_pill;

    const char** const_argv = const_cast<const char **>(argv);
    for (const auto& pair_checker : all_red_pills) {
        if (pair_checker.first(argc, const_argv)) {
            std::cout << pair_checker.second(argc, const_argv) << "\n";
        }
    }
}