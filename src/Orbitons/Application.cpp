#include "Application.h"
namespace Orbitons{
    Application::Application(){

        m_eventQueue = EventQueue::getInstance();
        
        Ref<Event> event = MakeRef<KeyPressEvent>(42, 0);

        event->m_Callback = [](){
            printf("custom event \n");
        };
        m_eventQueue->push(event);

        m_window = std::make_unique<Window>();

        Renderer::setAPI(RenderAPI::OpenGL);
        Renderer::init();

        m_scene.init();

    }
}