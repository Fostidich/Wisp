#include <control/request.hpp>
#include <vector>

request::request(const std::vector<std::string> &args) : flags() {
    // TODO pack "..." args into a single one

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

const std::map<enum flag, std::string> &request::getFlags() const {
    return flags;
}

enum command request::getCommand() const { return command; }

enum error request::getError() const { return error; }

const std::string &request::getUnhandled() const { return unhandled; }

bool request::checkArgumentsIntegrity(int start, std::string &lastFlag,
                                      const std::vector<std::string> &args,
                                      const std::vector<std::string> &vLong,
                                      const std::vector<std::string> &vShort) {
    if (!checkAtLeastOneFlag(start, args)) return false;
    if (!checkInternalUnknownCommand(start, args)) return false;
    if (!checkFlagRecognition(lastFlag, args, vLong, vShort)) return false;
    return true;
}

bool request::checkAtLeastOneFlag(int start,
                                  const std::vector<std::string> &args) {
    // Check the presence of at least one flag
    if (args.size() == start) {
        error = error::noOption;
        unhandled = args[1];
        return false;
    }
    return true;
}

bool request::checkInternalUnknownCommand(
    int start, const std::vector<std::string> &args) {
    // Check that between two values there is always a flag
    for (int temp = start - 1, i = start; i < args.size(); i++) {
        if (args[i][0] != '-') {
            if (i == temp + 1) {
                error = error::unknownCommand;
                unhandled = args[i];
                return false;
            }
            temp = i;
        }
    }
    return true;
}

bool request::checkFlagRecognition(std::string &lastFlag,
                                   const std::vector<std::string> &args,
                                   const std::vector<std::string> &vLong,
                                   const std::vector<std::string> &vShort) {
    // Check that all flags are recognised
    for (const auto &arg : args) {
        if (arg[0] == '-') {
            bool found = false;

            // Check if there is a match
            for (const auto &l : vLong)
                if (arg.compare(l) == 0) {
                    lastFlag = arg;
                    found = true;
                    break;
                }
            for (const auto &s : vShort)
                if (arg.compare(s) == 0) {
                    lastFlag = arg;
                    found = true;
                    break;
                }

            // Invoke an unknown flag error in case of no match
            if (!found) {
                error = error::unknownFlag;
                unhandled = arg;
                return false;
            }
            continue;
        }
    }
    return true;
}

bool request::findFlagValue(enum flag flag, const std::string &v1,
                            const std::string &v2, bool hasValue,
                            const std::vector<std::string> &args) {
    bool found = false;
    for (int i = 1; i < args.size(); i++) {
        if (args[i].compare(v2) == 0 || args[i].compare(v1) == 0) {
            // Check for repetitions
            if (found) {
                error = error::doubleFlag;
                unhandled = v1 + '/' + v2;
                return false;
            }

            // Check if flag actually has a value
            if (hasValue && (i == args.size() - 1 || args[i + 1][0] == '-')) {
                error = error::noValue;
                unhandled = args[i];
                return false;
            }

            // Check if flag actually hasn't a value
            if (!hasValue && (i != args.size() - 1 && args[i + 1][0] != '-')) {
                error = error::unknownCommand;
                unhandled = args[i + 1];
                return false;
            }

            // If value presence check is passed, put the value into flags map
            if (hasValue)
                flags[flag] = args[i + 1];
            else
                flags[flag];
            found = true;
        }
    }
    return true;
}

void request::builderGeneral(const std::vector<std::string> &args) {
    command = command::general;

    const std::vector<std::string> vLong = {
        "--help",   "--format",  "--example", "--version",
        "--random", "--destroy", "--list"};
    const std::vector<std::string> vShort = {"-h", "-f", "-e", "-v",
                                             "-r", "-d", "-l"};
    const std::vector<enum flag> vFlag = {
        flag::help,   flag::format,  flag::example, flag::version,
        flag::random, flag::destroy, flag::list};

    std::string lastFlag;
    if (!checkArgumentsIntegrity(1, lastFlag, args, vLong, vShort)) return;

    // Populate flags map
    for (int i = 0; i < vFlag.size(); i++)
        if (!findFlagValue(vFlag[i], vLong[i], vShort[i], false, args)) return;

    // No two flags can ever be used together
    if (flags.size() > 1) {
        error = error::incompatibleFlags;
        unhandled = lastFlag;
    }
}

void request::builderGlobal(const std::vector<std::string> &args) {
    command = command::global;

    const std::vector<std::string> vLong = {"--format", "--token",
                                            "--generate"};
    const std::vector<std::string> vShort = {"-f", "-t", "-g"};
    const std::vector<enum flag> vFlag = {flag::format, flag::token,
                                          flag::generate};

    std::string lastFlag;
    if (!checkArgumentsIntegrity(2, lastFlag, args, vLong, vShort)) return;

    // TODO add an empty string after global token or format
    auto args2 = args;
    for (int i = 0; i < args2.size(); i++) {
        if ((args2.size() == i + 1 || args2[i + 1][0] == '-') &&
            (args2[i].compare(vShort[0]) == 0 ||
             args2[i].compare(vShort[1]) == 0 ||
             args2[i].compare(vLong[0]) == 0 || args2[i].compare(vLong[1]) == 0))
             args2.insert(args2.begin() + i + 1, "");
             i++;
    }

    // Populate flags map
    int i;
    for (i = 0; i < vFlag.size() - 1; i++)
        if (!findFlagValue(vFlag[i], vLong[i], vShort[i], true, args2)) return;
    if (!findFlagValue(vFlag[i], vLong[i], vShort[i], false, args2)) return;

    // No two flags can ever be used together
    if (flags.size() > 1) {
        error = error::incompatibleFlags;
        unhandled = lastFlag;
    }
}

void request::builderGet(const std::vector<std::string> &args) {
    command = command::get;

    const std::vector<std::string> vLong = {
        "--provider", "--username", "--format", "--update", "--clipboard"};
    const std::vector<std::string> vShort = {"-p", "-u", "-f", "-n", "-c"};
    const std::vector<enum flag> vFlag = {flag::provider, flag::username,
                                          flag::format, flag::update,
                                          flag::clipboard};

    std::string lastFlag;
    if (!checkArgumentsIntegrity(2, lastFlag, args, vLong, vShort)) return;

    // Populate flags map
    int i;
    for (i = 0; i < vFlag.size() - 1; i++)
        if (!findFlagValue(vFlag[i], vLong[i], vShort[i], true, args)) return;
    if (!findFlagValue(vFlag[i], vLong[i], vShort[i], false, args)) return;

    // Check that provider and username are given
    if (!flags.contains(flag::provider)) {
        error = error::mandatoryFlag;
        unhandled = vLong[0] + '/' + vShort[0];
        return;
    }
    if (!flags.contains(flag::username)) {
        error = error::mandatoryFlag;
        unhandled = vLong[1] + '/' + vShort[1];
        return;
    }
}

void request::builderSet(const std::vector<std::string> &args) {
    command = command::set;

    const std::vector<std::string> vLong = {"--provider",   "--username",
                                            "--format",     "--update",
                                            "--annotation", "--remove"};
    const std::vector<std::string> vShort = {"-p", "-u", "-f",
                                             "-n", "-a", "-r"};
    const std::vector<enum flag> vFlag = {flag::provider,   flag::username,
                                          flag::format,     flag::update,
                                          flag::annotation, flag::remove};

    std::string lastFlag;
    if (!checkArgumentsIntegrity(2, lastFlag, args, vLong, vShort)) return;

    // Populate flags map
    int i;
    for (i = 0; i < vFlag.size() - 1; i++)
        if (!findFlagValue(vFlag[i], vLong[i], vShort[i], true, args)) return;
    if (!findFlagValue(vFlag[i], vLong[i], vShort[i], false, args)) return;

    // Check that provider and username are given
    if (!flags.contains(flag::provider)) {
        error = error::mandatoryFlag;
        unhandled = vLong[0] + '/' + vShort[0];
        return;
    }
    if (!flags.contains(flag::username)) {
        error = error::mandatoryFlag;
        unhandled = vLong[1] + '/' + vShort[1];
        return;
    }

    // A minimum of three flags is required
    if (flags.size() < 3) {
        error = error::noOption;
        unhandled = args[1];
        return;
    }

    // Remove flag do not want other flags
    if (flags.contains(flag::remove) && flags.size() != 3) {
        error = error::incompatibleFlags;
        unhandled = vLong[5] + '/' + vShort[5];
        return;
    }
}