#include "commands/commands.hpp"
#include "commands/utils.hpp"
#include "control/control.hpp"
#include "control/enums.hpp"
#include "ui/ui.hpp"

#define VERSION "0.2.0"

void control::execute(const request &request) {
    // Retrieve request data
    const auto &flags = request.getFlags();
    auto command = request.getCommand();
    auto error = request.getError();
    const auto &unhandled = request.getUnhandled();

    // Check and manage errors
    if (error != error::none) handlerError(error, unhandled);

    // Create files if they haven't been already
    if (!checkFilePresence()) return;

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

bool checkFilePresence() {
    if (!touchFile(dataFolder, entriesFile)) {
        ui::fileTouchError(dataFolder + entriesFile);
        return false;
    }
    if (!touchFile(dataFolder, configFile)) {
        ui::fileTouchError(dataFolder + configFile);
        return false;
    }
    return true;
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
        default:
            exit(static_cast<int>(error));
    }
    exit(static_cast<int>(error));
}

void handlerGeneral(const std::map<enum flag, std::string> &flags) {
    switch (flags.begin()->first) {
        case flag::help:
            ui::helpText();
            break;
        case flag::format:
            ui::formatText();
            break;
        case flag::example:
            ui::exampleText();
            break;
        case flag::version:
            ui::versionText(VERSION);
            break;
        case flag::random:
            ui::randomKey(commands::generateRandomKey());
            break;
        case flag::destroy:
            ui::destroyOutcome(ui::askConfirmation() && commands::deleteData());
            break;
        case flag::list:
            ui::showList(commands::retrieveEntries());
            break;
        default:
            exit(static_cast<int>(error::noOption));
    }
}

void handlerGlobal(const std::map<enum flag, std::string> &flags) {
    switch (flags.begin()->first) {
        case flag::format: {
            const std::string &v = flags.at(flag::format);
            if (v.empty())
                ui::showFormat(commands::getFormat());
            else
                ui::newFormat(commands::setFormat(v), v);
            break;
        }
        case flag::token: {
            const std::string &v = flags.at(flag::token);
            if (v.empty())
                ui::showToken(commands::getToken());
            else
                ui::newToken(commands::setToken(v), v);
            break;
        }
        case flag::generate: {
            std::string t = commands::generateToken();
            if (ui::showGeneratedToken(t))
                ui::newToken(commands::setToken(t), t);
            else
                ui::newTokenAbort();
            break;
        }
        default:
            exit(static_cast<int>(error::noOption));
    }
}

void handlerGet(const std::map<enum flag, std::string> &flags) {
    if (flags.contains(flag::provider)) ui::helpText();
}

void handlerSet(const std::map<enum flag, std::string> &flags) {
    if (flags.contains(flag::username)) ui::helpText();
}
