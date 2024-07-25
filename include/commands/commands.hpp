#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "control/entry.hpp"

#include <string>
#include <vector>

namespace commands {
std::string generateRandomKey();
bool deleteData();
std::vector<entry> retrieveEntries();
}

#endif
