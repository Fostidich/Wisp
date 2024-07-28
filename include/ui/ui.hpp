#ifndef UI_HPP
#define UI_HPP

#include "control/entry.hpp"

#include <string>
#include <vector>

namespace ui {
void fileTouchError(const std::string &filename);
void noArgumentError();
void unknownCommandError(const std::string& command);
void unknownFlagError(const std::string& flag);
void doubleFlagError(const std::string& flag);
void incompatibleFlagsError(const std::string& flag);
void noValueError(const std::string& flag);
void noOptionError(const std::string& command);
void mandatoryFlagError(const std::string& flag);

void helpText();
void formatText();
void exampleText();
void versionText(const std::string& version);
void randomKey(const std::string& key);
bool askConfirmation();
void destroyOutcome(bool outcome);
void showList(const std::vector<entry> &entries);

void showFormat(std::string format);
void newFormat(bool outcome, std::string newFormat);
void showToken(std::string token);
void newToken(bool outcome, std::string newToken);
bool showGeneratedToken(std::string token);
void newTokenAbort();
}

#endif
