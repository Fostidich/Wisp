//
// Created by kello on 22/11/23.
//

#include "general/General.h"
#include "Main.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void General::execute(string flag) {
    switch (flag[2]) {
        case 'h':
            printHelp();
            break;
        case 'v':
            printVersion();
            break;
        default:
            cout << "Unrecognised flag" << endl;
    }
}

void General::printHelp() {
    ifstream file("assets/helpText/help.txt");
    string line;
    if (!file.is_open()) {
        cout << "Error: unable to retrieve help data" << endl;
        return;
    }
    while (getline(file, line)) {
        cout << line << '\n';
    }
    cout << endl;
    file.close();
}

void General::printVersion() {
    cout << "VERSION:\n\n\tCurrently running version: " << WISP_PROGRAM_VERSION << "\n" << endl;
}
