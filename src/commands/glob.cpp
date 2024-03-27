//
// Created by kello on 15/02/24.
//

#include "commands/glob.h"
#include "utils/files.h"
#include "utils/utils.h"
#include <iostream>
#include <cstring>
#include <mINI/ini.h>
#include <filesystem>

//TODO: manage absence of hash or token when they are get-requested
//TODO: change and show for global hash

using namespace std;

const unsigned int TOKEN_LEN = 18;

glob::glob(int argc, char **argv) {
    flags = globFlags::parse_settings(argc, argv);
    if (flags.hash.has_value()) setHash(flags.hash.value());
    else if (flags.token) {
        if (flags.change.has_value()) setToken(flags.change.value());
        else if (flags.generate) generateToken();
        else if (flags.show) printToken();
    }
}

void glob::setHash(const std::string &newHash) {
    checkDir();
    mINI::INIFile file(getExecutableDir() + "personal-data/config.ini");
    mINI::INIStructure ini;
    if (!file.read(ini)) {
        cerr << "ERROR: unable to read from config.ini" << endl;
        return;
    }
    ini["globals"]["hash"] = newHash;
    if (!file.write(ini)) {
        cerr << "ERROR: unable to write to config.ini" << endl;
        return;
    }
}

void glob::setToken(const std::string &newToken) {
    checkDir();
    mINI::INIFile file(getExecutableDir() + "personal-data/config.ini");
    mINI::INIStructure ini;
    if (!file.read(ini)) {
        cerr << "ERROR: unable to read from config.ini" << endl;
        return;
    }
    ini["globals"]["token"] = newToken;
    if (!file.write(ini)) {
        cerr << "ERROR: unable to write to config.ini" << endl;
        return;
    }
}

void glob::generateToken() {
    char newToken[TOKEN_LEN + 1];
    for (int i{0}; i < TOKEN_LEN; i++)
        newToken[i] = randomChar();
    newToken[TOKEN_LEN] = '\0';
    cout << newToken << endl;

    cout << "Do you want to set this token as global? (Y/n) ";
    string input;
    getline(cin, input);
    if (input.empty() ||
        strcasecmp(input.c_str(), "y") == 0 ||
        strcasecmp(input.c_str(), "yes") == 0) {
        setToken(newToken);
        cout << "New token has been set" << endl;
        return;
    }
    cout << "Global token is unchanged" << endl;
}

void glob::printToken() {
    string token = getToken();
    if (token.empty()) {
        cout << "No token is set" << endl;
    } else cout << token << endl;
}

std::string glob::getToken() {
    checkDir();
    mINI::INIFile file(getExecutableDir() + "personal-data/config.ini");
    mINI::INIStructure ini;
    if (!file.read(ini)) {
        cerr << "ERROR: unable to read from config.ini" << endl;
        return "";
    }
    if (ini["globals"]["token"].empty()) {
        cerr << "ERROR: no token was set" << endl;
        char newToken[TOKEN_LEN + 1];
        for (int i{0}; i < TOKEN_LEN; i++)
            newToken[i] = randomChar();
        newToken[TOKEN_LEN] = '\0';
        setToken(newToken);
        cout << "New token has been generated" << endl;
        return newToken;
    }
    return ini["globals"]["token"];
}

std::string glob::getHash() {
    checkDir();
    mINI::INIFile file(getExecutableDir() + "personal-data/config.ini");
    mINI::INIStructure ini;
    if (!file.read(ini)) {
        cerr << "ERROR: unable to read from config.ini" << endl;
        return "";
    }
    if (ini["globals"]["hash"].empty()) {
        string defHash = "a.a.b.b.-.c.c.d.d";
        cerr << "ERROR: no hash mask was set" << endl;
        setHash(defHash);
        cout << "New hash mask has been generated" << endl;
        return defHash;
    }
    return ini["globals"]["hash"];
}

void glob::checkDir() {
    using namespace filesystem;
    string dir = getExecutableDir() + "personal-data";
    if (!exists(dir)) {
        if (!create_directories(dir)) {
            cerr << "ERROR: unable to create personal data folder" << endl;
            return;
        }
    }
    if (!exists(dir + "/config.ini")) {
        mINI::INIFile file(dir + "/config.ini");
        mINI::INIStructure ini;
        ini["globals"];
        if (!file.generate(ini)) {
            cerr << "ERROR: unable to generate config.ini" << endl;
            return;
        }
    }
}
