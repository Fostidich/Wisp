#include "commands/commands.hpp"
#include "commands/utils.hpp"

#include <exception>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

const std::string dataFolder = "personal-data/";

const std::string entriesFile = "entries.json";

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
    } catch (const std::exception &_) {
    }
    return entries;
}
