#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "event.h"
#include <iostream>
#include <termios.h>


extern std::string Right_key  ;
extern std::string Left_key  ;
extern std::string Down_key  ;
extern std::string Up_key  ;
extern std::string Enter_key ;


class key_handler : EventBase {
    public:
        void lap ();
        key_handler(void (*handler)(std::string key),bool _default=true);
        ~key_handler();
        void (*handler)(std::string key);
        void start();
        event *key_event=nullptr;
        struct termios oldSettings;
        struct termios newSettings;

};

#endif