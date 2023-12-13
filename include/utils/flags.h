//
// Created by kello on 12/12/23.
//

#ifndef FLAGS_H
#define FLAGS_H


#include <functional>
#include <string>
#include <optional>

#define S(str, f, v) {str, [](Flags& s) {s.f = v;}}
#define R(str, f, v) {str, [](Flags& s, const std::string& arg) { s.f = v; }}

namespace genFlags {
    struct Flags {
        bool help{false};
        bool mask{false};
        bool example{false};
        bool version{false};
        bool destroy{false};
        bool random{false};
    };

    Flags parse_settings(int argc, char **argv);

    typedef std::function<void(Flags &)> NoArgHandle;
    typedef std::function<void(Flags &, const std::string &)> OneArgHandle;

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

    const std::unordered_map<std::string, OneArgHandle> OneArg{
    };
}

namespace getFlags {
    struct Flags {
        std::optional<std::string> provider;
        std::optional<std::string> username;
        std::optional<std::string> hash;
        std::optional<std::string> update;
        bool clipboard{false};
    };

    typedef std::function<void(Flags &)> NoArgHandle;
    typedef std::function<void(Flags &, const std::string &)> OneArgHandle;

    Flags parse_settings(int argc, char **argv);

    const std::unordered_map<std::string, NoArgHandle> NoArgs{
            S("--clipboard", clipboard, true),
            S("-c", clipboard, true),
    };

    const std::unordered_map<std::string, OneArgHandle> OneArg{
            R("--provider", provider, arg),
            R("-p", provider, arg),
            R("--username", username, arg),
            R("-u", username, arg),
            R("--hash", hash, arg),
            R("-h", hash, arg),
            R("--update", update, arg),
            R("-n", update, arg),
    };
}

namespace setFlags {
    struct Flags {
        std::optional<std::string> provider;
        std::optional<std::string> username;
        std::optional<std::string> hash;
        std::optional<std::string> update;
        std::optional<std::string> annotation;
    };

    typedef std::function<void(Flags &)> NoArgHandle;
    typedef std::function<void(Flags &, const std::string &)> OneArgHandle;

    Flags parse_settings(int argc, char **argv);

    const std::unordered_map<std::string, NoArgHandle> NoArgs{
    };

    const std::unordered_map<std::string, OneArgHandle> OneArg{
            R("--provider", provider, arg),
            R("-p", provider, arg),
            R("--username", username, arg),
            R("-u", username, arg),
            R("--hash", hash, arg),
            R("-h", hash, arg),
            R("--update", update, arg),
            R("-n", update, arg),
            R("--annotation", annotation, arg),
            R("-a", annotation, arg),
    };
}

namespace globFlags {
    struct Flags {
        std::optional<std::string> hash;
        bool token{false};
        std::optional<std::string> change;
        bool generate{false};
        bool show{false};
    };

    typedef std::function<void(Flags &)> NoArgHandle;
    typedef std::function<void(Flags &, const std::string &)> OneArgHandle;

    Flags parse_settings(int argc, char **argv);

    const std::unordered_map<std::string, NoArgHandle> NoArgs{
            S("--token", token, true),
            S("-t", token, true),
            S("--generate", generate, true),
            S("-g", generate, true),
            S("--show", show, true),
            S("-s", show, true),
    };

    const std::unordered_map<std::string, OneArgHandle> OneArg{
            R("--hash", hash, arg),
            R("-h", hash, arg),
            R("--change", change, arg),
            R("-c", change, arg),
    };
}

namespace listFlags {
    struct Flags {
        bool show{false};
        bool add{false};
        bool remove{false};
        std::optional<std::string> provider;
        std::optional<std::string> username;
    };

    typedef std::function<void(Flags &)> NoArgHandle;
    typedef std::function<void(Flags &, const std::string &)> OneArgHandle;

    Flags parse_settings(int argc, char **argv);

    const std::unordered_map<std::string, NoArgHandle> NoArgs{
            S("--show", show, true),
            S("-s", show, true),
            S("--add", add, true),
            S("-a", add, true),
            S("--remove", remove, true),
            S("-r", remove, true),
    };

    const std::unordered_map<std::string, OneArgHandle> OneArg{
            R("--provider", provider, arg),
            R("-p", provider, arg),
            R("--username", username, arg),
            R("-u", username, arg),
    };
}

#undef S
#undef R


#endif //FLAGS_H
