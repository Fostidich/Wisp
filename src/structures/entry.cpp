//
// Created by kello on 18/02/24.
//

#include "structures/entry.h"

entry::entry(std::string &provider, std::string &username) :
        provider(provider), username(username) {}

std::string entry::getProvider() { return provider; }

std::string entry::getUsername() { return username; }

hash entry::getHash() { return hash; }

unsigned int entry::getUpdate() const { return update; }

std::string entry::getAnnotation() { return annotation; }

void entry::setHash(const class hash &newHash) { this->hash = newHash; }

void entry::setUpdate(int newUpdate) { this->update = newUpdate; }

void entry::setAnnotation(std::string &newAnnotation) { this->annotation = newAnnotation; }

//TODO: to string