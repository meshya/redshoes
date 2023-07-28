#include <iostream>
#include "event.h"
#include "cli.h"
#include "keyboard.h"
#include "form.h"
#include "redshoes.h"
#include "iptables.h"
#include "main.h"

int main() {

    HideCursor(); // From cli.cpp
    clearScreen(); // From cli.cpp


    BaseRulesMakeSure(); // From iptables.cpp

    FrontEndStartUp(); // From redshoes.cpp

    event::handle(); // From event.cpp
    /* It's event loop */

    systemOff(); // from some lines later :)

    return 0;
}

int InterSuperUser(){
    
}

void systemOff (){
    ShowCursor(); // from cli.cpp
    /* We should be responsable for users' terminal's cursor :) */
}