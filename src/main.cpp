#include "control/control.hpp"
#include "control/request.hpp"

int main(int argc, char *argv[]) {
    std::vector<std::string> args;
    args.reserve(argc);
    for (int i = 0; i < argc; i++) args.emplace_back(argv[i]);
    const request request(args);
    control::execute(request);
    return 0;
}
