#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include "pch.h"
#include "core.h"

#define EVENT_CLASS_TYPE(type)\
static EventType GetStaticType() { return EventType::type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }\
virtual const char* GetName() const override { return #type; }

namespace Orbitons{

    enum class EventType{
        None = 0,
        KeyPress, KeyRelease, 
        MouseMove, MousePress, MouseRelease, MouseWheel,
        WindowResize
    };

    enum class EventCategory{
        None = 0,
        EventCategoryKeyBoard, 
        EventCategoryMouse, 
        EventCategoryWindow
    };


    class Event{
    
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual const char * GetName() const = 0;

    private:

    };

    class EventQueue{
    
    public:
        EventQueue(){}

        void push(const Ref<Event>& event){ 

            m_Events.push_back(event);
            printf("Event pushed ....\n"); 
        }

        std::vector<Ref<Event>>::iterator begin(){ return m_Events.begin(); }
        std::vector<Ref<Event>>::iterator end(){ return m_Events.end(); }

        std::vector<Ref<Event>>::const_iterator begin() const { return m_Events.begin(); }
        std::vector<Ref<Event>>::const_iterator end() const { return m_Events.end(); }

    private:

        std::vector<Ref<Event>> m_Events;
    };
}
#endif /* EVENT_H */    