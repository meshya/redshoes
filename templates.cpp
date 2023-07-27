#include "templates.h"
#include <string>
#include <vector>
#include "replace.h"



std::string render(std::string body, selectore values){
    for (const auto& value : values){
        std::string _pathern = "\\{"+value[0]+"\\}";
        body = replace(body,_pathern,value[1]);
    }
    return body;
}