#include <iostream>
#include "redshoes.h"
#include "keyboard.h"
#include "form.h"
#include "cli.h"
#include "redsocks.h"
#include "editor.h"
#include "iptables.h"
#include "main.h"
#include "configs.h"
#include "terminal.h"

//Form* Form::Showing;

std::string message_text;
Form* keyboard_focus;
void focus_on_form(Form* the_form){
    keyboard_focus = the_form;
}

void keyHandler (std::string key){
    if(key==Right_key){
    }else if(key==Left_key){
    }else if(key==Down_key){
        keyboard_focus->Down();
    }else if(key==Up_key) {
        keyboard_focus->Up();
    }else if(key==Enter_key){
        keyboard_focus->focused()->click();
    }
}

slash_progress_letter redsocks_anim(200);
std::string redsocks_status_header (){
    std::string body = "";
    body += "Redsocks";
    if (not redsocks_status){
        body += " is off ";
        redsocks_anim.set(".");

    }else{
        body += " is running ";
        redsocks_anim.start();
    }
    body += *(redsocks_anim.letter);
    if (not redsocks_status){
        body += "    ";
    }

    return body ;
}

std::string redsocks_button (){
    std::string body = "";
    body += "Redsocks";

    if (redsocks_status){
        body = "Stop "  + body + "   ";
    }else{
        body = "Start " + body;
    }

    return body;
}

void redsocks_button_click (){
    if (redsocks_status){
        stop_redsocks();
    }else{
        start_redsocks();
    }
}


std::string message_bar(){
    return message_text;
}

void message_set(std::string text){
    message_text = text;
}

int inter_page_dyn_sizeX(){
    int inter_page = size_width()/2;
    return inter_page;
}

void redsocks_configure_click(){
    system_sleep_status = true;
    run_vim(REDSOCKS_CONFIG_TEMPLATE_PATH);
    system_sleep_status = false;
}


void iptables_configure_click(){
    system_sleep_status = true;
    run_vim(BASE_RULES_TEMPLATE_PATH);
    system_sleep_status = false;
}

dot_progress_letter iptable_on_anim(500,5,"*"," ");

dot_progress_letter iptable_off_anim(500,5," ","-");

std::string iptables_stat_body(){
    std::string result = "Tunnel is ";
    if ( tunnel_status ){
        result += "on <" + *(iptable_on_anim.letter) + ">";
    }else{
        result += "off <" + *(iptable_off_anim.letter) + ">";
    }
    result += "  ";
    return result;
}


std::string TunnelButtonTextRender (){
    std::string body = "";
    body += "Tunnel";

    if (tunnel_status){
        body = "Stop "  + body + "   ";
    }else{
        body = "Start " + body;
    }

    return body;
}

void TunnelButtonClick (){
    if (tunnel_status){
        tunnel_off();
    }else{
        tunnel_on();
    }
}

void ExitButton(){
    fail += 1; // from main.cpp
}

void killallRedsocks(){
    call("killall redsocks",false);
}

Form* main_form = new Form(0,0,&size_width,14);
LogZone* main_log = new LogZone(&inter_page_dyn_sizeX,0,&size_width,&size_height);


FormObject* message_bar_FO = new FormObject(&message_bar,true,"left",5);


int FrontEndStartUp(){

    main_form->push(new FormObject(&redsocks_status_header,true,"left",0));
    main_form->push(new FormObject(&iptables_stat_body,true,"left",0));
    main_form->push(new FormObject(&TunnelButtonTextRender,&TunnelButtonClick,false,"left",1));
    main_form->push(new FormObject(&redsocks_button,&redsocks_button_click,false,"left",1));
    main_form->push(new FormObject("Configure Redsocks",&redsocks_configure_click,false,"left",1));
    main_form->push(new FormObject("Kill all Redsocks",&killallRedsocks,false,"left",1));
    main_form->push(new FormObject("Configure iptables",&iptables_configure_click,false,"left",1));
    main_form->push(new FormObject("Exit",&ExitButton,false,"left",0));
    main_form->push(message_bar_FO);
    main_form->show();
    focus_on_form(main_form);
    key_handler* keyHandlerObject = new key_handler(&keyHandler);

    return 0;

}