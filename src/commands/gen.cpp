//
// Created by kello on 22/11/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "utils/flags.h"
#include "commands/gen.h"
#include "utils/files.h"
#include "utils/utils.h"
#include "structures/entry.h"

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
    cout << "VERSION:\n\n\tCurrently running version: " <<
         WISP_PROGRAM_VERSION << "\n" << endl;
}

void gen::printRandomKey() {
    stringstream ss;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            ss << randomChar();
        }
        ss << "-";
    }
    for (int j = 0; j < 4; j++) {
        ss << randomChar();
    }
    cout << ss.str() << endl;
}

void gen::destroyAllData() {
    cout << "Do you really want to delete all the personal data?\n"
            "Write \"CONFIRM\" to proceed: ";
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
    } catch (const exception &ex) {
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

    unsigned int maxLength = 0;
    vector<entry> entries;
    for (const auto &entryData: jsonData) {
        string provider = entryData["provider"];
        string username = entryData["username"];
        entry newEntry = entry(provider, username);
        if (entryData.contains("hash")) {
            string hash = entryData["hash"];
            newEntry.setMask(hashMask(hash));
        }
        if (entryData.contains("update")) {
            int update = entryData["update"];
            newEntry.setUpdate(update);
        }
        if (entryData.contains("annotation")) {
            string annotation = entryData["annotation"];
            newEntry.setAnnotation(annotation);
        }
        entries.push_back(newEntry);
        unsigned int lineLength = provider.length() + username.length() + 3;
        if (lineLength > maxLength)
            maxLength = lineLength;
    }
    entry::setMaxLengthLine(maxLength);
    for (auto e: entries) {
        cout << e.toString() << endl;
    }
}