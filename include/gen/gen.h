//
// Created by kello on 22/11/23.
//

#ifndef GENERAL_H
#define GENERAL_H


#include <string>
#include <optional>
#include <functional>

extern const std::string WISP_PROGRAM_VERSION;

namespace genFlags {
    struct Flags {
        bool help{false};
        bool mask{false};
        bool example{false};
        bool version{false};
        bool destroy{false};
        bool random{false};
    };

    typedef std::function<void(Flags &)> NoArgHandle;

#define S(str, f, v) {str, [](Flags& s) {s.f = v;}}
    const std::unordered_map<std::string, NoArgHandle> NoArgs{
            S("--help", help, true),
            S("-h", help, true),
            S("--mask", mask, true),
            S("-m", mask, true),
            S("--example", example, true),
            S("-e", example, true),
            S("--version", version, true),
            S("-v", version, true),
            S("--destroy", destroy, true),
            S("-d", destroy, true),
            S("--random", random, true),
            S("-r", random, true),
    };
#undef S

    typedef std::function<void(Flags &, const std::string &)> OneArgHandle;

#define S(str, f, v) {str, [](Flags& s, const std::string& arg) { s.f = v; }}
    const std::unordered_map<std::string, OneArgHandle> OneArgs{
    };
#undef S

    Flags parse_settings(int argc, const char *argv[]);
}

class gen {
public:
    gen(int argc, const char **argv);
private:
    genFlags::Flags flags;

    void printHelp() const;

    static void printVersion();
};

#endif //GENERAL_H
