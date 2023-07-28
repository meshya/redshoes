#include <string>
#include <cstdio>
#include <cstring>
#include "terminal.h"
#include "main.h"
#include "event.h"
#include "cli.h"
#include "templates.h"
#include "configs.h"
#include <fstream>
#include <string>
#include <sstream>


std::string call(std::string command ,bool superUser){
    if (superUser){
        if (!AmISuperUser()/* From main.cpp */){
            command = "sudo -C 3 " + command;
            clearScreen();
            ShowCursor();
            sleep_system();
            system(command.c_str());
            awaik_system();
            HideCursor();
            clearScreen();
            return " ";
        }
    }
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


int run_task_with_template_handle(std::string command ,std::string template_path, std::string main_path){

    std::ifstream template_file ;
    template_file.open(template_path.c_str());
    std::string template_body = "";
    std::stringstream buffer;
    buffer << template_file.rdbuf();
    template_body += buffer.str();
    template_file.close();
    selectore values;
    values.push_back({"redsocks_chain_name",REDSOCKS_CHAIN_NAME});
    values.push_back({"redsocks_port",REDSOCKS_PORT});
    values.push_back({"redshoes_chain_name",REDSHOES_CHAIN_NAME});
    std::ofstream main_file;
    main_file.open(main_path);
    main_file << render(template_body, values);
    selectore commandHandleValues;
    commandHandleValues.push_back({"conf_file",main_path});
    command = render(command,commandHandleValues);
    main_file.close();
    if (call(command, true) == ""){
        return 1;
    }
    return 0;

}
