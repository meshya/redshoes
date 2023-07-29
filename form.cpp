#include <iostream>
#include <sstream>
#include <list>
#include "form.h"
#include "cli.h"

void FormObject::FormObject2(bool solid, std::string _side, int margin){
    this->solid = solid;
    if (_side=="left"){
        side = 0;
    }else if(_side=="center"){
        side = 1;
    }else if(_side=="right"){
        side = 2;
    }
    this->margin = margin;
}

FormObject::FormObject(std::string body ,bool solid, std::string side, int margin){
    this->body = body;
    this->FormObject2(solid, side, margin);
}
FormObject::FormObject(std::string (*bodyH)() ,bool solid, std::string side, int margin){
    this->bodyHandle = bodyH;
    this->FormObject2(solid, side, margin);
}


FormObject::FormObject(std::string body ,void (*on_click)() ,bool solid, std::string side, int margin){
    this->body = body;
    this->onClick(on_click);
    this->FormObject2(solid, side, margin);
}

FormObject::FormObject(std::string (*bodyH)() ,void (*on_click)() ,bool solid, std::string side, int margin){
    this->bodyHandle = bodyH;
    this->onClick(on_click);
    this->FormObject2(solid, side, margin);
}

void FormObject::side_left(){
    this->side = 0;
}
void FormObject::side_center(){
    this->side = 1;
}
void FormObject::side_right(){
    this->side = 2;
}




std::string FormObject::handle(int width){
    std::string _body = body;
    if (_body==""){
        _body = this->bodyHandle();
    }
    if (side == 0){
        return _body;
    }
    return _body;

}

void FormObject::onClick(void (*clickHandler)()){
    this->click = clickHandler;
}


logLine::logLine(std::string line){
    body = line;
}

std::string logLine::handle(int width){
    return this->body;
}

base_page::base_page (int startx, int starty, int endx, int endy){
    static_startX = startx;
    static_startY = starty;
    static_endX = endx;
    static_endY = endy;
    base_page2();
}
base_page::base_page (int (*startx)(), int (*starty)(), int (*endx)(), int (*endy)()){
    dyn_startX = startx;
    dyn_startY = starty;
    dyn_endX = endx;
    dyn_endY = endy;
    base_page2();
}
base_page::base_page (int startx, int starty, int (*endx)(), int (*endy)()){
    static_startX = startx;
    static_startY = starty;
    dyn_endX = endx;
    dyn_endY = endy;
    base_page2();
}
base_page::base_page (int (*startx)(), int starty, int (*endx)(), int (*endy)()){
    dyn_startX = startx;
    static_startY = starty;
    dyn_endX = endx;
    dyn_endY = endy;
    base_page2();
}

base_page::base_page (int (*startx)(), int (*starty)(), int endx, int (*endy)()){
    dyn_startX = startx;
    dyn_startY = starty;
    static_endX = endx;
    dyn_endY = endy;
    base_page2();
}


base_page::base_page (int startx, int starty, int (*endx)(), int endy){
    static_startX = startx;
    static_startY = starty;
    dyn_endX = endx;
    static_endY = endy;
    base_page2();
}

void base_page::base_page2(){
    this->page_event = new event(*this,100);
    this->hide();
}


Form::Form(int startx, int starty, int endx, int endy) : base_page(startx, starty, endx, endy){}
Form::Form(int (*startx)(), int (*starty)(), int (*endx)(), int (*endy)()) :  base_page(startx, starty, endx, endy){}
Form::Form(int startx, int starty, int (*endx)(), int (*endy)()) :  base_page(startx, starty, endx, endy){}
Form::Form(int (*startx)(), int (*starty)(), int endx, int (*endy)()) :  base_page(startx, starty, endx, endy){}
Form::Form(int (*startx)(), int starty, int (*endx)(), int (*endy)()) :  base_page(startx, starty, endx, endy){}
Form::Form(int startx, int starty, int (*endx)(), int endy) :  base_page(startx, starty, endx, endy){}


LogZone::LogZone(int startx, int starty, int endx, int endy) :  base_page(startx, starty, endx, endy){}
LogZone::LogZone(int (*startx)(), int (*starty)(), int (*endx)(), int (*endy)()) :  base_page(startx, starty, endx, endy){}
LogZone::LogZone(int startx, int starty, int (*endx)(), int (*endy)()) :  base_page(startx, starty, endx, endy){}
LogZone::LogZone(int (*startx)(), int (*starty)(), int endx, int (*endy)()) :  base_page(startx, starty, endx, endy){}
LogZone::LogZone(int (*startx)(), int starty, int (*endx)(), int (*endy)()) :  base_page(startx, starty, endx, endy){}


