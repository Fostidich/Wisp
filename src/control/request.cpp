#include <control/request.hpp>

request::request(const std::vector<std::string>& args) : flags() {

    // Switch in request the provided command (first argument), with its enum value.
    // If no command is found, use the "none" value.
    // If the first argument starts with a "-", put "general" as command.
    if (args.size() <= 1) {
        command = command::noArgument;
        return;
    }
    if (args[1].starts_with('-')) {
        command = command::general;
        builderGeneral(args);
    }
    else if (args[1].compare("global") == 0)
        command = command::global;
    else if (args[1].compare("get") == 0)
        command = command::get;
    else if (args[1].compare("set") == 0)
        command = command::set;
    else {
        command = command::unknownCommand;
        unhandled = args[1];
        return;
    }
}

const std::map<enum flag, std::string>& request::getFlags() const {
    return flags;
}

enum command request::getCommand() const {
    return command;
}

const std::string& request::getUnhandled() const {
    return unhandled;
}

void request::builderGeneral(const std::vector<std::string>& args) {
    if (args[1].compare("--help") == 0 || args[1].compare("-h") == 0)
        flags[flag::help];
    else {
        flags[flag::unknownFlag];
        unhandled = args[1];
    }
}