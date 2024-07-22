#include <control/control.hpp>
#include <control/enums.hpp>
#include <ui/ui.hpp>

void control::execute(const request &request) {
    // Retrieve request data
    const auto &flags = request.getFlags();
    auto command = request.getCommand();
    auto error = request.getError();
    const auto &unhandled = request.getUnhandled();

    // Check and manage errors
    if (error != error::none) handlerError(error, unhandled);

    // Switch with the command value in the request to the right command handler
    switch (command) {
        case command::general:
            handlerGeneral(flags);
            break;
        case command::global:
            handlerGlobal(flags);
            break;
        case command::get:
            handlerGet(flags);
            break;
        case command::set:
            handlerSet(flags);
            break;
    }
}

void handlerError(enum error error, const std::string &unhandled) {
    switch (error) {
        case error::noArgument:
            ui::noArgumentError();
            break;
        case error::unknownCommand:
            ui::unknownCommandError(unhandled);
            break;
        case error::unknownFlag:
            ui::unknownFlagError(unhandled);
            break;
        case error::doubleFlag:
            ui::doubleFlagError(unhandled);
            break;
        case error::incompatibleFlags:
            ui::incompatibleFlagsError(unhandled);
            break;
        case error::noValue:
            ui::noValueError(unhandled);
            break;
        case error::noOption:
            ui::noOptionError(unhandled);
            break;
        case error::mandatoryFlag:
            ui::mandatoryFlagError(unhandled);
            break;
    }
    exit(static_cast<int>(error));
}

void handlerGeneral(const std::map<enum flag, std::string> &flags) {
    if (flags.contains(flag::help)) ui::printHelpText();
}

void handlerGlobal(const std::map<enum flag, std::string> &flags) {
    if (flags.contains(flag::token)) ui::printHelpText();
}

void handlerGet(const std::map<enum flag, std::string> &flags) {
    if (flags.contains(flag::provider)) ui::printHelpText();
}

void handlerSet(const std::map<enum flag, std::string> &flags) {
    if (flags.contains(flag::username)) ui::printHelpText();
}