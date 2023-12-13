//
// Created by kello on 13/12/23.
//

#ifndef GET_H
#define GET_H


#include "utils/flags.h"

class get {
public:
    get(int argc, char **argv);

private:
    getFlags::Flags flags;

    void getHash();
};


#endif //GET_H
