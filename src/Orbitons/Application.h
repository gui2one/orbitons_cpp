#ifndef APPLICATION_H
#define APPLICATION_H

#include "pch.h"
#include "Window.h"
#include "core/Scene.h"
#include "core/Camera.h"
#include "core/Timer.h"
#include "Renderer/Renderer.h"
#include "Renderer/GraphicContext.h"

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

        Ref<GraphicContext> m_context;


    };
}
#endif /* APPLICATION_H */