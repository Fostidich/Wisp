//
// Created by kello on 12/12/23.
//

#include <stdexcept>
#include <iostream>
#include "utils/flags.h"

//FIXME: find a way to reuse same code

genFlags::Flags genFlags::parse_settings(int argc, char **argv) {
    Flags settings;
    for (int i = 1 /* i=2 for one-word commands */; i < argc; i++) {
        std::string opt{argv[i]};
        if (auto j{NoArgs.find(opt)}; j != NoArgs.end())
            j->second(settings);
        else if (auto k{OneArg.find(opt)}; k != OneArg.end())
            if (++i < argc)
                k->second(settings, {argv[i]});
            else
                std::cerr << "ERROR: missing parameter after flag " << opt << std::endl;
        else
            std::cerr << "ERROR: unrecognized command-line option " << opt << std::endl;
    }
    return settings;
}

getFlags::Flags getFlags::parse_settings(int argc, char **argv) {
    Flags settings;
    for (int i = 2; i < argc; i++) {
        std::string opt{argv[i]};
        if (auto j{NoArgs.find(opt)}; j != NoArgs.end())
            j->second(settings);
        else if (auto k{OneArg.find(opt)}; k != OneArg.end())
            if (++i < argc)
                k->second(settings, {argv[i]});
            else
                std::cerr << "ERROR: missing parameter after flag " << opt << std::endl;
        else
            std::cerr << "ERROR: unrecognized command-line option " << opt << std::endl;
    }
    return settings;
}

setFlags::Flags setFlags::parse_settings(int argc, char **argv) {
    Flags settings;
    for (int i = 2; i < argc; i++) {
        std::string opt{argv[i]};
        if (auto j{NoArgs.find(opt)}; j != NoArgs.end())
            j->second(settings);
        else if (auto k{OneArg.find(opt)}; k != OneArg.end())
            if (++i < argc)
                k->second(settings, {argv[i]});
            else
                std::cerr << "ERROR: missing parameter after flag " << opt << std::endl;
        else
            std::cerr << "ERROR: unrecognized command-line option " << opt << std::endl;
    }
    return settings;
}

globFlags::Flags globFlags::parse_settings(int argc, char **argv) {
    Flags settings;
    for (int i = 2; i < argc; i++) {
        std::string opt{argv[i]};
        if (auto j{NoArgs.find(opt)}; j != NoArgs.end())
            j->second(settings);
        else if (auto k{OneArg.find(opt)}; k != OneArg.end())
            if (++i < argc)
                k->second(settings, {argv[i]});
            else
                std::cerr << "ERROR: missing parameter after flag " << opt << std::endl;
        else
            std::cerr << "ERROR: unrecognized command-line option " << opt << std::endl;
    }
    return settings;
}

listFlags::Flags listFlags::parse_settings(int argc, char **argv) {
    Flags settings;
    for (int i = 2; i < argc; i++) {
        std::string opt{argv[i]};
        if (auto j{NoArgs.find(opt)}; j != NoArgs.end())
            j->second(settings);
        else if (auto k{OneArg.find(opt)}; k != OneArg.end())
            if (++i < argc)
                k->second(settings, {argv[i]});
            else
                std::cerr << "ERROR: missing parameter after flag " << opt << std::endl;
        else
            std::cerr << "ERROR: unrecognized command-line option " << opt << std::endl;
    }
    return settings;
}