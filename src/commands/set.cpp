//
// Created by kello on 15/02/24.
//

#include "commands/set.h"
#include "utils/files.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using namespace nlohmann;

set::set(int argc, char **argv) {
    using namespace filesystem;
    string dir = getExecutableDir() + "personal-data";
    if (!exists(dir)) {
        if (!create_directories(dir)) {
            cerr << "ERROR: unable to create personal data folder" << endl;
            return;
        }
    }
    if (!exists(dir + "/entries.json")) {
        nlohmann::json newJson = nlohmann::json::object();
        ofstream file(dir + "/entries.json");
        file << setw(4) << newJson << endl;
        file.close();
        if (!exists(dir + "/entries.json")) {
            cerr << "ERROR: unable to generate entries.json" << endl;
            return;
        }
    }

    flags = setFlags::parse_settings(argc, argv);
    if (flags.provider.has_value() && flags.username.has_value()) {
        if (flags.remove)
            deleteEntry(flags.provider.value(), flags.username.value());
        else
            setEntry(flags.provider.value(), flags.username.value());
    } else {
        cerr << "ERROR: provider and username are mandatory" << endl;
    }
}

void set::setEntry(const std::string &provider, const std::string &username) {
    string path = getExecutableDir() + "personal-data/entries.json";
    ifstream inFile;
    inFile.open(path);
    if (!inFile.is_open()) {
        cerr << "ERROR: unable to read entries.json" << endl;
        return;
    }
    nlohmann::json jsonData;
    inFile >> jsonData;
    inFile.close();

    bool found = false;
    for (auto &element: jsonData) {
        if (element["provider"] == provider &&
            element["username"] == username) {
            if (flags.hash.has_value())
                element["hash"] = flags.hash.value();
            if (flags.update.has_value())
                element["update"] = stoi(flags.update.value());
            if (flags.annotation.has_value())
                element["annotation"] = flags.annotation.value();
            found = true;
            break;
        }
    }
    if (!found) {
        json element = {
                {"provider", provider},
                {"username", username}
        };
        if (flags.hash.has_value())
            element["hash"] = flags.hash.value();
        if (flags.update.has_value())
            element["update"] = stoi(flags.update.value());
        if (flags.annotation.has_value())
            element["annotation"] = flags.annotation.value();
        jsonData.push_back(element);
    }

    ofstream outFile;
    outFile.open(path);
    outFile << setw(4) << jsonData << endl;
    cout << "Entry list updated" << endl;
}

void set::deleteEntry(const string &provider, const string &username) {
    string path = getExecutableDir() + "personal-data/entries.json";
    ifstream inFile;
    inFile.open(path);
    if (!inFile.is_open()) {
        cerr << "ERROR: unable to read entries.json" << endl;
        return;
    }
    nlohmann::json jsonData;
    inFile >> jsonData;
    inFile.close();

    auto it = remove_if(jsonData.begin(),
                        jsonData.end(),
                        [&](const auto& element) {
        return (element["provider"] == provider && element["username"] == username);
    });
    jsonData.erase(it, jsonData.end());


    ofstream outFile;
    outFile.open(path);
    outFile << setw(4) << jsonData << endl;
    cout << "Entry list updated" << endl;
}
