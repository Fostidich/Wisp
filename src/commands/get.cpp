//
// Created by kello on 13/12/23.
//

#include <iostream>
#include <cstring>
#include <openssl/sha.h>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "commands/get.h"
#include "nlohmann/json.hpp"
#include "utils/files.h"
#include "commands/glob.h"
#include "utils/utils.h"

//TODO: manage clipboard
//TODO: set if new

using namespace std;

get::get(int argc, char **argv) {
    inputs = new unordered_map<string, string>();

    flags = getFlags::parse_settings(argc, argv);
    if (flags.provider.has_value() && flags.username.has_value()) {
        retrieveInputs();
    } else {
        cerr << "ERROR: provider and username are mandatory" << endl;
    }

    delete inputs;
}

void get::retrieveInputs() {
    string key;
    while(true) {
        cout << "Enter personal key: ";
        char ch;
        while ((ch = getHiddenChar()) != '\n') {
            key += ch;
            std::cout << '*';
        }
        cout << endl;
        if (key.empty()) cout << "No key inserted, try again" << endl;
        else break;
    }

    inputs->insert(make_pair("key", key));
    inputs->insert(make_pair("token", glob::getToken()));
    inputs->insert(make_pair("provider", flags.provider.value()));
    inputs->insert(make_pair("username", flags.username.value()));

    if (flags.update.has_value())
        inputs->insert(make_pair("update", flags.update.value()));
    else {
        string update = getEntryValue("update");
        inputs->insert(make_pair("update", update.empty() ? "0" : update));
    }
    if (flags.hash.has_value())
        inputs->insert(make_pair("hash", flags.hash.value()));
    else {
        string hash = getEntryValue("hash");
        inputs->insert(make_pair("hash", hash.empty() ? glob::getHash() : hash));
    }

    for (const auto& el : *inputs) {
        cout << el.first + ": " + el.second << endl;
    }
}

unsigned char *get::getHash(const string &input) {
    auto *hash = new unsigned char[SHA256_DIGEST_LENGTH];
    const auto *text = reinterpret_cast<const unsigned char *>(input.c_str());
    unsigned int len = strlen((const char *) text);
    SHA256(text, len, hash);
    return hash;
}

void get::printHash(unsigned char *hash, const std::string &mod) {
    if (mod.empty()) {
        cout << hash << endl;
        return;
    }
    if (mod == "bit" || mod == "b") {
        stringstream ss;
        for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            for (int j = 7; j >= 0; j--) {
                ss << ((hash[i] >> j) & 1);
            }
            // ss << " ";
        }
        cout << ss.str() << endl;
    } else if (mod == "hex" || mod == "h") {
        stringstream ss;
        ss << hex << setfill('0');
        for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << setw(2) << static_cast<unsigned int>(hash[i]);
        }
        cout << ss.str() << endl;
    }
}

std::string get::getEntryValue(const string &name) {
    string path = getExecutableDir() + "personal-data/entries.json";
    ifstream file;
    file.open(path);
    if (!file.is_open()) {
        cout << "No data to show" << endl;
        return "";
    }
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();
    for (auto el: jsonData) {
        if (el["provider"] == flags.provider.value() &&
            el["username"] == flags.username.value()) {
            if (!el.contains(name)) return "";
            if (el[name].is_string()) return el[name];
            else return to_string(el[name]);
        }
    }
    return "";
}
