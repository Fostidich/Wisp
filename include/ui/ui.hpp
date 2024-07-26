#ifndef UI_HPP
#define UI_HPP

#include "control/entry.hpp"

#include <string>
#include <vector>

namespace ui {
void noArgumentError();
void unknownCommandError(const std::string& text);
void unknownFlagError(const std::string& text);
void doubleFlagError(const std::string& text);
void incompatibleFlagsError(const std::string& text);
void noValueError(const std::string& text);
void noOptionError(const std::string& text);
void mandatoryFlagError(const std::string& text);

void helpText();
void formatText();
void exampleText();
void versionText(const std::string& text);
void randomKey(const std::string& text);
bool askConfirmation(const std::string& text);
void destroyOutcome(bool outcome);
void showList(const std::vector<entry> &entries);

void showFormat(std::string format);
void newFormat(bool outcome, std::string newFormat);
void showToken(std::string token);
void newToken(bool outcome, std::string newToken);
bool showGeneratedToken(std::string token);
}

#endif
