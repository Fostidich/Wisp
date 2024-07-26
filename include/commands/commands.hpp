#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "control/entry.hpp"

#include <string>
#include <vector>

namespace commands {
std::string generateRandomKey();
bool deleteData();
std::vector<entry> retrieveEntries();

/// An empty string is returned if a problem arises during file reading
std::string getFormat();
bool setFormat(std::string newFormat);
/// An empty string is returned if a problem arises during file reading
std::string getToken();
bool setToken(std::string newToken);
std::string generateToken();
}

#endif
