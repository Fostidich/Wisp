//
// Created by kello on 22/11/23.
//

#include <iostream>
#include <openssl/sha.h>
#include <cstring>
#include "general/General.h"

using namespace std;

int main(const int argc, char *argv[]) {
    if (argc > 1) {
        General::execute(argv[1]);
        return 0;
    }
    unsigned char text[] = "Kello";
    unsigned int len = strlen ((const char*) text);
    unsigned char hash [SHA256_DIGEST_LENGTH];
    SHA256(text, len, hash);
    for (unsigned char ch: hash)
        cout << (short)ch << "\n";
    return 0;
}
