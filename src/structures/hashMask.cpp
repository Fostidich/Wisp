//
// Created by kello on 18/02/24.
//

#include <iostream>
#include <openssl/sha.h>
#include "structures/hashMask.h"
#include "commands/get.h"

using namespace std;

const char symbols[] = {'!', '"', '$', '%', '&', '/', '(',
                        ')', '=', '?', '^', '*', '+',
                        '[',']', '@', '#', '_', ';',
                        ':', ',', '.'};

hashMask::hashMask() : isEmpty(true), splitsCount(0) {
    splits = nullptr;
}

hashMask::hashMask(std::string &hashString) :
        stringForm(hashString), isEmpty(false) {
    int count = 0;
    for (int i = 0; stringForm[i] != '\0'; i++) {
        if (stringForm[i] == '.') count++;
    }
    ++count;
    splits = new char[count];
    splitsCount = count;
}

bool hashMask::empty() const { return isEmpty; }

std::string hashMask::toString() {
    return stringForm;
}

void hashMask::satisfyConstraints() {
    //TODO
}

std::string hashMask::assign(unsigned char *plot) {
    char result[splitsCount + 1];
    int *sections = getSections(plot);

    for (int i = 0; i < splitsCount; ++i) {
        switch(splits[i]) {
            case '-': result[i] = '-';
            case 'a': result[i] = char('a' + sections[i] % 26);
            case 'b': result[i] = char('A' + sections[i] % 26);
            case 'c': result[i] = char('0' + sections[i] % 10);
            case 'd': result[i] = symbols[sections[i] % 22];
        }
    }

    result[splitsCount] = '\0';
    delete[] sections;
    return result;
}

int *hashMask::getSections(const unsigned char *plot) const {
    auto result = new int[splitsCount];
    int sectionLength = SHA256_DIGEST_LENGTH * 8 * 4 / splitsCount;

    get::printHash(plot, 4, "b", true);

    unsigned char temp = plot[0], temp2, latest = 0xFF;
    int j = 1;
    for (; j < sectionLength / 8; ++j) {
        temp ^= plot[j];
    }
    for (int k = 0; k < sectionLength % 8; ++k) {
        latest = latest >> 1;
    }
    temp2 = temp;
    temp ^= (plot[j + 1] & ~ latest) | (temp & latest);
    get::printHash(&plot[j + 1] , 1, "b");
    get::printHash(&temp, 1, "b");
    temp |= (temp2 & latest);
    result[0] = temp;

    get::printHash(&temp, 1, "b");
    get::printHash(&temp2, 1, "b");
    exit(1);

    for (int i = 0; i < splitsCount; ++i) {
        //TODO
    }

    return result;
}