#include "commands/commands.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <random>
#include <string>

#ifdef __APPLE__
#include <mach-o/dyld.h>
#include <limits.h>

std::string getExecutablePath() {
    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0) {
        return buffer;
    }
    return "";
}

#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>

std::string getExecutablePath() {
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        return buffer;
    }
    return "";
}

#else
#error "Unsupported OS"
#endif

std::string getExecutableDir() {
    std::string executablePath = getExecutablePath();
    size_t lastSlash = executablePath.find_last_of('/');
    std::string executableDir = (lastSlash != std::string::npos)
                                    ? executablePath.substr(0, lastSlash + 1)
                                    : "";
    return executableDir;
}

bool touchFile(const std::string &folder, const std::string &filename) {
    std::string path = getExecutableDir();
    if (path.empty()) return false;

    path += folder;
    if (!std::filesystem::exists(path) &&
        !std::filesystem::create_directories(path))
        return false;

    path += filename;
    if (!std::filesystem::exists(path)) {
        std::ofstream file(path);
        if (!file.is_open()) return false;
    }

    return true;
}

char randomChar() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 61);
    int rand = dis(gen);

    /*
     * 23 pound
     * 45 hyphen
     * 48-57 digits
     * 65-90 uppercase letters
     * 97-122 lowercase letters
     */
    if (rand < 10) return char('0' + rand);
    if (rand < 36)
        return char('A' + rand - 10);
    else
        return char('a' + rand - 36);
}

bool commands::checkFormatValidity(const std::string &format) {
    const std::vector<char> validChars = {'a', 'b', 'c', 'd', '.', '-'};
    if (format.back() == '.') return false;
    char temp = '.';
    for (int i = 0; i < format.size(); i++) {
        // Check char validity
        if (std::find(validChars.begin(), validChars.end(), format[i]) ==
            validChars.end())
            return false;

        // Check that no double dot can be found
        if (format[i] == '.' && temp == '.') return false;

        // Check that hyphen is always alone
        if (format[i] == '-' &&
            (temp != '.' || (i + 1 < format.size() && format[i + 1] != '.')))
            return false;

        temp = format[i];
    }
    return true;
}

std::vector<entry> commands::retrieveEntries() {
    std::vector<entry> entries;
    try {
        std::string path = getExecutableDir();
        if (path.empty()) return entries;
        path += dataFolder + entriesFile;

        std::ifstream file(path);
        if (!file.is_open()) return entries;
        nlohmann::json jsonData;
        file >> jsonData;
        if (file.fail() || !jsonData.is_array()) return entries;
        file.close();

        for (const auto &j : jsonData) {
            // Discard invalid entries
            if (!j.contains("provider") || !j.contains("username") ||
                !j["provider"].is_string() || !j["username"].is_string())
                continue;

            // Add new entry to the vector
            entry e(j);
            entries.push_back(e);
        }
    } catch (const std::exception &_) {}
    return entries;
}

bool commands::dumpEntries(const std::vector<entry> &entries) {
    try {
        std::string path = getExecutableDir();
        if (path.empty()) return false;
        path += dataFolder + entriesFile;

        std::ofstream file(path);
        if (!file.is_open()) return false;
        nlohmann::json jsonData;
        for (const auto &e : entries) jsonData.push_back(e.toJson());

        file << std::setw(4) << jsonData << std::endl;
        if (file.fail()) return false;
        file.close();

        return true;
    } catch (const std::exception &_) { return false; }
}

bool commands::lookForEntry(const entry &searched) {
    auto entries = commands::retrieveEntries();

    return std::find_if(
               entries.begin(), entries.end(), [&searched](const entry &e) {
                   return e.getProvider() == searched.getProvider() &&
                          e.getUsername() == searched.getUsername();
               }) != entries.end();
}
