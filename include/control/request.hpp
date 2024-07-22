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
    enum error getError() const;
    const std::string& getUnhandled() const;

  private:
    std::map<enum flag, std::string> flags;
    enum command command;
    enum error error { error::none };
    std::string unhandled;

    bool checkInternalUnknownCommand(int start, const std::vector<std::string>& args);
    void builderGeneral(const std::vector<std::string>& args);
    void builderGlobal(const std::vector<std::string>& args);
    void builderGet(const std::vector<std::string>& args);
    void builderSet(const std::vector<std::string>& args);
};

#endif