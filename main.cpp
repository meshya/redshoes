#include <iostream>

#include <unistd.h>
#include "event.h"
#include "cli.h"
#include "keyboard.h"
#include "form.h"
#include "redshoes.h"
#include "iptables.h"
#include "main.h"

int fail = 0;

int main() {

    int statusCode =  InterSuperUser();
    if (statusCode){
        print("Please run me with sudo");
        Cwrite("Run application anyway [y/n] ? ") ;
        std::string result;
        while(1){
            std::getline(std::cin,result);
            if (result == "y" or result == "Y" ){
                break;
            }else if(result=="n" or result=="N"){
                return 0;
            }
            result="";
            Cwrite("unvalid result only use y or n : ");
        }
    }

    HideCursor(); // From cli.cpp
    clearScreen(); // From cli.cpp

    if (fail == 0)
    fail += BaseRulesMakeSure(); // From iptables.cpp

    if (fail == 0)
    fail += FrontEndStartUp(); // From redshoes.cpp
    
    if (fail == 0)
    event::handle(); // From event.cpp
    /* It's event loop */

    systemOff(); // from some lines later :)

    return fail;
}

bool AmISuperUser(){
    return getuid() == 0 ;
}
int InterSuperUser(){
    if (getuid()!=0){
        if (setuid(0)!=0){
            return 1;
        }
    }
    return 0;
}

void systemOff (){
    ShowCursor(); // from cli.cpp
    /* We should be responsable for users' terminal's cursor :) */
    clearScreen();
    /* Think like japanes, clear everything bedore leave :) */
}