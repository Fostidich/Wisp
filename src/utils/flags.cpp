//
// Created by kello on 12/12/23.
//

#include <stdexcept>
#include <iostream>

template <class cmd>
typename cmd::Flags parse_settings(const int argc, const char **argv) {
    typename cmd::Flags settings;
    const auto& noArgs = cmd::NoArgs;
    const auto& oneArgs = cmd::OneArgs;
    for (int i = 1; i < argc; i++) {
        std::string opt{argv[i]};
        if (auto j{noArgs.find(opt)}; j != noArgs.end())
            j->second(settings);
        else if (auto k{oneArgs.find(opt)}; k != oneArgs.end())
            if (++i < argc || argv[1][0] != '-')
                k->second(settings, {argv[i]});
            else
                throw std::runtime_error{"ERROR: missing parameter after flag " + opt};
        else
            std::cerr << "ERROR: unrecognized command-line option " << opt << std::endl;
    }
    return settings;
}

