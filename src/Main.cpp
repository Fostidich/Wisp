//
// Created by kello on 22/11/23.
//

#include "Main.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int main(const int argc, char *argv[]) {
    optional
    fat guy 111
    fghj
    
    return 0;
}

MySettings parse_settings(int argc, const char* argv[]) {
    MySettings settings;
    // argv[0] is traditionally the program name, so start at 1
    for(int i {1}; i < argc; i++) {
        string opt {argv[i]};
        // Is this a NoArg?
        if(auto j {NoArgs.find(opt)}; j != NoArgs.end())
            j->second(settings); // Yes, handle it!

            // No, how about a OneArg?
        else if(auto k {OneArgs.find(opt)}; k != OneArgs.end())
            // Yes, do we have a parameter?
            if(++i < argc)
                // Yes, handle it!
                k->second(settings, {argv[i]});
            else
                // No, and we cannot continue, throw an error
                throw std::runtime_error {"missing param after " + opt};

            // No, has infile been set yet?
        else if(!settings.infile)
            // No, use this as the input file
            settings.infile = argv[i];

            // Yes, possibly throw here, or just print an error
        else
            cerr << "unrecognized command-line option " << opt << endl;
    }

    return settings;
}
