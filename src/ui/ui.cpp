#include "ui/ui.hpp"

#include <cmath>
#include <iostream>

const std::string suggestHelp = "Use \"wisp --help\" for a list of commands.";

void ui::noArgumentError() {
    std::cerr << "No argument provided. " << suggestHelp << std::endl;
}

void ui::unknownCommandError(const std::string &text) {
    std::cerr << "Unknown command: \"" << text << "\". " << suggestHelp
              << std::endl;
}

void ui::unknownFlagError(const std::string &text) {
    std::cerr << "Unknown flag: \"" << text << "\". " << suggestHelp
              << std::endl;
}

void ui::doubleFlagError(const std::string &text) {
    std::cerr << "Flag \"" << text << "\" cannot be repeated. " << suggestHelp
              << std::endl;
}

void ui::incompatibleFlagsError(const std::string &text) {
    std::cerr << "Flag \"" << text << "\" cannot be used with priors. "
              << suggestHelp << std::endl;
}

void ui::noValueError(const std::string &text) {
    std::cerr << "Flag \"" << text << "\" requires a value. " << suggestHelp
              << std::endl;
}

void ui::noOptionError(const std::string &text) {
    std::cerr << "Command \"" << text << "\" requires option flags. "
              << suggestHelp << std::endl;
}

void ui::mandatoryFlagError(const std::string &text) {
    std::cerr << "Flag \"" << text << "\" is mandatory. " << suggestHelp
              << std::endl;
}

void ui::helpText() {
    std::cout << R"(
    wisp - General actions:
        -h, --help                      Show help panel
        -f, --format                    Show format details
        -e, --example                   Show usage examples
        -v, --version                   Print version
        -r, --random                    Print a random key
        -d, --destroy                   Immediately destroy all saved information
        -l, --list                      Access stored data

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

    wisp global - Global settings:
        -f, --format <(format)>         Set or show global hash format
        -t, --token <(token)>           Set or show the private token
        -g, --generate                  Generate a new private token
    )" << std::endl;
}

void ui::formatText() {  // TODO put description
    std::cout << R"(
    .   character separator
    -   the hyphen itself
    a   lowercase letter
    b   uppercase letter
    c   one-digit number
    d   special character

    Examples of hash formats:
        a.a.b.b.c.c.d.d
        ab.ab.ab.ab.-.c.c.c.c
        abcd.abcd.abcd.abcd
    )" << std::endl;
}

void ui::exampleText() {  // TODO put description
    std::cout << R"(
    wisp --help
    wisp --version

    wisp get -p website.com -u you@mail.com
    wisp get -p website.com -u you@mail.com -h ab.bc.cd -u 2

    wisp set -p website.com -u you@mail.com -a "love this app"
    wisp set -p website.com -u you@mail.com -h ab.bc.cd -u 2

    wisp glob -h ab.ab.ab.ab.-.c.c.c.c
    wisp glob --token -g
    )" << std::endl;
}

void ui::versionText(const std::string &text) {
    std::cout << "Wisp version: " << text << std::endl;
}

void ui::randomKey(const std::string &text) {
    std::cout << text << std::endl;
}

bool ui::askConfirmation(const std::string &text) {
    std::cout << text << std::endl;
    std::cout << "Write \"CONFIRM\" to proceed: ";
    std::string confirm;
    getline(std::cin, confirm);
    return confirm.compare("CONFIRM") == 0;
}

void ui::destroyOutcome(bool outcome) {
    const std::string toPrint =
        outcome ? "All data successfully deleted." : "Unable to delete data.";
    std::cout << toPrint << std::endl;
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
