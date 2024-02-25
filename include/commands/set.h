//
// Created by kello on 15/02/24.
//

#ifndef SET_H
#define SET_H


#include "utils/flags.h"

class set {
public:
    /**
     * Class constructor.
     * Flags are put into flags struct
     * @param argc main argc
     * @param argv main argv
     */
    set(int argc, char **argv);

private:
    /**
     * Flags struct contains:\n
     * - provider\n
     * - username\n
     * - hash\n
     * - update\n
     * - annotation\n
     * - remove\n
     */
    setFlags::Flags flags;

    /**
     * Update or generate a new element with the provided attributes
     * @param provider provider input string
     * @param username username input string
     */
    void setEntry(const std::string& provider, const std::string& username);

    /**
     * Remove element with the provided attributes
     * @param provider provider input string
     * @param username username input string
     */
    static void deleteEntry(const std::string& provider, const std::string& username);
};


#endif //SET_H
