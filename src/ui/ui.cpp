#include <ui/ui.hpp>
#include <iostream>

const std::string suggestHelp = "Use \"wisp --help\" for a list of commands";

void ui::noArgumentError() {
    std::cerr << "No argument provided. " << suggestHelp << std::endl;
}

void ui::unknownCommandError(const std::string& text) {
    std::cerr << "Unknown command: \"" << text << "\". " << suggestHelp << std::endl;
}

void ui::unknownFlagError(const std::string& text) {
    std::cerr << "Unknown flag: \"" << text << "\". " << suggestHelp << std::endl;
}

void ui::printHelpText() {
    std::cout << "HELP" << std::endl;
}