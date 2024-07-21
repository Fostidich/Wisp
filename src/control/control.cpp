#include <control/control.hpp>
#include <control/enums.hpp>
#include <ui/ui.hpp>

static void handlerGeneral(const std::map<enum flag, std::string> &flags);

void control::execute(const request &request) {
    enum command command = request.getCommand();
    const auto &flags = request.getFlags();

    // Unknown flag check
    if (flags.contains(flag::unknownFlag)) {
        ui::unknownFlagError(request.getUnhandled());
        exit(1);
    }

    // Switch with the command value in the request to the right command handler
    switch (command) {
    case command::noArgument:
        ui::noArgumentError();
        exit(1);
    case command::general:
        handlerGeneral(flags);
        break;
    case command::global:
        break;
    case command::get:
        break;
    case command::set:
        break;
    case command::unknownCommand:
        ui::unknownCommandError(request.getUnhandled());
        exit(1);
    }
}

static void handlerGeneral(const std::map<enum flag, std::string> &flags) {
    if (flags.contains(flag::help))
        ui::printHelpText();
}