#include <iostream>
#include <ui/ui.hpp>

const std::string suggestHelp = "Use \"wisp --help\" for a list of commands";

void ui::noArgumentError() { std::cerr << "No argument provided. " << suggestHelp << std::endl; }

void ui::unknownCommandError(const std::string &text) {
    std::cerr << "Unknown command: \"" << text << "\". " << suggestHelp << std::endl;
}

void ui::unknownFlagError(const std::string &text) {
    std::cerr << "Unknown flag: \"" << text << "\". " << suggestHelp << std::endl;
}

void ui::noValueError(const std::string &text) {
    std::cerr << "Flag \"" << text << "\" requires a value. " << suggestHelp << std::endl;
}

void ui::noOptionError(const std::string &text) {
    std::cerr << "Command \"" << text << "\" requires option flags. " << suggestHelp << std::endl;
}

void ui::printHelpText() {
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
        -n, --update <update>           Use a custom update number for generation
        -c, --clipboard                 Save the hash to clipboard without printing it

    wisp set - Add custom settings:
        -p, --provider <*provider*>     Add settings for the entry with this provider
        -u, --username <*username*>     Add settings for the entry with this username
        -f, --format <format>           Set format for the selected entry
        -n, --update <update>           Set update number for the selected entry
        -a, --annotation <"note">       Set a note for the selected entry
        -r, --remove                    Remove the entry from the list

    wisp global - Global settings:
        -f, --format <(format)>         Set or show global hash format
        -t, --token <(token)>           Set or show the private token
        -g, --generate                  Generate a new private token
    )" << std::endl;
}