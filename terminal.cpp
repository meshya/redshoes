#include <string>
#include <cstdio>
#include <cstring>
#include "terminal.h"

std::string call(std::string command){
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }
    std::string output = " " ;

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            output += buffer ;
    }

    pclose(pipe);

    return output;


}