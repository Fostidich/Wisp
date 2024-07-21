#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class command {
    noArgument, general, global, getter, setter, unknownCommand
};

enum class flag {
    unknownFlag, help, mask, example, version, random, destroy, list,
    provider, username, hash, update, clipboard, annotation, remove,
    token, change, generate, show
};

#endif