std::string spaces(int num){
    std::string out = "";
    for (int i=0; i<=num; i++){
        out += " ";
    }
    return out;
}

int base_page::startX(){
    if (dyn_startX){
        return (*dyn_startX)();
    }else{
        return static_startX;
    }
}
int base_page::startY(){
    if (dyn_startY){
        return (*dyn_startY)();
    }else{
        return static_startY;
    }
}
int base_page::endX(){
    if(dyn_endX){
        return (*dyn_endX)();
    }else{
        return static_endX;
    }
}
int base_page::endY(){
    if(dyn_endY){
        return (*dyn_endY)();
    }else{
        return static_endY;
    }
}


int base_page::max_lenX(){
    return this->endX() - this->startX();
}
int base_page::max_lenY(){
    return this->endY() - this->startY();
}

void base_page::lap(){
    std::string body = render();
    std::istringstream body_stream(body);
    std::list<std::string> fit_body; 
    std::string line;

    //print("this is body");
    //print(body);

    //print("before while");
    while(std::getline(body_stream, line)){
//        //print("before strip");
//        
        //line = strip(line);
//        //print("after strip");
        line = line.substr(scrolX);
        //print(line);
        if (line.length() > max_lenX()){
            line.erase(max_lenX());
            //print("flag 1");
        }
        if (line.length()<max_lenX()){
            line += spaces(max_lenX()-line.length());
            //print("flag 2");
        }
            fit_body.push_back(line);
//        std::cout << line << std::endl;
    }
    //print("after while");

    int onused_lines = fit_body.size() - max_lenY() ;
    if (onused_lines < 0){
        onused_lines = 0;
    }
    int real_scrolY = scrolY;
    if(onused_lines < scrolY){
        real_scrolY = onused_lines;
    }

    int lines_printed=0;
    int lines_rendered=0;
    std::list<std::string>::iterator lineIter = fit_body.begin();
    while (lines_printed < (max_lenY()-1)){
        if (lines_rendered >= real_scrolY){
            if (lines_rendered >= fit_body.size()){
                line = spaces(max_lenY());
            }else{
                line = *lineIter;
            }
            int _x = startX();
            int _y = startY()+lines_printed + 1;
            moveTo(_x,_y);
            print(line);
            back();
            lines_printed++;
        }
        std::advance(lineIter, 1);
        lines_rendered++;
    }

}


std::string base_page::render (){
    std::string result = "";
    for (BaseFormObject* FO : this->members){
        result += FO->handle()+"\n";
    }
    return result;
}


void Form::push(FormObject* FO){
    members.push_back(FO);
    selectables_cache = -1;
}


void base_page::show(){
    this->page_event->start();
}


void base_page::hide(){
    this->page_event->stop();
}

void Form::Up(){
    focus = focus - 1;
    if (focus < 1){
        focus = selectables();
    }
    focused_cache=nullptr;
}

void Form::Down(){
    focus += 1;
    if (focus>selectables()){
        focus = 1;
    }
    focused_cache=nullptr;
}

int Form::selectables (){
    if (!(selectables_cache == -1)){
        return selectables_cache;
    }
    selectables_cache = 0;
    for (BaseFormObject* _FO : members){
        FormObject* FO = dynamic_cast<FormObject*>(_FO);
        if (!FO->solid){
            selectables_cache += 1;
        }
    }
    return selectables_cache;
}


FormObject* Form::focused(){
    if (focused_cache){
        return focused_cache;
    }
    int num = 0;

    for (BaseFormObject* FO_p : Form::members){
        FormObject* FO = dynamic_cast<FormObject*>(FO_p);
        if (!(FO->solid)){
            num++;
            if ( num == focus ){
                focused_cache = FO;
                return FO;
            }
        }
    }
    return nullptr;
}


std::string Form::render(){
    std::string result = "";
    std::string selector_space;
    for (BaseFormObject* FO_p : this->members){
        FormObject* FO = dynamic_cast<FormObject*>(FO_p);
        if (!FO->solid){
            if (this->focused()==FO){
                selector_space = "~> ";
            }else{
                selector_space = "   ";
            }
        }else{
            selector_space = "";
        }

        std::string _margin = "";
        for (int i = 0; i<FO->margin; i++){
            _margin = " " + _margin ;
        }


        result += _margin + selector_space + FO->handle()+"\n";
    }
    return result;
}



void LogZone::log (std::string text){
    std::istringstream text_stream(text);
    std::string line ;
    while(std::getline(text_stream,line)){
        this->log_one_line(line);
    }
}
void LogZone::log_one_line(std::string line){
    logLine* FO = new logLine(line);
    this->members.push_back(FO);
}
