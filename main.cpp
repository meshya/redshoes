#include <iostream>
#include "event.h"
#include "cli.h"
#include "keyboard.h"
#include "form.h"
#include "redshoes.h"
#include "iptables.h"

//event e(EVENT,100);

//std::string row2_H (){
//    return "mohali "+ *(l.letter);
//}




int main() {

    HideCursor(); // From cli.cpp
    clearScreen(); // From cli.cpp


    BaseRulesMakeSure(); // From iptables.cpp

    FrontEndStartUp(); // From redshoes.cpp

    event::handle(); // From event.cpp
    /* It's main event loop */

    systemOff(); // from six line laters :)

    return 0;
}

void systemOff (){
    ShowCursor(); // from cli.cpp    
}