//
// Created by kello on 22/11/23.
//

#ifndef GENERAL_H
#define GENERAL_H

#include <string>


class General {
public:
    static void execute(std::string flag);


private:
    static void printHelp();

    static void printVersion();
};


#endif //GENERAL_H
