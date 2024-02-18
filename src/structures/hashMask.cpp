//
// Created by kello on 18/02/24.
//

#include "structures/hashMask.h"

hashMask::hashMask() : isEmpty(true) {}

hashMask::hashMask(std::string &hashString) :
        stringForm(hashString), isEmpty(false) {
    //TODO: do things with the string
}

bool hashMask::empty() const { return isEmpty; }

std::string hashMask::toString() {
    return stringForm;
}

