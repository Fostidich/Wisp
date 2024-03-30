//
// Created by kello on 13/12/23.
//

#include <iostream>
#include <cstring>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <list>
#include "commands/get.h"
#include "nlohmann/json.hpp"
#include "utils/files.h"
#include "commands/glob.h"
#include "utils/utils.h"
#include "structures/hashMask.h"

//TODO: manage clipboard copy
//TODO: set the entry in list if it's new

using namespace std;

const int SHIFT_MUL = 4;

get::get(int argc, char **argv) {
    inputs = new unordered_map<string, string>();
    fullHash = new unsigned char[SHA256_DIGEST_LENGTH];

    flags = getFlags::parse_settings(argc, argv);
    if (flags.provider.has_value() && flags.username.has_value()) {
        retrieveInputs();
        checkInputs();
        calculateHash();
        printHashWithMask();
    } else {
        cerr << "ERROR: provider and username are mandatory" << endl;
    }

    delete[] fullHash;
    delete inputs;
}

void get::retrieveInputs() {
    string key;
    while (true) {
        cout << "Enter personal key: ";
        char ch;
        while ((ch = getHiddenChar()) != '\n') {
            key += ch;
            std::cout << "";
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
}

unsigned char *get::getSHA256(const string &input) {
    auto *hash = new unsigned char[SHA256_DIGEST_LENGTH];
    const auto *text = reinterpret_cast<const unsigned char *>(input.c_str());
    unsigned int len = strlen((const char *) text);
    SHA256(text, len, hash);
    return hash;
}

void get::printHash(const unsigned char *hash, int length, const std::string &mod, bool spaces) {
    if (mod.empty()) {
        cout << hash << endl;
        return;
    }
    if (mod == "bit" || mod == "b") {
        stringstream ss;
        for (size_t i = 0; i < length; i++) {
            for (int j = 7; j >= 0; j--) {
                ss << ((hash[i] >> j) & 1);
            }
            if (spaces) ss << " ";
        }
        cout << ss.str() << endl;
    } else if (mod == "hex" || mod == "h") {
        stringstream ss;
        ss << hex << setfill('0');
        for (size_t i = 0; i < length; i++) {
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

void get::calculateHash() {
    //input hash
    vector<unsigned char*> hashes(4);
    hashes[0] = getSHA256(inputs->at("provider"));
    hashes[1] = getSHA256(inputs->at("username"));
    hashes[2] = getSHA256(inputs->at("key"));
    hashes[3] = getSHA256(inputs->at("token"));

    //update shifts
    int shifts = 0;
    for (int i = 0; i < 4; i++) {
        shiftRight(hashes[i], SHA256_DIGEST_LENGTH,
                   SHIFT_MUL * shifts * stoi(inputs->at("update")));
        shifts++;
    }

    //input hashes xor
    auto *plot = new unsigned char[SHA256_DIGEST_LENGTH];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        plot[i] = hashes[0][i];
    for (int i = 1; i < 4; ++i)
        for (int j = 0; j < SHA256_DIGEST_LENGTH; ++j)
            plot[j] ^= hashes[i][j];

    //finish
    fullHash = plot;
}

void get::printHashWithMask() {
    hashMask hash(inputs->at("hash"));
    hash.satisfyConstraints(fullHash);
    string toPrint = hash.assign(fullHash);
    cout << toPrint.c_str() << endl;
}

void get::shiftRight(unsigned char *v, size_t length, int num) {
    typedef unsigned char byte;
    for (int t{0}; t < num; t++) {
        byte currentCarry = v[32 - 1] & 0x01;
        for (size_t i{0}; i < 32; i++) {
            byte carry = v[i] & 0x01;
            v[i] >>= 1;
            v[i] |= (currentCarry << 7);
            currentCarry = carry;
        }
    }
}

void get::checkInputs() {
    auto toAddUpdate = make_pair("update", to_string(stoi(inputs->at("update")) % 64));
    inputs->erase("update");
    inputs->insert(toAddUpdate);

    if (inputs->at("hash").front() == '.' || inputs->at("hash").back() == '.') {
        cerr << "ERROR: Hash mask is not valid; a valid one will be used instead" << endl;
        auto toAddHash = make_pair("hash", "b.ab.ab.a.-.c.c.c.c");
        inputs->erase("hash");
        inputs->insert(toAddHash);
    }
    char temp = '.';
    for (auto ch : inputs->at("hash")) {
        if (ch != 'a' && ch != 'b' && ch != 'c' && ch != 'd' && ch != '.' && ch != '-' ||
        ch == '.' && temp == '.') {
            cerr << "ERROR: Hash mask is not valid; a valid one will be used instead" << endl;
            auto toAddHash = make_pair("hash", "b.ab.ab.a.-.c.c.c.c");
            inputs->erase("hash");
            inputs->insert(toAddHash);
            break;
        }
        temp = ch;
    }
}
