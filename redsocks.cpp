#include "redsocks.h"
#include "event.h"
#include "cli.h"
#include "redshoes.h"
#include "configs.h"
#include "terminal.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <limits.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>



std::string getExecutableName(pid_t pid) {
    std::string execName;
    std::ostringstream oss;
    oss << "/proc/" << pid << "/comm";  // Path to the process command file

    std::ifstream file(oss.str());
    if (file.is_open()) {
        std::getline(file, execName);
        file.close();
    }

    return execName;
}



bool isProcessRunning(pid_t pid) {
    int status;
    return waitpid(pid, &status, WNOHANG) == 0;
}



int start_redsocks(){
    std::string command = "";
    command += REDSOCKS_BIN_FILE_PATH;
    command += " -c {conf_file}";
    command += " -p " + REDSOCKS_PID_FILE_PATH;
    run_task_with_template_handle(command ,REDSOCKS_CONFIG_TEMPLATE_PATH ,REDSOCKS_CONFIG_RENDERED_PATH);
    set_status();
    return 0;
}

int stop_redsocks(){
    int kill_status = kill(pid_redsocks(), SIGINT);
    set_status();
    if (kill_status == 0){
        return 0; // Kill was succefull ! haha I'm a killer !!!
        //std::cout << "killer" << std::endl;
    }else{
        //std::cout << "Failed kill pid " << pid_redsocks() << " try running redshoes as superuser." << std::endl;
        return 1;
    }
    // ToDo : make redshoes understandable what is error in kill the pid
}


int pid_redsocks(){

    if (!(std::filesystem::exists(REDSOCKS_PID_FILE_PATH))){
        return 0;
    }

    std::ifstream pid_file_S(REDSOCKS_PID_FILE_PATH);
    std::string pidSTR = "";
    std::string line;
    while(std::getline(pid_file_S, line)){
        pidSTR += line;
    }
    pidSTR = strip(pidSTR);
    if (pidSTR==""){
        return 0;
    }

    int PID = std::stoi(pidSTR);

    if (isProcessRunning(PID) == false){
        return 0;
    }

    if (getExecutableName(PID)=="redsocks"){
        return PID;
    }else{
        return 0 ;
    }
}

bool redsocks_status = false;

void set_status(){
    if (pid_redsocks()==0){
        redsocks_status = false;
    } else {
        redsocks_status = true;
    }
}

event set_status_E(&set_status,2500);
