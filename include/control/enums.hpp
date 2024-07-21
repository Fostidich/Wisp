#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class command {
    noArgument, general, global, get, set, unknownCommand
};

enum class flag {
    help, format, example, version, random, destroy, list,
    provider, username, update, clipboard, annotation, remove,
    token, generate, unknownFlag
};

#endif