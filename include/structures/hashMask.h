//
// Created by kello on 18/02/24.
//

#ifndef HASH_H
#define HASH_H


#include <string>

/// The array contains all the symbols that can be used as an hash character
extern const char symbols[];

class hashMask {
public:
    /**
     * Class constructor.
     * Hash is set to empty-value
     */
    hashMask();

    /**
     * Class constructor.
     * Initial actions on the hash mask string are performed
     * @param hashMask is the string which defines the hash mask
     */
    explicit hashMask(std::string &hashString);

    /**
     * If object is undefined, object is empty
     * @return empty-value of the object
     */
    [[nodiscard]] bool empty() const;

    /**
     * Hash mask is returned in string form
     * @return hash mask string
     */
    std::string toString();

    /**
     * Hash mask is reduced to have only one possible character type for section.
     * Every character type that appears will be found in the satisfied hash mask at least once
     * (if possible).
     */
    void satisfyConstraints();

    /**
     * Plot is split in sections and the hash (from hash mask) is computed.
     * @param plot hash of the inputs
     * @return final hash
     */
    std::string assign(unsigned char* plot);

private:
    /**
     * Value is true if object is undefined
     */
    bool isEmpty;

    /**
     * When constraints are satisfied, resulting char are put in a vector
     */
    char* splits;

    /**
     * Size of splits vector;
     */
    int splitsCount;

    /**
     * String form of the hash mask
     */
    std::string stringForm;

    /**
     * Plot is divided in sections, and the integer of each section is put in the returned array
     * @param plot bits input string
     * @return sections integer array
     */
    int *getSections(unsigned char *plot);
};


#endif //HASH_H
