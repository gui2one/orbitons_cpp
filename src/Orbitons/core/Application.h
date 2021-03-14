#ifndef APPLICATION_H
#define APPLICATION_H

#include "pch.h"
#include "Window.h"
#include "Core/Scene.h"
#include "Core/Camera.h"
#include "Core/Timer.h"
#include "Renderer/Renderer.h"


#include "Events/Event.h"
#include "Events/KeyboardEvent.h"
namespace Orbitons{
    class Application{

    public : 
        std::unique_ptr<Window> m_window;
        Orbitons::Scene m_scene;
        Timer m_timer;

        void onKeyPress(Ref<Event> event){
            
        }

    public:
        Application();
        void run();
    private:

        EventQueue* m_eventQueue;



    };
}
#endif /* APPLICATION_H */