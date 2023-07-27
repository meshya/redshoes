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
    clearScreen();


    base_rules_make_sure();

    FrontEndStartUp(); // From redshoes.cpp

    event::handle();

    std::cout << "\e[?25h"; // restore cursor
    
    return 0;
}

void systemOff (){
    
}