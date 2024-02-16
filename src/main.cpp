//
// Created by kello on 22/11/23.
//

#include "main.h"
#include "commands/gen.h"
#include "commands/get.h"
#include "commands/set.h"
#include "commands/glob.h"
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
        free(new gen(argc, argv)); // FIXME: is it the same?
    } else if (strcmp(argv[1], "get") == 0) {
        get(argc, argv);
    } else if (strcmp(argv[1], "set") == 0) {
        set(argc, argv);
    } else if (strcmp(argv[1], "glob") == 0) {
        glob(argc, argv);
    } else {
        std::cout << "ERROR: unknown command, try with \"wisp --help\"" << std::endl;
    }
}