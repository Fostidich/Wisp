#include "input/word.hpp"
using namespace std;

Word::Word(string input) {
    value = input;
}

string Word::getValue() {
    return value;
}

int Word::encode() {
    int output = 0, i = 0;
    for (const char ch : value) {
        output += static_cast<int>(ch);
        i++;
    }
    return output;
}
