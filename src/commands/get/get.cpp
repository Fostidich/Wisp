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
    flags = getFlags::parse_settings(argc, argv);
    if (flags.provider.has_value() && flags.username.has_value()) getHash();
    else {
        std::cout << "ERROR: provider or username are mandatory" << std::endl;
    }
}

void get::getHash() {
    string input = flags.provider.value() + flags.username.value();
    const auto *text = reinterpret_cast<const unsigned char *>(input.c_str());
    unsigned int len = strlen((const char *) text);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(text, len, hash);
    stringstream ss;
    ss << hex << setfill('0');
    for (const auto &byte: hash) {
        ss << setw(2) << static_cast<unsigned int>(byte);
    }
    cout << ss.str() << endl;
}