#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "control/enums.hpp"

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

    bool checkArgumentsIntegrity(int start, std::string& lastFlag,
        const std::vector<std::string>& args, const std::vector<std::string>& vLong,
        const std::vector<std::string>& vShort);
    bool checkAtLeastOneFlag(int start, const std::vector<std::string>& args);
    bool checkInternalUnknownCommand(int start, const std::vector<std::string>& args);
    bool checkFlagRecognition(std::string& lastFlag, const std::vector<std::string>& args,
        const std::vector<std::string>& vLong, const std::vector<std::string>& vShort);
    bool findFlagValue(enum flag flag, const std::string& v1, const std::string& v2, bool hasValue,
        const std::vector<std::string>& args);

    void builderGeneral(const std::vector<std::string>& args);
    void builderGlobal(const std::vector<std::string>& args);
    void builderGet(const std::vector<std::string>& args);
    void builderSet(const std::vector<std::string>& args);
};

#endif
