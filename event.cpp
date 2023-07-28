#include <iostream>
#include <chrono>
#include <thread>
#include "event.h"
#include "main.h"

bool system_sleep_status = false ;

void sleep_system(){
    system_sleep_status = true;
}
void awaik_system(){
    system_sleep_status = false;
}

void sleep (int milisecounds){
    std::this_thread::sleep_for(std::chrono::milliseconds(milisecounds));
}


int now (){
    int result = std::chrono::system_clock::now().time_since_epoch().count() / 1000000;
    return result;
}



std::list<event*> event::events; // Definition of the static stack variable


event::event(EventBase& ref ,int value) {
    refEvent=&ref;
    delay = value;
    set_last_run();
    events.push_back(this);
}

event::event(event_func ref ,int value){
    func = ref;
    delay = value;
    set_last_run();
    events.push_back(this);

}

int event::between(){
    return now() - (*this).last_run;
}

void event::set_last_run(){
    last_run = now();
}

void event::run(){
    if(refEvent)
        refEvent->lap();
    else if(func)
        func();
    set_last_run();

}


void event::start (){
    stat = true;
}

void event::stop(){
    stat = false;
}

void event::handle() {

    while(1){
        if (fail!=0){
            break;
        }
        if (!system_sleep_status){
            for (event* e : event::events){

                if (e->between() > e->delay){ 
                    if (e->stat){
                        e->run();
                    }
                }
            }
        }
        sleep(100);
    }
}


