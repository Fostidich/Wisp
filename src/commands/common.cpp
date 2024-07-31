#include "commands/commands.hpp"
#include "commands/utils.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

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
