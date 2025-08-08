#include "control/control.hpp"
#include "commands/commands.hpp"
#include "control/enums.hpp"
#include "ui/ui.hpp"

#define VERSION "1.0.0"

void control::execute(const request &request) {
    // Retrieve request data
    const auto &flags = request.getFlags();
    auto command = request.getCommand();
    auto error = request.getError();
    const auto &unhandled = request.getUnhandled();

    // Check and manage errors
    if (error != error::none)
        handlerError(error, unhandled);

    // Check format validty
    if (flags.contains(flag::format))
        checkFormat(flags.at(flag::format));

    // Create files if they haven't been already
    checkFilePresence();

    // Check config data validity and presence
    checkConfigs();

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

void checkFormat(const std::string &format) {
    if (commands::checkFormatValidity(format))
        return;
    ui::invalidFormatError();
    exit(static_cast<int>(error::invalidFormat));
}

void checkFilePresence() {
    if (!touchFile(dataFolder, entriesFile)) {
        ui::fileTouchError(dataFolder + entriesFile);
        exit(static_cast<int>(error::untouchableFiles));
    }
    if (!touchFile(dataFolder, configFile)) {
        ui::fileTouchError(dataFolder + configFile);
        exit(static_cast<int>(error::untouchableFiles));
    }
}

void checkConfigs() {
    if (commands::getToken().empty() &&
        !commands::setToken(commands::generateToken())) {
        ui::configsError();
        exit(static_cast<int>(error::invalidConfigs));
    }
    std::string format = commands::getFormat();
    if ((format.empty() || !commands::checkFormatValidity(format)) &&
        !commands::setFormat(DEFAULT_FORMAT)) {
        ui::configsError();
        exit(static_cast<int>(error::invalidConfigs));
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
    entry e(flags);
    commands::populateEntry(e);
    std::string hash = commands::generateHash(e, ui::inputKey());

    if (flags.contains(flag::clipboard))
        if (commands::copyToClipboard(hash))
            ui::hashCopiedToClipboard();
        else
            ui::hashNotCopiedToClipboard();
    else
        ui::hashGeneration(hash);

    if (!commands::lookForEntry(e)) {
        bool present;
        if (ui::askForAddition())
            if (commands::setEntry(entry(flags), present) && !present)
                ui::entryCreated();
            else
                ui::entryNotCreated();
        else
            ui::entryNotAdded();
    }
}

void handlerSet(const std::map<enum flag, std::string> &flags) {
    entry e(flags);
    bool present;
    if (flags.contains(flag::remove)) {
        if (commands::deleteEntry(e, present))
            ui::entryDeleted();
        else
            present ? ui::entryNotDeleted() : ui::entryNotFound();
    } else {
        if (commands::setEntry(e, present))
            present ? ui::entryUpdated() : ui::entryCreated();
        else
            ui::entryNotUpdated();
    }
}
