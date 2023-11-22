//
// Created by kello on 22/11/23.
//

#include "../include/Main.h"

#include <fstream>
#include <iostream>

#include "../include/general/General.h"
#include "../include/get/Get.h"
#include "../include/glob/Glob.h"
#include "../include/list/List.h"
#include "../include/set/Set.h"

using namespace std;

int main(const int argc, char* argv[]) {
    switch (argv[1]) {
        case "get": Get get();
        case "set": Set set();
        case "glob": Glob glob();
        case "list": List list();
        default: General general(argc, argv);
    }
    ifstream file("assets/help.txt");
    string line;
    if (!file.is_open()) return -1;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    cout << endl;
    file.close();
    cout << "Currently running version: " << wisp_program_version << endl;
    return 0;
}
