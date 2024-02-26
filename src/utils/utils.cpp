//
// Created by kello on 25/02/24.
//

#include "utils/utils.h"
#include <random>
#include <termios.h>
#include <csignal>

using namespace std;

char randomChar() {
    /*
     * 23 pound
     * 45 hyphen
     * 48-57 digits
     * 65-90 uppercase letters
     * 97-122 lowercase letters
     */
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 61);
    int rand = dis(gen);

    if (rand < 10) return char('0' + rand);
    if (rand < 36) return char('A' + rand - 10);
    else return char('a' + rand - 36);
}

char getHiddenChar() {
    struct termios oldT{}, newT{};
    char ch;
    tcgetattr(STDIN_FILENO, &oldT);
    newT = oldT;
    newT.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newT);
    ch = static_cast<char>(getchar());
    tcsetattr(STDIN_FILENO, TCSANOW, &oldT);
    return ch;
}