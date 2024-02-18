//
// Created by kello on 18/02/24.
//

#include "structures/date.h"
#include <chrono>
#include <ctime>

date::date() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);
    year = localTime->tm_year + 1900;
    month = localTime->tm_mon + 1;
    day = localTime->tm_mday;
}

date::date(unsigned int year, unsigned int month, unsigned int day) :
        year(year), month(month), day(day) {}

std::string date::toString() const {
    std::string m, d;
    if (month < 10) m = "0" + std::to_string(month);
    else m = std::to_string(month);
    if (day < 10) d = "0" + std::to_string(day);
    else d = std::to_string(day);
    return std::to_string(year) + "-" + m + "-" + d;
}