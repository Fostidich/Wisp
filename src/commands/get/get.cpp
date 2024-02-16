//
// Created by kello on 13/12/23.
//

#include <iostream>
#include <cstring>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "commands/get/get.h"

using namespace std;

get::get(int argc, char **argv) {
    hash = new unsigned char[SHA256_DIGEST_LENGTH];

    flags = getFlags::parse_settings(argc, argv);
    if (flags.provider.has_value() && flags.username.has_value()) {
        getHash(flags.provider.value() + flags.username.value());
        printHash();
        printHash("hex");
        printHash("bit");
    } else {
        cerr << "ERROR: provider and username are mandatory" << endl;
    }
}

void get::getHash(const string& input) {
    const auto *text = reinterpret_cast<const unsigned char *>(input.c_str());
    unsigned int len = strlen((const char *) text);
    SHA256(text, len, hash);
}

void get::printHash(const std::string &mod) {
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
