#include <iostream>
#include "event.h"


extern std::string REDSOCKS_BIN_FILE_PATH;
extern std::string REDSOCKS_PID_FILE_PATH;
extern std::string REDSOCKS_CONFIG_FILE_PATH;


int pid_redsocks();

extern bool status_redsocks;

void set_status ();

extern event set_status_E ;

int start_redsocks();

int stop_redsocks();
