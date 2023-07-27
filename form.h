#ifndef FORM_H
#define FORM_H


#include <iostream>
#include <list>
#include "cli.h"
#include "event.h"


class BaseFormObject{
    public:
        virtual std::string handle(int width = -1)=0;
};

class FormObject : public BaseFormObject{
    public:
        bool solid;
        std::string body = "";
        std::string (*bodyHandle)() =nullptr ;
        FormObject(std::string body ,bool solid, std::string side="left", int margin=0);
        FormObject(std::string (*bodyH)() ,bool solid, std::string side="left", int margin=0);
        FormObject(std::string body ,void (*on_click)(),bool solid, std::string side="left", int margin=0);
        FormObject(std::string (*bodyH)() ,void (*on_click)(),bool solid, std::string side="left", int margin=0);
        void FormObject2(bool solid, std::string side, int margin);

        int margin ; // only works in left or right
        int side;
        /*
        0 for left
        1 for center
        2 for right
        */

        std::string handle(int width = -1) override;
        void (*click)();
        void onClick(void (*click)());
        void side_right();
        void side_left();
        void side_center();

};

class logLine : public BaseFormObject {
    public:
        std::string body ;
        logLine(std::string line);
        std::string handle(int width = -1) override;
};


class member_ship_page {
    public: 
        std::list<BaseFormObject*> members;
};


class base_page : public EventBase, public member_ship_page{
    public:

        void show();
        void hide();

        int static_startX;
        int static_startY;
        int static_endX;
        int static_endY;

        int (*dyn_startX)() = nullptr;
        int (*dyn_startY)() = nullptr;
        int (*dyn_endX)() = nullptr;
        int (*dyn_endY)() = nullptr;

        int startX();
        int startY();
        int endX();
        int endY();

        int scrolX = 0;
        int scrolY = 0;

        int max_lenX ();
        int max_lenY ();

        base_page(int startx, int starty, int endx, int endy);
        base_page(int (*startx)(), int (*starty)(), int (*endx)(), int (*endy)());
        base_page(int startx, int starty, int (*endx)(), int (*endy)());
        base_page(int (*startx)(), int (*starty)(), int endx, int (*endy)());
        base_page(int (*startx)(), int starty, int (*endx)(), int (*endy)());
        base_page(int startx, int starty, int (*endx)(), int endy);
        void base_page2();

        virtual std::string render();
        void lap() override ;
        event* page_event;

};

class Form : public base_page{
    public:
        int refreshRate;
        void push(FormObject* FO);
        int focus = 0;
        void Down();
        void Up();
        int selectables ();
        int selectables_cache = -1;
        FormObject* focused ();
        FormObject* focused_cache=nullptr ;

        Form(int startx, int starty, int endx, int endy);
        Form(int (*startx)(), int (*starty)(), int (*endx)(), int (*endy)());
        Form(int startx, int starty, int (*endx)(), int (*endy)());
        Form(int (*startx)(), int (*starty)(), int endx, int (*endy)());
        Form(int (*startx)(), int starty, int (*endx)(), int (*endy)());
        Form(int startx, int starty, int (*endx)(), int endy);

        std::string render();

        //std::list<FormObject*> members;


};

class LogZone : public base_page{
    public:
        void log(std::string text);
        void log_one_line(std::string line);

        LogZone(int startx, int starty, int endx, int endy);
        LogZone(int (*startx)(), int (*starty)(), int (*endx)(), int (*endy)());
        LogZone(int startx, int starty, int (*endx)(), int (*endy)());
        LogZone(int (*startx)(), int (*starty)(), int endx, int (*endy)());
        LogZone(int (*startx)(), int starty, int (*endx)(), int (*endy)());

        //std::list<logLine*> members;


};


void formEvent ();

#endif