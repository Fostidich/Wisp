#include "ui/ui.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <termios.h>
#include <unistd.h>

const std::string suggestHelp = "Use \"wisp --help\" for a list of commands.";
const std::string suggestFormat = "Use \"wisp --format\" for format rules.";

const std::vector<std::string> yes = {"", "y", "Y", "yes", "YES", "Yes"};
const std::vector<std::string> no = {"n", "N", "no", "NO", "No"};

void ui::invalidFormatError() {
    std::cerr << "Invalid format. " << suggestFormat << std::endl;
}

void ui::fileTouchError(const std::string &filename) {
    std::cerr << "Unable to touch \"" << filename << "\"." << std::endl;
}

void ui::configsError() {
    std::cerr << "Unable to access the config file" << std::endl;
}

void ui::noArgumentError() {
    std::cerr << "No argument provided. " << suggestHelp << std::endl;
}

void ui::unknownCommandError(const std::string &command) {
    std::cerr << "Unknown command: \"" << command << "\". " << suggestHelp
              << std::endl;
}

void ui::unknownFlagError(const std::string &flag) {
    std::cerr << "Unknown flag: \"" << flag << "\". " << suggestHelp
              << std::endl;
}

void ui::doubleFlagError(const std::string &flag) {
    std::cerr << "Flag \"" << flag << "\" cannot be repeated. " << suggestHelp
              << std::endl;
}

void ui::incompatibleFlagsError(const std::string &flag) {
    std::cerr << "Flag \"" << flag << "\" cannot be used with priors. "
              << suggestHelp << std::endl;
}

void ui::noValueError(const std::string &flag) {
    std::cerr << "Flag \"" << flag << "\" requires a value. " << suggestHelp
              << std::endl;
}

void ui::noOptionError(const std::string &command) {
    std::cerr << "Command \"" << command << "\" requires option flags. "
              << suggestHelp << std::endl;
}

void ui::mandatoryFlagError(const std::string &flag) {
    std::cerr << "Flag \"" << flag << "\" is mandatory. " << suggestHelp
              << std::endl;
}

void ui::helpText() {
    std::cout << R"(
    wisp - General actions:
        -h, --help                      Show help panel
        -f, --format                    Show format details
        -v, --version                   Print version
        -r, --random                    Print a random key
        -d, --destroy                   Immediately destroy all saved information
        -l, --list                      Access stored data

    wisp global - Global settings:
        -f, --format <(format)>         Set or show global hash format
        -t, --token <(token)>           Set or show the private token
        -g, --generate                  Generate a new private token

    wisp get - Generate hash:
        -p, --provider <*provider*>     Generate hash with the specified provider
        -u, --username <*username*>     Generate hash with the specified username
        -f, --format <format>           Use a custom format for generation
        -n, --update <update number>    Use a custom update number for generation
        -c, --clipboard                 Save the hash to clipboard without printing it

    wisp set - Add custom settings:
        -p, --provider <*provider*>     Add settings for the entry with this provider
        -u, --username <*username*>     Add settings for the entry with this username
        -f, --format <format>           Set format for the selected entry
        -n, --update <update number>    Set update number for the selected entry
        -a, --annotation <"note">       Set a note for the selected entry
        -r, --remove                    Remove the entry from the list
    )" << std::endl;
}

void ui::formatText() {
    std::cout << R"(
        Symbols:
          .  - Section Separator
          -  - Literal Hyphen
          a  - Lowercase Letter (a-z)
          b  - Uppercase Letter (A-Z)
          c  - One-Digit Number (0-9)
          d  - Special Character (e.g., !@#$%^&*)

        Rules:
          - Sections are separated by dots ('.').
          - A hyphen ('-') must be alone within a section and surrounded by dots.
          - Sections cannot be empty or contain invalid characters.
          - Format cannot start or end with a dot or contain consecutive dots.

        Examples:
          1. a.a.b.b.c.c.d.d
          2. ab.ab.ab.ab.-.c.c.c.c
          3. abcd.abcd.abcd.abcd
    )" << std::endl;
}

void ui::versionText(const std::string &version) {
    std::cout << "Wisp version: " << version << std::endl;
}

void ui::randomKey(const std::string &key) {
    std::cout << key << std::endl;
}

bool ui::askConfirmation() {
    std::cout << "Do you really want to delete all personal data?" << std::endl;
    std::cout << "Write \"CONFIRM\" to proceed: ";
    std::string confirm;
    getline(std::cin, confirm);
    return confirm.compare("CONFIRM") == 0;
}

void ui::destroyOutcome(bool outcome) {
    if (outcome)
        std::cout << "All data successfully deleted." << std::endl;
    else
        std::cerr << "Unable to delete data." << std::endl;
}

