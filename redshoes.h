#ifndef REDSHOES_H
#define REDSHOES_H

#include <iostream>
#include "form.h"
#include "event.h"
#include "cli.h"

void keyHandler (std::string key);
void message_set(std::string text);
extern FormObject* redsocks_stat_FO ;
extern FormObject* redsocks_button_FO ;
extern FormObject* message_bar_FO ;
extern FormObject* redsocks_configure_FO ;
extern FormObject* iptables_stat_FO;
extern Form* main_form;
extern LogZone* main_log;

extern Form* keyboard_focus;
void focus_on_form(Form* the_form);

//int startUp();

#endif