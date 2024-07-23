#include <termios.h>

#include <csignal>
#include <random>
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>

#include <climits>
#endif

char randomChar() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 61);
    int rand = dis(gen);

    /*
     * 23 pound
     * 45 hyphen
     * 48-57 digits
     * 65-90 uppercase letters
     * 97-122 lowercase letters
     */
    if (rand < 10) return char('0' + rand);
    if (rand < 36)
        return char('A' + rand - 10);
    else
        return char('a' + rand - 36);
}

char getHiddenChar() {
    struct termios oldT {
    }, newT{};
    char ch;
    tcgetattr(STDIN_FILENO, &oldT);
    newT = oldT;
    newT.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newT);
    ch = static_cast<char>(getchar());
    tcsetattr(STDIN_FILENO, TCSANOW, &oldT);
    return ch;
}

std::string getExecutableDir() {
    std::string executablePath = getExecutablePath();
    size_t lastSlash = executablePath.find_last_of('/');
    std::string executableDir = (lastSlash != std::string::npos)
                                    ? executablePath.substr(0, lastSlash + 1)
                                    : "";
    return executableDir;
}

std::string getExecutablePath() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return std::string(buffer);
#elif __linux__
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        return buffer;
    } else {
        return "";
    }
#else
    return "";
#endif
}