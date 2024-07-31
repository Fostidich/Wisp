#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "control/entry.hpp"

#include <string>
#include <vector>

const std::string dataFolder = "personal-data/";
const std::string entriesFile = "entries.json";
const std::string configFile = "config.ini";

namespace commands {
std::string generateRandomKey();
bool deleteData();

std::vector<entry> retrieveEntries();
bool dumpEntries(const std::vector<entry> &entries);

/// An empty string is returned if a problem arises during file reading
std::string getFormat();
bool setFormat(std::string newFormat);
/// An empty string is returned if a problem arises during file reading
std::string getToken();
bool setToken(std::string newToken);
std::string generateToken();

bool setEntry(const entry &toSet);
bool deleteEntry(const entry &toDelete);
}

#endif
