#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <control/enums.hpp>
#include <map>
#include <string>
#include <vector>

class request {
public:
    request(const std::vector<std::string>& args);
    const std::map<enum flag, std::string>& getFlags() const;
    enum command getCommand() const;
    const std::string& getUnhandled() const;
private:
    std::map<enum flag, std::string> flags;
    enum command command;
    std::string unhandled;

    void builderGeneral(const std::vector<std::string>& args);
};

#endif