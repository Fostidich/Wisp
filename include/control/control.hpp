#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "control/request.hpp"

namespace control {
void execute(const request &request);
}

void handlerError(enum error error, const std::string &unhandled);
void handlerGeneral(const std::map<enum flag, std::string> &flags);
void handlerGlobal(const std::map<enum flag, std::string> &flags);
void handlerGet(const std::map<enum flag, std::string> &flags);
void handlerSet(const std::map<enum flag, std::string> &flags);

#endif