void ui::showList(const std::vector<entry> &entries) {
    if (entries.empty()) {
        std::cout << "No data to show." << std::endl;
        return;
    }

    int providerMaxLen = 1, usernameMaxLen = 1, updateMaxLen = 1;
    for (const auto &e : entries) {
        int p = e.getProvider().size();
        int u = e.getUsername().size();
        int n = std::log10(e.getUpdate()) + 1;
        if (p > providerMaxLen) providerMaxLen = p;
        if (u > usernameMaxLen) usernameMaxLen = u;
        if (n > updateMaxLen) updateMaxLen = n;
    }
    for (const auto &e : entries)
        std::cout << e.toString(providerMaxLen, usernameMaxLen, updateMaxLen)
                  << std::endl;
}

void ui::showFormat(const std::string &format) {
    std::cout << "Global hash format: " << format << std::endl;
}

void ui::newFormat(bool outcome, const std::string &newFormat) {
    if (outcome)
        std::cout << "New global hash format set: " << newFormat << std::endl;
    else
        std::cerr << "Unable to set new global hash format." << std::endl;
}

void ui::showToken(const std::string &token) {
    std::cout << "Global private token: " << token << std::endl;
}

void ui::newToken(bool outcome, const std::string &newToken) {
    if (outcome)
        std::cout << "New global private token set: " << newToken << std::endl;
    else
        std::cerr << "Unable to set new global private token." << std::endl;
}

bool ui::showGeneratedToken(const std::string &token) {
    std::cout << "Generated token: " << token << std::endl;
    std::string choice;
    const std::string question =
        "Would you like to set it as global private token? [y] / n ";
    std::cout << question;
    getline(std::cin, choice);

    while (std::find(yes.begin(), yes.end(), choice) == yes.end() &&
           std::find(no.begin(), no.end(), choice) == no.end()) {
        std::cout << "Unknown answer." << std::endl;
        std::cout << question;
        getline(std::cin, choice);
    }

    return std::find(yes.begin(), yes.end(), choice) != yes.end();
}

void ui::newTokenAbort() {
    std::cout << "New token not set." << std::endl;
}

void ui::entryUpdated() {
    std::cout << "Entry has been updated." << std::endl;
}

void ui::entryCreated() {
    std::cout << "New entry created." << std::endl;
}

void ui::entryNotCreated() {
    std::cerr << "Unable to create new entry." << std::endl;
}

void ui::entryNotAdded() {
    std::cout << "Entry not added." << std::endl;
}

void ui::entryNotUpdated() {
    std::cerr << "Unable to update entry." << std::endl;
}

void ui::entryDeleted() {
    std::cout << "Entry has been deleted." << std::endl;
}

void ui::entryNotDeleted() {
    std::cerr << "Unable to delete entry." << std::endl;
}

void ui::entryNotFound() {
    std::cout << "Entry not found." << std::endl;
}

bool ui::askForAddition() {
    std::string choice;
    const std::string question =
        "Do you want to save this as a new entry? [y] / n ";
    std::cout << question;
    getline(std::cin, choice);

    while (std::find(yes.begin(), yes.end(), choice) == yes.end() &&
           std::find(no.begin(), no.end(), choice) == no.end()) {
        std::cout << "Unknown answer." << std::endl;
        std::cout << question;
        getline(std::cin, choice);
    }

    return std::find(yes.begin(), yes.end(), choice) != yes.end();
}

std::string ui::inputKey() {
    std::string key;
    while (true) {
        std::cout << "Enter personal key: ";
        char ch;
        while ((ch = getHiddenChar()) != '\n') {
            key += ch;
            std::cout << "";
        }
        std::cout << std::endl;
        if (key.empty())
            std::cout << "No key inserted, try again" << std::endl;
        else
            break;
    }
    return key;
}

void ui::hashGeneration(const std::string &hash) {
    std::cout << hash << std::endl;
}

void ui::hashCopiedToClipboard() {
    std::cout << "Copied to clipboard." << std::endl;
}

void ui::hashNotCopiedToClipboard() {
    std::cerr << "Unable to copy to clipboard." << std::endl;
    std::cerr << "Copying to cliboard requires \"xclip\"." << std::endl;
    std::cerr << "It can be installed with \"sudo apt install xclip\"."
              << std::endl;
}

char getHiddenChar() {
    struct termios oldT {};
    struct termios newT {};
    char ch;
    tcgetattr(STDIN_FILENO, &oldT);
    newT = oldT;
    newT.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newT);
    ch = static_cast<char>(getchar());
    tcsetattr(STDIN_FILENO, TCSANOW, &oldT);
    return ch;
}
