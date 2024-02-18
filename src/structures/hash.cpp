//
// Created by kello on 18/02/24.
//

#include "structures/hash.h"

hash::hash() : isNull(true) {}

hash::hash(std::string &hashMask) :
        hashMask(hashMask), isNull(false) {
    //TODO: do things with the string
}

bool hash::isNullValue() const { return isNull; }

std::string hash::toString() {
    return hashMask;
}

