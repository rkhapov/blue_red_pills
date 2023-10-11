#include "Constants.h"
#include "RedPill.h"
#include "SimpleRedPill.h"

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
    SimpleRedPill first_pill = SimpleRedPill(argc, const_argv);
    all_red_pills.push_back(
        std::make_shared<SimpleRedPill>(first_pill)
    );

    for (const auto& red_pill : all_red_pills) {
        if (red_pill->args_checker()) {
            std::cout << red_pill->red_pill_caller() << "\n";
        }
    }
}
