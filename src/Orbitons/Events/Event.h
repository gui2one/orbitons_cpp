#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include "core.h"
#include "pch.h"


#define EVENT_CLASS_TYPE(type)\
static EventType GetStaticType() { return EventType::type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }\
virtual const char* GetName() const override { return #type; }

#define EVENT_CATEGORY_TYPE(category) virtual int GetCategoryFlags()const override { return category; } 

namespace Orbitons{

    enum class EventType{
        None = 0,
        KeyPress, KeyRelease, 
        MouseMove, MousePress, MouseRelease, MouseWheel,
        WindowResize, WindowClose
    };

    enum EventCategoryFlag{
        None = 0,
        EventCategoryKeyboard = BIT(0), 
        EventCategoryMouse    = BIT(1), 
        EventCategoryWindow   = BIT(2)
    };


    class Event{
    
    public:
        std::function<void()> m_Callback;
        bool m_Handled = false;
    public:
        virtual ~Event() = default;


        virtual EventType GetEventType() const = 0;
        virtual const char * GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;


    private:

    };

    class Dispatcher{
    public:
        Event& m_Event;

    public :
        Dispatcher(Event& e)
            :m_Event(e)
        {
            
        }

        template<typename T, typename F>
        bool dispatch(const F& fn){

            if( m_Event.GetName() == T.GetStaticName()){

                T.m_Handled = fn(static_cast<T&>(m_Event));
            }
            return true;
        }
    private:
    };
    /**
     * EventQueue  
     * Singleton Pattern  
     */
    class EventQueue{
    

    protected:
        /// protected constructor ( singleton pattern )
        EventQueue(){};
        static EventQueue* m_instance; 
    public:
        
        /// not cloneable
        EventQueue(const EventQueue& other) = delete;
        /// not assignable
        void operator=(const EventQueue& other ) = delete;

        static EventQueue* getInstance();


        void push(const Ref<Event>& event){ 

            m_Events.push_back(event);
            // printf("%s Event pushed ... \n", event->GetName()); 
        }

        void process(){
            for(Ref<Event>& ev : m_Events){
                ev->m_Callback();
                // printf("Callback Done ...\n");
            }

            m_Events.erase(m_Events.begin(), m_Events.end());
            // printf("Events in queue : %d\n", (int)m_Events.size());
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