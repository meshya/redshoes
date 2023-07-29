#include "keyboard.h"
#include "event.h"
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>



std::string Right_key = "\033[C" ;
std::string Left_key = "\033[D" ;
std::string Down_key = "\033[B" ;
std::string Up_key = "\033[A" ;
std::string Enter_key = "\n";


void key_handler::lap(){
    std::string key = "" ;
    char letter ;
    while (read(STDIN_FILENO, &letter, 1) > 0){
        key += letter;
    }
    if (!(key == "")){
        this->handler(key);
    }
}

void key_handler::start(){
    this->key_event = new event(*this, 50);
}

key_handler::key_handler(void (*handler)(std::string key),bool _default){
    this->handler=handler;
    struct termios old__Settings, new__Settings;
    this->oldSettings = old__Settings;
    this->newSettings = new__Settings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    if (_default){
        this->start();
    }
}

key_handler::~key_handler(){
    if (key_event){
        delete key_event ;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &this->oldSettings);
}
