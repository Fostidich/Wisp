#ifndef WORD_HPP
#define WORD_HPP

#include <iostream>

class Word {
    public:
        Word(std::string input);
        std::string getValue();
        int encode();

    private:
        std::string value;
};

#endif