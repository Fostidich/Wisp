//
// Created by kello on 12/12/23.
//

#ifndef FLAGS_H
#define FLAGS_H


#include <functional>
#include <string>
#include <optional>

template<class cmd>
typename cmd::Flags parse_settings(int argc, const char **argv);

class genFlags {
public:
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
    const std::unordered_map<std::string, NoArgHandle> NoArgs {
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
};

class getFlags {
public:
    struct Flags {
        std::optional<std::string> provider;
        std::optional<std::string> username;
        std::optional<std::string> hash;
        std::optional<std::string> update;
        bool clipboard{false};
    };

    typedef std::function<void(Flags &)> NoArgHandle;

#define S(str, f, v) {str, [](Flags& s) {s.f = v;}}
    const std::unordered_map<std::string, NoArgHandle> NoArgs{
            S("--clipboard", clipboard, true),
            S("-c", clipboard, true),
    };
#undef S

    typedef std::function<void(Flags &, const std::string &)> OneArgHandle;

#define S(str, f, v) {str, [](Flags& s, const std::string& arg) { s.f = v; }}
    const std::unordered_map<std::string, OneArgHandle> OneArgs{
            S("--provider", provider, arg),
            S("-p", provider, arg),
            S("--username", username, arg),
            S("-u", username, arg),
            S("--hash", hash, arg),
            S("-h", hash, arg),
            S("--update", update, arg),
            S("-n", update, arg),
    };
#undef S
};


#endif //FLAGS_H
