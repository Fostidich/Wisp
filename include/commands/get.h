//
// Created by kello on 13/12/23.
//

#ifndef GET_H
#define GET_H


#include "utils/flags.h"

class get {
public:
    /**
     * Class constructor.
     * Flags are put into flags struct
     * @param argc main argc
     * @param argv main argv
     */
    get(int argc, char **argv);

private:
    /**
     * Flags struct contains:\n
     * - provider\n
     * - username\n
     * - hash\n
     * - update\n
     * - clipboard\n
     */
    getFlags::Flags flags;

    /**
     * Store the SHA256 got from getHash()
     */
    unsigned char *hash;

    /**
     * Run SHA256 on the input string and store the digest into the hash attribute
     */
    void getHash(const std::string &input);

    /**
     * Print the hash attribute
     * @param mod select print mode (hex, bit, or empty)
     */
    void printHash(const std::string &mod = "");
};


#endif //GET_H
