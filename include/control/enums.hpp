#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class command {
    noArgument, general, global, getter, setter, unknownCommand
};

enum class flag {
    unknownFlag, help
};

#endif