#include "Constants.h"
#include "RedPill.h"

#include "CpuProcName.h"
#include "CpuidMan.h"
#include "CpuidHvMan.h"
#include "CpuNumOperation.h"


#include <memory>
#include <vector>
#include <iostream>


/*
Для работы после сборки (команда "make")
Затем с желаемыми аргументами ("./main $ARGS")

Можно вызвать с параметром "Simple" и получить вывод вашего процессора с вашей видеокартой
("./main Simple")

*/
int main(int argc, char** argv) {

    std::vector<std::shared_ptr<RedPill>> all_red_pills;

    const char** const_argv = const_cast<const char **>(argv);

    CpuProcName cpuProcName(argc, const_argv);
    CpuidMan cpuidMan(argc, const_argv);
    CpuidHvMan cpuidHvMan(argc, const_argv);
    CpuNumOperation cpuNumOperation(argc, const_argv);
    

    all_red_pills.push_back(
        std::make_shared<CpuProcName>(cpuProcName)
    );

    all_red_pills.push_back(
        std::make_shared<CpuidMan>(cpuidMan)
    );

    all_red_pills.push_back(
        std::make_shared<CpuidHvMan>(cpuidHvMan)
    );

    all_red_pills.push_back(
        std::make_shared<CpuNumOperation>(cpuNumOperation)
    );


    for (const auto& red_pill : all_red_pills) {
        if (red_pill->args_checker() != RedPill::StatusForRun::kCannot) {
            std::cout << red_pill->red_pill_caller() << "\n";
        }
    }
}
