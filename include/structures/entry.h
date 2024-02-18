//
// Created by kello on 18/02/24.
//

#ifndef ENTRY_H
#define ENTRY_H


#include <string>
#include "structures/hash.h"

class entry {
public:
    /**
     * Class constructor.
     * Provider and username are mandatory, other attributes can be set with
     * respective setters
     * @param provider provider input value
     * @param username username input value
     */
    entry(std::string& provider, std::string& username);

    /**
     * Getter for provider
     * @return provider string
     */
    std::string getProvider();

    /**
     * Getter for username
     * @return  username string
     */
    std::string getUsername();

    /**
     * Getter for hash
     * @return hash object
     */
    hash getHash();

    /**
     * Getter for update
     * @return update integer
     */
    unsigned int getUpdate() const;

    /**
     * Getter for annotation
     * @return annotation string
     */
    std::string getAnnotation();

    /**
     * Setter for hash
     * @param newHash hash object
     */
    void setHash(const hash& newHash);

    /**
     * Setter for update
     * @param newUpdate update integer
     */
    void setUpdate(int newUpdate);

    /**
     * Setter for annotation
     * @param newAnnotation annotation string
     */
    void setAnnotation(std::string& newAnnotation);

    /**
     * Entry is returned in string form
     * @return entry string
     */
    std::string toString();

private:

    /**
     * Provider string is always defined
     */
    std::string provider;

    /**
     * Username string is always defined
     */
    std::string username;

    /**
     * Hash object is always initialized but it can be null-value
     */
    hash hash;

    /**
     * Update number has 0 as default value, if it is not been set afterwards
     */
    unsigned int update{0};

    /**
     * Annotation string is an optional custom phrase
     */
    std::string annotation;

    //TODO: date
};


#endif //ENTRY_H
