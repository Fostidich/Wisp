//
// Created by kello on 22/11/23.
//

#include <iostream>
#include <openssl/sha.h>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "general/General.h"

using namespace std;

int main(const int argc, char *argv[]) {
    if (argc > 1) {
        General::execute(argv[1]);
        return 0;
    }
    cout << "Enter word: ";
    string input;
    getline(cin, input);
    const auto* text = reinterpret_cast<const unsigned char*>(input.c_str());
    unsigned int len = strlen ((const char*) text);
    unsigned char hash [SHA256_DIGEST_LENGTH];
    SHA256(text, len, hash);
    stringstream ss;
    ss << hex << setfill('0');
    for (const auto& byte : hash) {
        ss << setw(2) << static_cast<unsigned int>(byte);
    }
    cout << ss.str() << endl;
    return 0;
}
