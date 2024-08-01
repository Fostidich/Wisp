#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "control/request.hpp"

namespace control {
void execute(const request &request);
}

void checkFormat(const std::string &format);
void checkFilePresence();
void checkConfigs();
void handlerError(enum error error, const std::string &unhandled);
void handlerGeneral(const std::map<enum flag, std::string> &flags);
void handlerGlobal(const std::map<enum flag, std::string> &flags);
void handlerGet(const std::map<enum flag, std::string> &flags);
void handlerSet(const std::map<enum flag, std::string> &flags);

#endif
