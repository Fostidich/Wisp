//
// Created by kello on 22/11/23.
//

#include "gen/gen.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const std::string WISP_PROGRAM_VERSION = "wisp-0.1.0";

gen::gen(int argc, const char **argv) {
    flags = genFlags::parse_settings(argc, argv);
    if (flags.help) printHelp();
    else if (flags.version) printVersion();
}

void gen::printHelp() const {
    ifstream file;
    if (flags.mask) file.open("assets/help-text/helpMask.txt");
    else if (flags.example) file.open("assets/help-text/helpExample.txt");
    else file.open("assets/help-text/help.txt");
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

using namespace genFlags;
Flags genFlags::parse_settings(const int argc, const char **argv) {
    Flags settings;
    for (int i = 1 /* use 2 if a command is provided */; i < argc; i++) {
        string opt{argv[i]};
        if (auto j{NoArgs.find(opt)}; j != NoArgs.end())
            j->second(settings);
        else if (auto k{OneArgs.find(opt)}; k != OneArgs.end())
            if (++i < argc || argv[1][0] != '-')
                k->second(settings, {argv[i]});
            else
                throw std::runtime_error{"ERROR: missing parameter after flag " + opt};
        else
            cerr << "ERROR: unrecognized command-line option " << opt << endl;
    }
    return settings;
}