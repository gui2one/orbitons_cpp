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

    void Application::run(){
        while(!m_window->shouldClose()){


            glEnable(GL_DEPTH_TEST);
            float delta_time = m_timer.getDeltaTime();
            m_timer.update();
            

            float angle = m_timer.getElapsedTime();

            glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f);        


            m_window->refresh(m_scene, m_scene.m_activeCamera, m_timer);
        }

        m_window->m_ui.close();
    
        glfwTerminate();
    }
}