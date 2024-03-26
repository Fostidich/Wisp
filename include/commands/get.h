//
// Created by kello on 13/12/23.
//

#ifndef GET_H
#define GET_H


#include "utils/flags.h"

/// Input hashes shifts are multiplied by a constant
extern const int SHIFT_MUL;

class get {
public:
    /**
     * Class constructor.
     * Flags are put into flags struct
     * @param argc main argc
     * @param argv main argv
     */
    get(int argc, char **argv);

/**
 * Print the hash attribute
 * @param hash is the bit string to print
 * @param length is the length of the plot array
 * @param mod select print mode (hex, bit, or empty)
 * @param spaces if true, spaces are added between bytes
 */
static void printHash(const unsigned char *hash, int length = 32, const std::string &mod = "b",  bool spaces = true);

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
     * Calculated hash made from all inputs
     */
    unsigned char *fullHash;

/**
 * Run SHA256 on the input string and store the digest into the hash attribute
 * @param input is the string to make an hash of
 * @return the SHA256 hash in bytes form
 */
    static unsigned char *getSHA256(const std::string &input);

    /**
     * Inputs map attribute is filled with all necessary string, by retrieving them
     * from files or args
     */
    void retrieveInputs();

    /**
     * Given the string name of the attribute, the value is returned.
     * The json entry is searched by comparing provider and username fields.
     * If the entry is not found, or if the field isn't specified, empty string is returned.
     * @param name string name of the field
     * @return requested string value
     */
    std::string getEntryValue(const std::string &name);

    /**
     * Starting from inputs map, the full hash is calculated
     */
    void calculateHash();

    /**
     * Starting from the full hash previously calculated, a usable hash
     * is printed based on the hash mask
     */
    void printHashWithMask();

    /**
     * Provided array is shifter right num times
     * @param v is the vector to shift
     * @param length is the length of the vector
     * @param num is the number of shifts
     */
    static void shiftRight(unsigned char *v, size_t length, int num);
};


#endif //GET_H
