#include "commands/commands.hpp"

#include <exception>
#include <filesystem>

std::string commands::generateRandomKey() {
    std::string s;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            s += randomChar();
        }
        if (i != 2) s += '-';
    }
    return s;
}

bool commands::deleteData() {
    std::string path = getExecutableDir();
    if (path.empty()) return false;
    path += dataFolder;
    try {
        if (std::filesystem::exists(path))
            std::filesystem::remove_all(path);
        else
            return false;
    } catch (const std::exception &_) {
        return false;
    }
    return true;
}
