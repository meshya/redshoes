#include <string>
#include <sys/wait.h>
#include <iostream>
#include <limits.h>
#include "configs.h"

std::string REDSOCKS_CHAIN_NAME = "RED_SOCKS";
std::string REDSOCKS_PORT = "55442";
std::string REDSHOES_CHAIN_NAME = "RED_SHOES";

std::string here() {
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, sizeof(path));

    if (count != -1) {
        path[count] = '\0';
        std::string filePath(path);
        std::string folderPath = filePath.substr(0, filePath.find_last_of('/'));
        return folderPath;
    } else {
        std::cerr << "Error retrieving file path." << std::endl;
        return " ";
    }
}


std::string REDSOCKS_BIN_FILE_PATH=here()+"/bin/redsocks/redsocks";
std::string REDSOCKS_PID_FILE_PATH=here()+"/bin/redsocks/pid";
std::string REDSOCKS_CONFIG_FILE_PATH=here()+"/bin/redsocks/config.conf";
std::string BASE_RULES_TEMPLATE_PATH=here()+"/bin/iptables/base_rules_template.conf";
std::string BASE_RULES_RENDERED_PATH=here()+"/bin/iptables/base_rules.conf";
std::string TUNNEL_ON_TEMPLATE_PATH=here()+"/bin/iptables/tunnel_on_template.conf";
std::string TUNNEL_OFF_TEMPLATE_PATH=here()+"/bin/iptables/tunnel_off_template.conf";
std::string TUNNEL_OFF_RENDERED_PATH=here()+"/bin/iptables/tunnel_off.conf";
std::string TUNNEL_ON_RENDERED_PATH=here()+"/bin/iptables/tunnel_on.conf";
