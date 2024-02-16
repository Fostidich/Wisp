//
// Created by kello on 15/02/24.
//

#include "commands/glob.h"
#include <iostream>

using namespace std;

glob::glob(int argc, char **argv) {
    flags = globFlags::parse_settings(argc, argv);
    if (flags.hash.has_value()) {
        cout << flags.hash.value() << endl;
    }
}
