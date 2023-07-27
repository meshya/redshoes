#ifndef CLI_H
#define CLI_H

#include <iostream>
#include "event.h"



int size_width();
int size_height();

void moveTo(int x, int y);
void back();
void clearScreen();
void setTextColor(int color);
void print(std::string text);
void Cwrite(std::string text);


std::string strip(std::string text);

class progress_bar : public EventBase{
    private :
        int stat;

    public:
        int x;
        int y;
        int delay;
        progress_bar(int x, int y, int _delay = 10);
        ~progress_bar();
        void lap();
        void run();
        event *lap_event=nullptr;
};

class base_progress_letter : public EventBase{
    public:
        std::string* letter;
        int delay;
        base_progress_letter(int delay);
        ~base_progress_letter();
        void lap();
        void start();
        void stop();
        void hide();
        void show();
        void set(std::string letter);
        event* progress_event=nullptr;
        std::string base_letter="";
        virtual void _lap()=0;


};

class slash_progress_letter : public base_progress_letter{
    public:
        slash_progress_letter(int delay);
        void _lap();

};

class dot_progress_letter : public base_progress_letter{
    public:
        int len;
        std::string base;
        std::string mover;
        int status;
        dot_progress_letter(int _delay, int len, std::string _base, std::string mover);
        void _lap();
        std::string lap_str_calc ();
};

void HideCursor();
void ShowCursor();

#endif