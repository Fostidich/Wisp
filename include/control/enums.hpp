#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class command { general, global, get, set };

enum class flag {
    help,
    format,
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
    none,
    noArgument,
    unknownCommand,
    unknownFlag,
    doubleFlag,
    incompatibleFlags,
    noValue,
    noOption,
    mandatoryFlag
};

#endif
