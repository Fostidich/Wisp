//
// Created by kello on 22/11/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <sstream>
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
    // FIXME: help text files are to be generated somehow
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
    stringstream ss;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++){
            ss << randomChar();
        }
        ss << "-";
    }
    for (int j = 0; j < 4; j++){
        ss << randomChar();
    }
    cout << ss.str() << endl;
}

void gen::destroyAllData() {
    cout << "destroy all" << endl;
}

void gen::printList() {
    cout << "full pairs list" << endl;
}

char gen::randomChar() {

    /*
     * 23 pound
     * 45 hyphen
     * 48-57 digits
     * 65-90 uppercase letters
     * 97-122 lowercase letters
     */

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 61);
    int rand = dis(gen);

    if (rand < 10) return char('0' + rand);
    if (rand < 36) return char('A' + rand - 10);
    else return char('a' + rand - 36);
}