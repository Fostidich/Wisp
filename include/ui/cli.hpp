#ifndef CLI_HPP
#define CLI_HPP

#include <string>

class cli {
public:
    void makeRequest(int argc, char *argv[]);
    void printHelpText(std::string text);
};

#endif