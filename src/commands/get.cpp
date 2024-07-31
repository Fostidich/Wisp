#include "commands/commands.hpp"

#include <openssl/sha.h>

void commands::populateEntry(entry &initial) {
    auto entries = commands::retrieveEntries();

    std::string f;
    int n;
    for (const auto &e : entries) {
        if (e.getProvider().compare(initial.getProvider()) ||
            e.getUsername().compare(initial.getUsername()))
            continue;
        f = e.getFormat();
        n = e.getUpdate();
        break;
    }

    if (initial.getFormat().empty()) {
        if (f.empty())
            initial.setFormat(commands::getFormat());
        else
            initial.setFormat(f);
    }

    if (initial.getUpdate() == 0 && n > 0) initial.setUpdate(n);
}

std::string commands::generateHash(const entry &seed, const std::string &key) {
    std::string token = commands::getToken();
    std::string provider = seed.getProvider();
    std::string username = seed.getUsername();
    std::string format = seed.getFormat();
    int update = seed.getUpdate();

    return key;
}

bool commands::copyToClipboard(const std::string &text) {
    if (!system("which xclip > /dev/null 2>&1") &&
        !system(
            ("echo " + text + " | xclip -selection clipboard > /dev/null 2>&1")
                .c_str()))
        return true;
    else
        return false;
}

unsigned char *getSHA256(const std::string &input) {
    auto *hash = new unsigned char[SHA256_DIGEST_LENGTH];
    const auto *text = reinterpret_cast<const unsigned char *>(input.c_str());
    unsigned int len = strlen((const char *)text);
    SHA256(text, len, hash);
    return hash;
}
