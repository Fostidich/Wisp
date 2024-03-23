//
// Created by kello on 18/02/24.
//

#include <openssl/sha.h>
#include <iostream>
#include "structures/hashMask.h"
#include "commands/get.h"

using namespace std;

const char symbols[] = {'!', '"', '$', '%', '&', '/', '(',
                        ')', '=', '?', '^', '*', '+',
                        '[', ']', '@', '#', '_', ';',
                        ':', ',', '.'};

hashMask::hashMask() : isEmpty(true), splitsCount(0) {
    splits = nullptr;
}

hashMask::hashMask(std::string &hashString) :
        stringForm(hashString), isEmpty(false) {
    int count = 1;
    for (int i = 0; stringForm[i] != '\0'; i++) {
        if (stringForm[i] == '.') count++;
    }
    splits = new char[count];
    splitsCount = count;
}

bool hashMask::empty() const { return isEmpty; }

std::string hashMask::toString() {
    return stringForm;
}

void hashMask::satisfyConstraints() {
    //TODO
    for (int i = 0; i < splitsCount; ++i)
        splits[i] = stringForm[2 * i];
}

std::string hashMask::assign(unsigned char *plot) {
    //TODO: to test
    char *result = new char[splitsCount + 1];
    int *sections = getSections(plot);

    for (int i = 0; i < splitsCount; ++i) {
        switch (splits[i]) {
            case '-':
                result[i] = '-';
                break;
            case 'a':
                result[i] = char('a' + sections[i] % 26);
                break;
            case 'b':
                result[i] = char('A' + sections[i] % 26);
                break;
            case 'c':
                result[i] = char('0' + sections[i] % 10);
                break;
            case 'd':
                result[i] = symbols[sections[i] % 22];
                break;
        }
    }
    result[splitsCount] = '\0';

    delete[] sections;
    return result;
}

int *hashMask::getSections(const unsigned char *plot) const {
    auto *result = new int[splitsCount];
    auto *temp = new unsigned char[SHA256_DIGEST_LENGTH];
    auto *temp2 = new unsigned char[SHA256_DIGEST_LENGTH];
    unsigned char toAdd;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        temp[i] = plot[i];

    for (int i = 0; i < splitsCount; ++i) {
        SHA256(temp, SHA256_DIGEST_LENGTH, temp2);
        toAdd = temp2[0];
        for (int j = 1; j < SHA256_DIGEST_LENGTH; ++j)
            toAdd ^= temp2[j];
        result[i] = toAdd;
        for (int j = 0; j < SHA256_DIGEST_LENGTH; ++j)
            temp[j] = temp2[j];
    }

    delete[] temp;
    delete[] temp2;
    return result;
}