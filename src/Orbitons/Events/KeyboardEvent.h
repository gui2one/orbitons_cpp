#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H
#include "Event.h"
namespace Orbitons{

    class KeyboardEvent : public Event{
    public:
        KeyboardEvent(){}
        virtual ~KeyboardEvent(){}

        EVENT_CATEGORY_TYPE(EventCategoryKeyboard)
        
    private:

    };


    class KeyPressEvent : public KeyboardEvent{
    public:
        int m_Keycode;
        uint32_t m_RepeatCount;
    public:
        KeyPressEvent(int keycode, uint32_t repeat_count)
        : m_Keycode(keycode), m_RepeatCount(repeat_count){}

        EVENT_CLASS_TYPE(KeyPress)
    };

    class KeyReleaseEvent : public KeyboardEvent{
    public:
        int m_Keycode;

    public:
        KeyReleaseEvent(int keycode)
        : m_Keycode(keycode){}

        EVENT_CLASS_TYPE(KeyRelease)
    };    
}
#endif /* KEYBOARD_EVENT_H */