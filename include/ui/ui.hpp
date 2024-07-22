#ifndef UI_HPP
#define UI_HPP

#include <string>

namespace ui {
void noArgumentError();
void unknownCommandError(const std::string& text);
void unknownFlagError(const std::string& text);
void doubleFlagError(const std::string& text);
void incompatibleFlagsError(const std::string& text);
void noValueError(const std::string& text);
void noOptionError(const std::string& text);
void mandatoryFlagError(const std::string& text);
void printHelpText();
}

#endif