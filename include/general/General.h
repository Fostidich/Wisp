//
// Created by kello on 22/11/23.
//

#ifndef GENERAL_H
#define GENERAL_H
#include <string>


class General {
public:
    General(int argc, char* argv[]);
private:
    void printHelp();
    void printVersion();
};


#endif //GENERAL_H
