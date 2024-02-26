//
// Created by kello on 18/02/24.
//

#include <vector>
#include "structures/entry.h"

entry::entry(std::string &provider, std::string &username, std::string &sDate) :
        provider(provider), username(username) {
    std::vector<int> result;
    std::string::size_type pos = 0;
    std::string::size_type nextPos = 0;

    nextPos = sDate.find('-', pos);
    if (nextPos == std::string::npos) {
        lastModified = date();
        return;
    }
    result.push_back(std::stoi(sDate.substr(pos, nextPos - pos)));

    pos = nextPos + 1;
    nextPos = sDate.find('-', pos);
    if (nextPos == std::string::npos) {
        lastModified = date();
        return;
    }
    result.push_back(std::stoi(sDate.substr(pos, nextPos - pos)));

    pos = nextPos + 1;
    result.push_back(std::stoi(sDate.substr(pos)));

    lastModified = date(result[0], result[1], result[2]);
}

std::string entry::getProvider() { return provider; }

std::string entry::getUsername() { return username; }

hashMask entry::getMask() { return mask; }

unsigned int entry::getUpdate() const { return update; }

std::string entry::getAnnotation() { return annotation; }

date entry::getLastModified() { return lastModified; }

void entry::setMask(const class hashMask &newMask) { mask = newMask; }

void entry::setUpdate(unsigned int newUpdate) { update = newUpdate; }

void entry::setAnnotation(std::string &newAnnotation) { annotation = newAnnotation; }

void entry::setMaxLengthLine(unsigned int newMaxLengthLine) { maxLengthLine=newMaxLengthLine; }

std::string entry::toString() {
    std::string u, h, a;
    std::string temp = update < 10 ? std::to_string(update) + " " : std::to_string(update);
    u = update != 0 ? temp : "  ";
    h = !mask.empty() ? mask.toString() : "";
    a = !annotation.empty() ? annotation : "";
    temp = !mask.empty() ? u + " " + h + "  " + a : u + " " + a;
    std::string result = "[" + lastModified.toString() + "]  " +
            provider + " - " +
            username + fillSpaces(provider + " - " + username) + " " +
            temp;
    return result;
}

std::string entry::fillSpaces(const std::string& word) {
    std::string spaces = " ";
    for (size_t i{word.length()}; i < maxLengthLine; i++)
        spaces += " ";
    return spaces;
}

unsigned int entry::maxLengthLine = 0;
