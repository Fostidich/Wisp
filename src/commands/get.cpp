#include "commands/commands.hpp"

#include <openssl/sha.h>
#include <string>

const std::vector<char> symbols = {'!', '"', '$', '%', '&', '/', '(', ')', '=',
    '?', '^', '*', '+', '[', ']', '@', '#', '_', ';', ':', ',', '.'};

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

bool commands::copyToClipboard(const std::string &text) {
    if (!system("which xclip > /dev/null 2>&1") &&
        !system(
            ("echo " + text + " | xclip -selection clipboard > /dev/null 2>&1")
                .c_str()))
        return true;
    else
        return false;
}

std::string commands::generateHash(const entry &seed, const std::string &key) {
    // Input retrieval
    std::string token = commands::getToken();
    std::string provider = seed.getProvider();
    std::string username = seed.getUsername();
    std::string format = seed.getFormat();
    int update = seed.getUpdate();
    if (!checkFormatValidity(format)) format = DEFAULT_FORMAT;

    // Compress data to plot
    auto plot = obtainPlot(provider, username, key, token, update);

    // Split format in sections
    std::vector<std::string> splits = splitFormat(format);

    // Hash plot and assign char for each format section
    std::string result;
    for (int i = 0; i < splits.size(); i++) {
        result += assignChar(plot, splits[i]);
        std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
        SHA256(plot.data(), plot.size(), hash.data());
        plot = hash;
    }

    return result;
}

bool checkFormatValidity(const std::string &format) {
    // TODO check format during input phase, not here
    const std::vector<char> validChars = {'a', 'b', 'c', 'd', '.', '-'};
    if (format.back() == '.') return false;
    char temp = '.';
    for (int i = 0; i < format.size(); i++) {
        // Check char validity
        if (std::find(validChars.begin(), validChars.end(), format[i]) ==
            validChars.end())
            return false;

        // Check that no double dot can be found
        if (format[i] == '.' && temp == '.') return false;

        // Check that hyphen is always alone
        if (format[i] == '-' &&
            (temp != '.' || (i + 1 < format.size() && format[i + 1] != '.')))
            return false;

        temp = format[i];
    }
    return true;
}

std::vector<unsigned char> getSHA256(const std::string &input) {
    std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
    auto text = reinterpret_cast<const unsigned char *>(input.data());
    SHA256(text, input.size(), hash.data());
    return hash;
}

void shiftRight(std::vector<unsigned char> &v, int times) {
    for (int t = 0; t < times; t++) {
        unsigned char currentCarry = v[v.size() - 1] & 0x01;
        for (int i = 0; i < v.size(); i++) {
            unsigned char carry = v[i] & 0x01;
            v[i] >>= 1;
            v[i] |= (currentCarry << 7);
            currentCarry = carry;
        }
    }
}

std::vector<unsigned char> obtainPlot(const std::string &provider,
    const std::string &username, const std::string &key,
    const std::string &token, int update) {
    // Input hash
    std::vector<std::vector<unsigned char>> hashes(4);
    hashes[0] = getSHA256(provider);
    hashes[1] = getSHA256(username);
    hashes[2] = getSHA256(key);
    hashes[3] = getSHA256(token);

    // Update-based shifts
    for (int i = 0; i < 4; i++)
        shiftRight(hashes[i], UPDATE_SHIFT_MULTIPLIER * i * update);

    // XOR inputs together
    std::vector<unsigned char> plot(hashes[0]);
    plot = hashes[0];
    for (int i = 1; i < 4; ++i)
        for (int j = 0; j < SHA256_DIGEST_LENGTH; ++j) plot[j] ^= hashes[i][j];

    return plot;
}

std::vector<std::string> splitFormat(const std::string &format) {
    std::vector<std::string> splits;
    std::string temp;
    for (int i = 0; i < format.size(); i++) {
        if (format[i] == '.') {
            splits.push_back(temp);
            temp.clear();
        } else
            temp += format[i];
    }
    splits.push_back(temp);
    return splits;
}

char assignChar(
    const std::vector<unsigned char> &plot, const std::string &split) {
    if (split.empty() || split[0] == '-') return '-';

    // Populate chars pool
    std::vector<char> pool;
    for (char ch : split) switch (ch) {
            case 'a':
                for (char l = 'a'; l <= 'z'; l++) pool.push_back(l);
                break;
            case 'b':
                for (char u = 'A'; u <= 'Z'; u++) pool.push_back(u);
                break;
            case 'c':
                for (char d = '0'; d <= '9'; d++) pool.push_back(d);
                break;
            case 'd':
                pool.insert(pool.end(), symbols.begin(), symbols.end());
                break;
        }

    // XOR bytes of plot
    unsigned char tablet = plot[0];
    for (int i = 1; i < SHA256_DIGEST_LENGTH; i++) tablet ^= plot[i];

    // Char selection
    return pool.at(tablet % pool.size());
}
