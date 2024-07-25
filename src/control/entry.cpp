#include "control/entry.hpp"

#include <exception>
#include <format>
#include <sys/ioctl.h>

struct date today() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm *localTime = std::localtime(&currentTime);
    return {.year = static_cast<unsigned int>(localTime->tm_year + 1900),
        .month = static_cast<unsigned int>(localTime->tm_mon + 1),
        .day = static_cast<unsigned int>(localTime->tm_mday)};
}

bool isDateValid(struct date date) {
    if (date.year == 0 || date.month == 0 || date.day == 0) return false;
    if (date.year > 4000 || date.month > 12 || date.day > 31) return false;

    const int daysInMonth[] = {
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isLeap =
        date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0);

    if (isLeap && date.month == 2 && date.day > 29) return false;
    if (date.day > daysInMonth[date.month]) return false;

    return true;
}

entry::entry(std::string provider, std::string username) {
    this->provider = provider;
    this->username = username;
    date = today();
}

entry::entry(nlohmann::basic_json<> entry) {
    try {
        if (entry.contains("provider") && entry["provider"].is_string())
            provider = entry["provider"];
        if (entry.contains("username") && entry["username"].is_string())
            username = entry["username"];
        if (entry.contains("format") && entry["format"].is_string())
            format = entry["format"];
        if (entry.contains("update") && entry["update"].is_number_unsigned())
            update = entry["update"];
        if (entry.contains("annotation") && entry["annotation"].is_string())
            annotation = entry["annotation"];
        if (entry.contains("date")) {
            const auto &d = entry["date"];
            if (d.contains("year") && d["year"].is_number_unsigned())
                date.year = d["year"];
            if (d.contains("month") && d["month"].is_number_unsigned())
                date.month = d["month"];
            if (d.contains("day") && d["day"].is_number_unsigned())
                date.day = d["day"];
            if (!isDateValid(date)) date = today();
        }
    } catch (const std::exception &e) {
        throw;
    }
}

const std::string &entry::getProvider() const {
    return provider;
}

const std::string &entry::getUsername() const {
    return username;
}

const std::string &entry::getFormat() const {
    return format;
}

int entry::getUpdate() const {
    return update;
}

const struct date &entry::getDate() const {
    return date;
}

void entry::setFormat(const std::string newFormat) {
    format = newFormat;
}

void entry::setUpdate(int newUpdate) {
    update = newUpdate;
    date = today();
}

void entry::setAnnotation(const std::string newAnnotation) {
    annotation = newAnnotation;
}

std::string entry::toString(  // TODO use colors :)
    int providerMaxLen, int usernameMaxLen, int updateMaxLen) const {
    std::string s;
    struct winsize w;
    int width = ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0 ? w.ws_col : 100;

    s += '[' + std::format("{:0{}}", date.year, 4) + '-' +
         std::format("{:0{}}", date.month, 2) + '-' +
         std::format("{:0{}}", date.day, 2) + ']';
    s += ' ' + std::format("{:<{}}", provider, providerMaxLen);
    s += ' ' + std::format("{:<{}}", username, usernameMaxLen);
    s += ' ' + std::format("{:>{}}", update, updateMaxLen);
    s += ' ' + format;
    s += (format.empty() ? "" : " ") + annotation;

    if (s.size() > width) s.erase(width);
    return s;
}