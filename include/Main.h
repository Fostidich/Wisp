//
// Created by kello on 22/11/23.
//

#ifndef MAIN_H
#define MAIN_H

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>

const std::string WISP_PROGRAM_VERSION = "wisp-0.1.0";

struct MySettings {
    bool help {false};
    bool verbose {false};
    std::optional<std::string> infile;
    std::optional <std::string> outfile;
    std::optional<int> value;
};

typedef std::function<void(MySettings&)> NoArgHandle;

#define S(str, f, v) {str, [](MySettings& s) {s.f = v;}}
const std::unordered_map<std::string, NoArgHandle> NoArgs {
        S("--help", help, true),
        S("-h", help, true),
        S("--verbose", verbose, true),
        S("-v", verbose, true),
        S("--quiet", verbose, false),
};
#undef S

typedef std::function<void(MySettings&, const std::string&)> OneArgHandle;

#define S(str, f, v) {str, [](MySettings& s, const std::string& arg) { s.f = v; }}
const std::unordered_map<std::string, OneArgHandle> OneArgs {
        S("--input", infile, arg),
        S("--output", outfile, arg),
        S("--value", value, stoi(arg)),
};
#undef S

MySettings parse_settings(int argc, const char* argv[]);
int main(int argc, char *argv[]);


#endif
