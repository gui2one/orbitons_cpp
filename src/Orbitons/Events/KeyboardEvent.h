#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H
#include "Event.h"
namespace Orbitons{

    class KeyboardEvent : public Event{
    public:
        KeyboardEvent(){}
        virtual ~KeyboardEvent(){
    
        }

        EVENT_CLASS_TYPE(KeyPress)
    private:

    };
}
#endif /* KEYBOARD_EVENT_H */