#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "event.h"
#include "cli.h"


std::string strip (std::string text){
    text.erase(0, text.find_first_not_of(" "));
    text.erase(text.find_last_not_of(" ") + 1);
    text.erase(0, text.find_first_not_of("\n"));
    text.erase(text.find_last_not_of("\n") + 1);
    // It's a tiny "if" which revail us is text fully stripped or no
    if (text.find_last_not_of("\n")==(text.length()-1) and text.find_first_not_of(" ")==0 and text.find_first_not_of("\n")==0 and text.find_last_not_of(" ")==(text.length()-1)){
        return text;
    }else{
        // resume strip
        return strip(text);
    }
}


struct winsize window;

int size_width ()
{
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
  return window.ws_col;
}

int size_height ()
{
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
  return window.ws_row;
}

// Terminal escape sequences
const std::string ESC = "\x1B";  // Escape character
const std::string CSI = ESC + "[";  // Control Sequence Introducer
int mapx =0;
int mapy=0;
int before_x = 0;
int before_y = 0;

// Function to move the cursor to a specific position
void moveTo(int x, int y) {
    std::cout << CSI << y << ";" << x << "H";
    before_x = mapx;
    before_y = mapy;
    mapx = x;
    mapy = y;
}

void back (){
    moveTo(before_x, before_y);
}

// Function to clear the screen
void clearScreen() {
    std::cout << CSI << "2J";
}

// Function to set the text color
void setTextColor(int color) {
    std::cout << CSI << "38;5;" << color << "m";
}

void print(std::string text) {
    std::cout << text << std::endl;
}

void Cwrite(std::string text) {
    std::cout << text ;
}


progress_bar::progress_bar(int _x , int _y, int _delay){
    stat = 0;
    x = _x;
    y = _y;
    delay  = _delay;
}

progress_bar::~progress_bar(){
    delete lap_event;
}
void progress_bar::lap (){
    moveTo(x, y);
    stat++;
    std::string _char;
    if (stat == 4){
        stat = 0 ;
    }
  switch(stat){
      case 0:
          _char = '|';
          break;
      case 1:
          _char = '/';
          break;
      case 2:
          _char = '-';
          break;
      case 3:
          _char = "\\";
          break;
    }
    print(_char);
    //std::cout << "is going ";
    //back() ;
}



void progress_bar::run () {
    lap_event = new event(*this,delay);
}


base_progress_letter::base_progress_letter(int delay){
    this->letter= new std::string("");
    this->delay=delay;
    this->progress_event = new event(*this,delay);
}
base_progress_letter::~base_progress_letter(){
    delete this->progress_event;
    *(this->letter) = "";
}

// void progress_bar::lap(){
//     if ( !(*letter=="") ){
//     }
// }
void base_progress_letter::lap(){
    if ( !(*letter=="") ){
        this->_lap();
    }
}
void base_progress_letter::start(){
    if (this->progress_event->stat == false or *(this->letter)==""){
        *(this->letter) = base_letter;
        this->progress_event->start();
    }
}
void base_progress_letter::stop(){
    if (this->progress_event->stat == true){
        this->progress_event->stop();
    }
}
void base_progress_letter::hide(){
    *letter = "";
}
void base_progress_letter::show(){
    *letter = base_letter;
}
void base_progress_letter::set(std::string letter){
  this->stop();
  *(this->letter) = letter;
}

slash_progress_letter::slash_progress_letter(int delay):
  base_progress_letter(delay){
    base_letter="/";
}
void slash_progress_letter::_lap(){
    if (*letter == "/"){
        *letter = "-";
    } else if (*letter == "-"){
        *letter = "\\";
    } else if (*letter == "\\"){
        *letter = "|";
    } else if (*letter == "|"){
        *letter = "/";
    }

}


std::string sub_char (int num, std::string character){
    std::string result = "";
    for (int i=0; i<num; i++){
        result += character;
    }
    return result;
}

dot_progress_letter::dot_progress_letter(int _delay, int len, std::string _base, std::string mover):  base_progress_letter(_delay){
    this->len = len;
    this->base = _base;
    this->mover = mover;
    this->status = 0;
    this->base_letter = lap_str_calc();
    this->start();
}

std::string dot_progress_letter::lap_str_calc(){
    std::string result = "";
    result += sub_char(status,base);
    result += mover;
    result += sub_char(len - status,base);
    return result;
}

void dot_progress_letter::_lap(){
    status++;
    if (status > len){
        status = 0;
    }
    *letter = lap_str_calc();
}

void HideCursor(){
    std::cout << "\e[?25l";
}
void ShowCursor(){
    std::cout << "\e[?25h";
}