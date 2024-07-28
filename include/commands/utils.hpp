#ifndef UTILS_CPP
#define UTILS_CPP

#include <string>

char randomChar();
char getHiddenChar();

/// Returns the path to the folder in which the executable is.
/// The string comprehends the last slash.
/// If an error occurs, the returned string will be empty.
std::string getExecutableDir();
std::string getExecutablePath();
/// Check file presence, otherwise it's created.'
/// If file is directly in the executable folder, folder string must be empty.
bool touchFile(std::string folder, std::string filename);

#endif
