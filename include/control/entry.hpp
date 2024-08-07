#ifndef ENTRY_HPP
#define ENTRY_HPP

#include "control/enums.hpp"

#include <nlohmann/json.hpp>
#include <string>

struct date {
    unsigned int year;
    unsigned int month;
    unsigned int day;
};
struct date today();
bool isDateValid(struct date date);

class entry {
  public:
    /// Entry is initialized with today's date
    entry(const std::string &provider, const std::string &username);
    /// Entry is initialized with today's date
    entry(const nlohmann::basic_json<> &entry);
    /// Entry is initialized with today's date
    entry(const std::map<enum flag, std::string> &flags);

    std::string getProvider() const;
    std::string getUsername() const;
    std::string getFormat() const;
    int getUpdate() const;
    std::string getAnnotation() const;
    struct date getDate() const;

    void setFormat(const std::string &newFormat);
    /// Setting a new update will also update the date with today's date
    void setUpdate(int newUpdate);
    void setAnnotation(const std::string &newAnnotation);

    std::string toString(
        int providerMaxLen, int usernameMaxLen, int updateMaxLen) const;
    nlohmann::json toJson() const;

  private:
    std::string provider;
    std::string username;
    std::string format;
    int update{0};
    std::string annotation;
    struct date date {
        .year = 2000, .month = 1, .day = 1
    };
};

#endif
