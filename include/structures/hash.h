//
// Created by kello on 18/02/24.
//

#ifndef HASH_H
#define HASH_H


#include <string>

class hash {
public:
    /**
     * Class constructor.
     * Hash is set to null-value (check its value with isNullValue())
     */
    hash();

    /**
     * Class constructor.
     * Initial actions on the hash mask string are performed
     * @param hashMask is the string which defines the hash mask
     */
    hash(std::string &hashMask);

    /**
     * If object is undefined, null-value is true
     * @return null-value of the object
     */
    bool isNullValue() const;

    /**
     * Hash mask is returned in string form
     * @return hash mask string
     */
    std::string toString();

private:
    /**
     * Value is true if object is undefined
     */
    bool isNull;

    /**
     * String form of the hash mask
     */
    std::string hashMask;
};


#endif //HASH_H
