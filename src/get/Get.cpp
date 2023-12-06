//
// Created by kello on 22/11/23.
//

#include "get/Get.h"
#include <cstring>
#include <openssl/sha.h>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string Get::getSHA256(const string &input) {
    const auto *text = reinterpret_cast<const unsigned char *>(input.c_str());
    unsigned int len = strlen((const char *) text);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(text, len, hash);
    stringstream ss;
    ss << hex << setfill('0');
    for (const auto &byte: hash) {
        ss << setw(2) << static_cast<unsigned int>(byte);
    }
    return ss.str();
}