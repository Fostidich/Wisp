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
     * Inputs map contains the strings of:\n
     * - provider\n
     * - username\n
     * - key\n
     * - token\n
     * - update\n
     * - hash mask
     */
    std::unordered_map<std::string, std::string> *inputs;

    /**
     * Inputs map attribute is filled with all necessary string, by retrieving them
     * from files or args
     */
    void retrieveInputs();

    /**
     * Run SHA256 on the input string and store the digest into the hash attribute
     * @param input is the string to make an hash of
     * @return the SHA256 hash in bytes form
     */
    static unsigned char *getHash(const std::string &input);

    /**
     * Print the hash attribute
     * @param mod select print mode (hex, bit, or empty)
     */
    static void printHash(unsigned char *hash, const std::string &mod = "");

    /**
     * Given the string name of the attribute, the value is returned.
     * The json entry is searched by comparing provider and username fields.
     * If the entry is not found, or if the field isn't specified, empty string is returned.
     * @param name string name of the field
     * @return requested string value
     */
    std::string getEntryValue(const std::string &name);
};


#endif //GET_H
