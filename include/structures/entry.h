//
// Created by kello on 18/02/24.
//

#ifndef ENTRY_H
#define ENTRY_H


#include <string>
#include "structures/hashMask.h"
#include "structures/date.h"

class entry {
public:
    /**
     * Class constructor.
     * Provider and username are mandatory, other attributes can be set with
     * respective setters
     * @param provider provider input value
     * @param username username input value
     */
    entry(std::string& provider, std::string& username, std::string& sDate);

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
     * Getter for mask
     * @return hash mask object
     */
    hashMask getMask();

    /**
     * Getter for update
     * @return update integer
     */
    [[nodiscard]] unsigned int getUpdate() const;

    /**
     * Getter for annotation
     * @return annotation string
     */
    std::string getAnnotation();

    /**
     * Getter for date
     * @return last modified date
     */
    date getLastModified();

    /**
     * Setter for mask
     * @param newMask hash mask object
     */
    void setMask(const hashMask& newMask);

    /**
     * Setter for update
     * @param newUpdate update integer
     */
    void setUpdate(unsigned int newUpdate);

    /**
     * Setter for annotation
     * @param newAnnotation annotation string
     */
    void setAnnotation(std::string& newAnnotation);

    /**
     * Setter for max length line
     * @param newMaxLengthLine max length line integer
     */
    static void setMaxLengthLine(unsigned int newMaxLengthLine);

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
     * Custom hash mask for the entry
     */
    hashMask mask;

    /**
     * Update number has 0 as default value, if it is not been set afterwards
     */
    unsigned int update{0};

    /**
     * Annotation string is an optional custom phrase
     */
    std::string annotation;

    /**
     * Date of the last changes
     */
    date lastModified;

    /**
     * Constant length of the string made of provider and username
     */
    static unsigned int maxLengthLine;

    /**
     * Given a string, return a string containing as many spaces as to
     * fill the constant length line. If input word is longer, one space
     * will still be returned
     * @return white spaces string
     */
    static std::string fillSpaces(const std::string& word);
};


#endif //ENTRY_H
