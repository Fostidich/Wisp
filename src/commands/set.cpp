#include "commands/commands.hpp"

bool commands::setEntry(const entry &toSet) {
    bool found = false;
    auto entries = commands::retrieveEntries();

    // Look for the entry
    for (auto &e : entries) {
        if (e.getProvider().compare(toSet.getProvider()) == 0 &&
            e.getUsername().compare(toSet.getUsername()) == 0) {
            // Updating entry
            std::string f = toSet.getFormat();
            int n = toSet.getUpdate();
            std::string a = toSet.getAnnotation();
            if (!f.empty()) e.setFormat(f);
            if (n > 0) e.setUpdate(n);
            if (!a.empty()) e.setAnnotation(a);
            found = true;
            break;
        }
    }

    // Add a new entry
    if (!found) entries.push_back(toSet);

    return commands::dumpEntries(entries);
}

bool commands::deleteEntry(const entry &toDelete) {
    return true;
    // TODO
}
