#ifndef APPLICATION_H
#define APPLICATION_H

#include "core.h"
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
        
        Scene m_scene;
        Timer m_timer;


    public:
        Application();

        void run();
        void onEvent(Event& e);
        Window& getWindow() { return *m_window; }
        GLFWwindow* getGLFWWindow(){ return m_window->getNativeWindow(); }


    private:
        std::unique_ptr<Window> m_window;
        static Application* m_instance;



    };

    // To be defined in CLIENT

}
#endif /* APPLICATION_H */