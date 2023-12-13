//
// Created by kello on 22/11/23.
//

#include "main.h"
#include "commands/gen/gen.h"
#include "commands/get/get.h"
#include <iostream>
#include <cstring>

int main(int argc, char **argv) {
    assignFlags(argc, argv);
    return 0;
}

void assignFlags(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "ERROR: no input provided, try with \"wisp --help\"" << std::endl;
    } else if (argv[1][0] == '-') {
        gen(argc, argv);
    } else if (strcmp(argv[1], "get") == 0) {
        get(argc, argv);
    } else {
        //TODO: switch commands
    }
}