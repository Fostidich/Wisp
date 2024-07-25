#include "control/control.hpp"
#include "control/request.hpp"

int main(int argc, char *argv[]) {
    std::vector<std::string> args;
    for (int i = 0; i < argc; i++) args.push_back(std::string(argv[i]));
    const request request(args);
    control::execute(request);
    return 0;
}
