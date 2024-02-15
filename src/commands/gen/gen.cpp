//
// Created by kello on 22/11/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include "utils/flags.h"
#include "commands/gen/gen.h"
#include "utils/files.h"

using namespace std;

const std::string WISP_PROGRAM_VERSION = "wisp-0.1.0";

gen::gen(int argc, char **argv) {
    flags = genFlags::parse_settings(argc, argv);
    if (flags.help) printHelp();
    else if (flags.version) printVersion();
    else if (flags.random) printRandomKey();
}

void gen::printHelp() const {
    std::string executableDir = getExecutableDir();
    ifstream file;
    if (flags.mask) file.open(executableDir + "assets/help-text/helpMask.txt");
    else if (flags.example) file.open(executableDir + "assets/help-text/helpExample.txt");
    else file.open(executableDir + "assets/help-text/help.txt");
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

void gen::printVersion() {
    cout << "VERSION:\n\n\tCurrently running version: " << WISP_PROGRAM_VERSION << "\n" << endl;
}

void gen::printRandomKey() {

};