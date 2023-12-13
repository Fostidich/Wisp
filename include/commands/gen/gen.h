//
// Created by kello on 22/11/23.
//

#ifndef GEN_H
#define GEN_H


#include <string>
#include <optional>
#include <functional>
#include "utils/flags.h"

extern const std::string WISP_PROGRAM_VERSION;

class gen {
public:
    gen(int argc, char **argv);

private:
    genFlags::Flags flags;

    void printHelp() const;

    static void printVersion();
};


#endif //GEN_H
