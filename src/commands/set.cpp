//
// Created by kello on 15/02/24.
//

#include "commands/set.h"
#include <iostream>

using namespace std;

set::set(int argc, char **argv) {
    flags = setFlags::parse_settings(argc, argv);
    if (flags.provider.has_value() && flags.username.has_value()) {
        cout << flags.provider.value() << endl;
        cout << flags.username.value() << endl;
    }
}
