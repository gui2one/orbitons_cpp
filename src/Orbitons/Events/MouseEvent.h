#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H
#include "Event.h"
namespace Orbitons{

    class MouseEvent : public Event{
    public:
        MouseEvent(){}
        virtual ~MouseEvent(){}

        EVENT_CATEGORY_TYPE(EventCategoryMouse)
        
    private:

    };


    class MousePressEvent : public MouseEvent{
    public:
        int m_Button;
        uint32_t m_RepeatCount;
    public:
        MousePressEvent(int button, uint32_t repeat_count)
        : m_Button(button), m_RepeatCount(repeat_count){}

        EVENT_CLASS_TYPE(MousePress)
    };

    class MouseReleaseEvent : public MouseEvent{
    public:
        int m_Button;

    public:
        MouseReleaseEvent(int button)
        : m_Button(button){}

        EVENT_CLASS_TYPE(MouseRelease)
    };    

    class MouseScrollEvent : public MouseEvent{
    public:
        double m_xoffset;
        double m_yoffset;

    public:
        MouseScrollEvent(double xoffset, double yoffset)
        : m_xoffset(xoffset), m_yoffset(yoffset){}

        EVENT_CLASS_TYPE(MouseScroll)
    };  
}
#endif /* MOUSE_EVENT_H */