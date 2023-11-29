//
// Created by kello on 22/11/23.
//

#include "general/General.h"
#include "Main.h"
#include <iostream>
#include <fstream>

using namespace std;

void General::execute() {
    printHelp();
    printVersion();
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
    cout << "VERSION:\n\n\tCurrently running version: " << wisp_program_version << endl;
}
