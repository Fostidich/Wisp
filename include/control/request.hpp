#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <string>

class request {
public:
    std::map<std::string, std::string> getFlags();
    std::string getCommand();
private:
    std::map<std::string, std::string> flags;
    std::string command;
};

#endif