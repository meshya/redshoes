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
    (*main_form).push(redsocks_stat_FO);
    (*main_form).push(iptables_stat_FO);
    (*main_form).push(redsocks_button_FO);
    (*main_form).push(redsocks_configure_FO);
    (*main_form).push(message_bar_FO);
    (*main_form).show();
    focus_on_form(main_form);

    event::handle();

    std::cout << "\e[?25h"; // restore cursor
    
    return 0;
}
