#ifndef TERM_H
#define TERM_H

#include <string>

std::string call(std::string command, bool superUser=false);
int run_task_with_template_handle(std::string command ,std::string template_path, std::string main_path);

#endif