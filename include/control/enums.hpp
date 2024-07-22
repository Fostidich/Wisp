#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class command { general, global, get, set };

enum class flag {
    help,
    format,
    example,
    version,
    random,
    destroy,
    list,
    provider,
    username,
    update,
    clipboard,
    annotation,
    remove,
    token,
    generate
};

enum class error {
    none = 0,
    noArgument = 1,
    unknownCommand = 2,
    unknownFlag = 3,
    noValue = 4,
    noOption = 5
};

#endif