#include <fstream>
#include <vector>
#include <array>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include "configs.h"
#include "terminal.h"
#include "event.h"
#include "iptables.h"
#include <sstream>

bool tunnel_status = false;

bool isChainExists(const std::string& chainName) {
    std::string command = "iptables-save";
    std::string output = "" ;
    output += call(command);

    if (output == "") {
        std::cerr << "Error executing iptables-save command." << std::endl;
        return false;
    }

    bool chainFound = false;

    if (strstr(output.c_str(), (":" + chainName).c_str())){
        chainFound = true;
    }

    return chainFound;
}

int run_iptables_template_rule(std::string template_path, std::string main_path){
    return run_task_with_template_handle("iptables-restore < {conf_file}",template_path, main_path);
}

int set_base_rules(){
    return run_iptables_template_rule(BASE_RULES_TEMPLATE_PATH,BASE_RULES_RENDERED_PATH);

}

int remove_base_rules(){
    std::string command1 = "iptables -F " + REDSOCKS_CHAIN_NAME;
    std::string command2 = "iptables -X " + REDSOCKS_CHAIN_NAME;
    std::string command3 = "iptables -F " + REDSHOES_CHAIN_NAME;
    std::string command4 = "iptables -X " + REDSHOES_CHAIN_NAME;

    if ((call(command1, true)=="") or (call(command2, true)=="") or (call(command3, true)=="") or (call(command4, true)=="")){
        return 1;
    }
    return 0;
}

int BaseRulesMakeSure(){
    if (isChainExists(REDSOCKS_CHAIN_NAME) or isChainExists(REDSHOES_CHAIN_NAME)){
        if (remove_base_rules()!=0){
            return 1;
        }
    }
    if (set_base_rules()!=0){
        return 1;
    }
    return 0;
}

int tunnel_on (){
    int status =  run_iptables_template_rule(TUNNEL_ON_TEMPLATE_PATH,TUNNEL_ON_RENDERED_PATH);
    if (status == 0){
        tunnel_status = true;
    }else{
        tunnel_status = false;
    }
    return status;
}


int tunnel_off (){
    return run_iptables_template_rule(TUNNEL_OFF_TEMPLATE_PATH,TUNNEL_OFF_RENDERED_PATH);
}