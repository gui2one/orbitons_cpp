#include "Event.h"

namespace Orbitons
{

    EventQueue * EventQueue::m_instance = nullptr;
    EventQueue * EventQueue::getInstance(){

        if( m_instance == nullptr){
            m_instance = new EventQueue();
        }

        return m_instance;
    }
} // namespace Orbitons
