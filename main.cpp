#include "controller.h"
#include <iostream>

int main() {
    std::cout << "Simple Calculator\n";
    std::cout << "> ";
    repl(std::cin, std::cout);
    return 0;
}
