//
// Created by kello on 22/11/23.
//

#ifndef GEN_H
#define GEN_H


#include <string>
#include <optional>
#include <functional>
#include "utils/flags.h"

/// Program name and version
extern const std::string WISP_PROGRAM_VERSION;

class gen {
public:
    /**
     * Class constructor.
     * Flags are put into flags struct
     * @param argc main argc
     * @param argv main argv
     */
    gen(int argc, char **argv);

private:
    /**
     * Flags struct contains:\n
     * - help\n
     * - mask\n
     * - example\n
     * - version\n
     * - random\n
     * - destroy\n
     * - list\n
     */
    genFlags::Flags flags;

    /**
     * Print the help panel. If additional options have been defined, the specific help
     * panel is printed
     */
    void printHelp() const;

    /**
     * Print the program version
     */
    static void printVersion();

    /**
     * Print a random key that can become the personal one to be used
     */
    static void printRandomKey();

    /**
     * Delete the full "personal-data" folder
     */
    static void destroyAllData();

    /**
     * The list of entries contained in the entries.json file is printed
     */
    static void printList();

    /**
     * Generate a random char between digits, uppercase and lowercase letters, hyphen and pound
     * @return the random char
     */
    static char randomChar();
};


#endif //GEN_H
