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

    std::cout << "\e[?25l"; // Hide cursor
    clearScreen();


    base_rules_make_sure();

    FrontEndStartUp(); // from redshoes.cpp

    event::handle();

    std::cout << "\e[?25h"; // restore cursor
    
    return 0;
}
