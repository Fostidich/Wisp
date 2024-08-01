#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "control/entry.hpp"

#include <string>
#include <vector>

#define DEFAULT_FORMAT "b.ab.ab.a.-.c.c.c.c"
#define TOKEN_LEN 48
#define UPDATE_SHIFT_MULTIPLIER 4

const std::string dataFolder = "personal-data/";
const std::string entriesFile = "entries.json";
const std::string configFile = "config.ini";

namespace commands {
std::string generateRandomKey();
bool deleteData();

std::vector<entry> retrieveEntries();
bool dumpEntries(const std::vector<entry> &entries);
/// Comparison is made only for provider and username
bool lookForEntry(const entry &searched);

/// An empty string is returned if a problem arises during file reading
std::string getFormat();
bool setFormat(const std::string &newFormat);
/// An empty string is returned if a problem arises during file reading
std::string getToken();
bool setToken(const std::string &newToken);
std::string generateToken();

bool setEntry(const entry &toSet, bool &present);
bool deleteEntry(const entry &toDelete, bool &present);

void populateEntry(entry &initial);
bool copyToClipboard(const std::string &text);
std::string generateHash(const entry &seed, const std::string &key);
}

/// Returns the path to the folder in which the executable is.
/// The string comprehends the last slash.
/// If an error occurs, the returned string will be empty.
std::string getExecutableDir();
std::string getExecutablePath();
/// Check file presence, otherwise it's created.
/// If file is directly in the executable folder, folder string must be empty.
bool touchFile(const std::string &folder, const std::string &filename);

char randomChar();
bool checkFormatValidity(const std::string &format);
std::vector<unsigned char> getSHA256(const std::string &input);
void shiftRight(std::vector<unsigned char> &v, int times);
std::vector<unsigned char> obtainPlot(const std::string &provider,
    const std::string &username, const std::string &key,
    const std::string &token, int update);
std::vector<std::string> splitFormat(const std::string &format);
char assignChar(
    const std::vector<unsigned char> &plot, const std::string &split);

#endif
