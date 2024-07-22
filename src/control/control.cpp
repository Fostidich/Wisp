#include <control/control.hpp>
#include <control/enums.hpp>
#include <ui/ui.hpp>

static void handlerError(enum error error, const std::string &unhandled);
static void handlerGeneral(const std::map<enum flag, std::string> &flags);

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
            break;
        case command::get:
            break;
        case command::set:
            break;
    }
}

static void handlerError(enum error error, const std::string &unhandled) {
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
        case error::noValue:
            ui::noValueError(unhandled);
            break;
        case error::noOption:
            ui::noOptionError(unhandled);
            break;
    }
    exit(static_cast<int>(error));
}

static void handlerGeneral(const std::map<enum flag, std::string> &flags) {
    if (flags.contains(flag::help)) ui::printHelpText();
}