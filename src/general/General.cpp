//
// Created by kello on 22/11/23.
//

#include "../../include/general/General.h"

#include <iostream>

General::General(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Error: no command provided, try \"wisp --help\"" << std::endl;
        exit(1);
    }
    switch (argv) {
        case "-v" || "--version": printVersion();
    }
}

