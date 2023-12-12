//
// Created by kello on 22/11/23.
//

#include <iostream>
#include "main.h"
#include "gen/gen.h"

int main(int argc, const char **argv) {
    assignFlags(argc, argv);
    return 0;
}

void assignFlags(int argc, const char **argv) {
    if (argc < 2) {
        std::cout << "ERROR: no input provided, try with \"wisp --help\"" << std::endl;
    } else if (argv[1][0] == '-') {
        gen(argc, argv);
    } else {
        //TODO: switch commands
    }
}