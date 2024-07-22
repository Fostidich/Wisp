#include <control/request.hpp>

request::request(const std::vector<std::string> &args) : flags() {
    // Switch with the provided command to the right request builder
    if (args.size() <= 1)
        error = error::noArgument;
    else if (args[1].starts_with('-'))
        builderGeneral(args);
    else if (args[1].compare("global") == 0)
        builderGlobal(args);
    else if (args[1].compare("get") == 0)
        builderGet(args);
    else if (args[1].compare("set") == 0)
        builderSet(args);
    else {
        error = error::unknownCommand;
        unhandled = args[1];
    }
}

const std::map<enum flag, std::string> &request::getFlags() const { return flags; }

enum command request::getCommand() const { return command; }

enum error request::getError() const { return error; }

const std::string &request::getUnhandled() const { return unhandled; }

bool request::checkInternalUnknownCommand(int start, const std::vector<std::string> &args) {
    // Check the presence of at least one flag
    if (args.size() == start) {
        error = error::noOption;
        unhandled = args[1];
        return false;
    }

    // Check that between two values there is always a flag
    for (int temp = start - 1, i = start; i < args.size(); i++) {
        if (args[i][0] != '-') {
            if (i == temp + 1) {
                unhandled = args[i];
                error = error::unknownCommand;
                return false;
            }
            temp = i;
        }
    }
    return true;
}

void request::builderGeneral(const std::vector<std::string> &args) {
    command = command::general;
    if (!checkInternalUnknownCommand(1, args)) return;

    if (args[1].compare("--help") == 0 || args[1].compare("-h") == 0)
        flags[flag::help];
    else {
        error = error::unknownFlag;
        unhandled = args[1];
    }
}

void request::builderGlobal(const std::vector<std::string> &args) {
    command = command::global;
    if (!checkInternalUnknownCommand(2, args)) return;

    if (args[2].compare("--token") == 0 || args[2].compare("-t") == 0)
        flags[flag::token];
    else {
        error = error::unknownFlag;
        unhandled = args[2];
    }
}

void request::builderGet(const std::vector<std::string> &args) {
    command = command::get;
    if (!checkInternalUnknownCommand(2, args)) return;

    if (args[2].compare("--provider") == 0 || args[2].compare("-p") == 0)
        flags[flag::provider];
    else {
        error = error::unknownFlag;
        unhandled = args[2];
    }
}

void request::builderSet(const std::vector<std::string> &args) {
    command = command::set;
    if (!checkInternalUnknownCommand(2, args)) return;

    if (args[2].compare("--username") == 0 || args[2].compare("-u") == 0)
        flags[flag::username];
    else {
        error = error::unknownFlag;
        unhandled = args[2];
    }
}