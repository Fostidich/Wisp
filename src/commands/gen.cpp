//
// Created by kello on 22/11/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <sstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "utils/flags.h"
#include "commands/gen.h"
#include "utils/files.h"

using namespace std;

const std::string WISP_PROGRAM_VERSION = "wisp-0.1.0";

gen::gen(int argc, char **argv) {
    flags = genFlags::parse_settings(argc, argv);
    if (flags.help) printHelp();
    else if (flags.version) printVersion();
    else if (flags.random) printRandomKey();
    else if (flags.destroy) destroyAllData();
    else if (flags.list) printList();
    else cerr << "ERROR: no available option selected" << endl;
}

void gen::printHelp() const {
    string dir = getExecutableDir();
    ifstream file;
    if (flags.mask) file.open(dir + "help-text/helpMask.txt");
    else if (flags.example) file.open(dir + "help-text/helpExample.txt");
    else file.open(dir + "help-text/help.txt");
    if (!file.is_open()) {
        cerr << "ERROR: unable to retrieve help data" << endl;
        return;
    }
    string line;
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
    cout << "Do you really want to delete all the personal data?\nWrite \"CONFIRM\" to proceed: ";
    string confirm;
    getline(cin, confirm);
    if (confirm != "CONFIRM") {
        cout << "Nothing was deleted" << endl;
        return;
    }

    string path = getExecutableDir() + "personal-data";
    try {
        if (filesystem::exists(path)) {
            filesystem::remove_all(path);
            cout << "Personal data successfully deleted" << endl;
        } else {
            cerr << "ERROR: no data to delete" << endl;
        }
    } catch (const exception& ex) {
        cerr << "ERROR: unable to delete personal data" << endl;
    }
}

void gen::printList() {
    string path = getExecutableDir() + "personal-data/entries.json";
    ifstream file;
    file.open(path);
    if (!file.is_open()) {
        cout << "No data to show" << endl;
        return;
    }
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();
    cout << jsonData.dump(4) << endl;
    //TODO: print better
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