#include "commands/commands.hpp"
#include "commands/utils.hpp"

#include <exception>
#include <mINI/ini.h>

#define TOKEN_LEN 48
#define DEFAULT_FORMAT "b.ab.ab.a.-.c.c.c.c"

std::string commands::getFormat() {
    try {
        std::string path = getExecutableDir();
        if (path.empty()) return "";
        path += dataFolder + configFile;

        mINI::INIFile file(path);
        mINI::INIStructure ini;
        if (!file.read(ini)) return "";
        if (ini["globals"]["format"].empty()) return "";
        return ini["globals"]["format"];
    } catch (const std::exception &_) {
        return "";
    }
}

bool commands::setFormat(std::string newFormat) {
    try {
        std::string path = getExecutableDir();
        if (path.empty()) return false;
        path += dataFolder + configFile;

        mINI::INIFile file(path);
        mINI::INIStructure ini;
        if (!file.read(ini)) return false;
        ini["globals"]["format"] = newFormat;
        return file.write(ini);
    } catch (const std::exception &_) {
        return false;
    }
}

std::string commands::getToken() {
    try {
        std::string path = getExecutableDir();
        if (path.empty()) return "";
        path += dataFolder + configFile;

        mINI::INIFile file(path);
        mINI::INIStructure ini;
        if (!file.read(ini)) return "";
        if (ini["globals"]["token"].empty()) return "";
        return ini["globals"]["token"];
    } catch (const std::exception &_) {
        return "";
    }
}

bool commands::setToken(std::string newToken) {
    try {
        std::string path = getExecutableDir();
        if (path.empty()) return false;
        path += dataFolder + configFile;

        mINI::INIFile file(path);
        mINI::INIStructure ini;
        if (!file.read(ini)) return false;
        ini["globals"]["token"] = newToken;
        return file.write(ini);
    } catch (const std::exception &_) {
        return false;
    }
}

std::string commands::generateToken() {
    std::string newToken;
    for (int i = 0; i < TOKEN_LEN; i++) newToken += randomChar();
    return newToken;
}
