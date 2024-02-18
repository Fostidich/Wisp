//
// Created by kello on 18/02/24.
//

#ifndef HASH_H
#define HASH_H


#include <string>

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

private:
    /**
     * Value is true if object is undefined
     */
    bool isEmpty;

    /**
     * String form of the hash mask
     */
    std::string stringForm;
};


#endif //HASH_H
