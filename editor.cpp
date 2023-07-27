#include <string>
#include "editor.h"
#include <cstdlib>

void run_vim(std::string file_path){
    system(("vim "+file_path).c_str());
}