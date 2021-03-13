#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include "Window.h"
#include "core/Scene.h"
#include "core/Camera.h"
#include "core/Timer.h"
#include "Renderer/Renderer.h"

#include "Events/Event.h"
#include "Events/KeyboardEvent.h"
namespace Orbitons{
    class Application{

    public : 
        std::unique_ptr<Window> m_window;
        Orbitons::Scene m_scene;
        Timer m_timer;

    public:
        Application();
        void run();
    private:

        EventQueue* m_eventQueue;
 

    };
}
#endif /* APPLICATION_H */