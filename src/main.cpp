#include <iostream>
#include "input/word.hpp"
using namespace std;

int main() {
    string input;
    cout << "Insert word: ";
    cin >> input;
    Word block(input);
    cout << "value: " << block.getValue() << ", encoded to: " << block.encode() << endl;
    return 0;
}
