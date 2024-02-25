//
// Created by kello on 15/02/24.
//

#ifndef GLOB_H
#define GLOB_H


#include "utils/flags.h"

/// Length of the random generated token
extern const unsigned int TOKEN_LEN;

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

    /**
     * Update global hash value in config.ini
     * @param newHash new hash to set
     */
    static void setHash(const std::string& newHash);

    /**
     * Update global token value in config.ini
     * @param newToken new token to set
     */
    static void setToken(const std::string& newToken);

    /**
     * Generate a random token that can be set as the global one
     */
    static void generateToken();

    /**
     * Print the global token value
     */
    static void printToken();

    /**
     * Get the global token value
     * @return global token string
     */
    static std::string getToken();
};


#endif //GLOB_H
