#ifndef EVENT_H
#define EVENT_H

#include <stack>
#include <list>

extern bool system_sleep;

typedef void(*event_func)();

class EventBase{
public:
    virtual void lap()=0;
};

class event {

    public:

        int delay;
        int last_run;
        int between();
        void set_last_run();
        EventBase* refEvent=nullptr;
        event_func func=nullptr;

        event(EventBase& ref ,int value);
        event(event_func ref ,int value);
        void run ();
        void start();
        void stop();
        bool stat = true;


        static void handle();
        static std::list<event*> events; // Static stack variable to hold events
};



#endif // EVENT_H
