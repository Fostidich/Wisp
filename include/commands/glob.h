//
// Created by kello on 15/02/24.
//

#ifndef GLOB_H
#define GLOB_H


#include "utils/flags.h"

class glob {
public:
    /**
     * Class constructor.
     * Flags are put into flags struct
     * @param argc main argc
     * @param argv main argv
     */
    glob(int argc, char **argv);

private:
    /**
     * Flags struct contains:\n
     * - hash\n
     * - token\n
     * - change\n
     * - generate\n
     * - show\n
     */
    globFlags::Flags flags;
};


#endif //GLOB_H
