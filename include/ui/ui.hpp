#ifndef UI_HPP
#define UI_HPP

#include "control/entry.hpp"

#include <string>
#include <vector>

namespace ui {
void fileTouchError(const std::string& filename);
void configsError();
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
void showList(const std::vector<entry>& entries);

void showFormat(const std::string& format);
void newFormat(bool outcome, const std::string& newFormat);
void showToken(const std::string& token);
void newToken(bool outcome, const std::string& newToken);
bool showGeneratedToken(const std::string& token);
void newTokenAbort();

void entryUpdated();
void entryCreated();
void entryNotCreated();
void entryNotAdded();
void entryNotUpdated();
void entryDeleted();
void entryNotDeleted();
void entryNotFound();

bool askForAddition();
std::string inputKey();

void hashGeneration(const std::string& hash);
void hashCopiedToClipboard();
void hashNotCopiedToClipboard();
}

char getHiddenChar();

#endif
