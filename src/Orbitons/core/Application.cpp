#include "Application.h"
#include "Scene/ResourceLibrary.h"
namespace Orbitons
{

    Application *Application::s_instance = nullptr;
    Application *Application::getInstance()
    {

        if (s_instance == nullptr)
        {

            s_instance = new Application();
        }

        return s_instance;
    }

    Application::Application()
    {

        ResourceLibrary::getInstance().addItem(MakeRef<TextureItem>());
        Renderer::setAPI(RenderAPI::OpenGL);
        Renderer::init();

        m_window = std::make_unique<Window>();
        m_window->setEventCallback(BIND_EVENT_FUNCTION(Application::onEvent));
        m_window->m_ui.setEventCallback(BIND_EVENT_FUNCTION(Application::onEvent));
        m_window->m_controls.setEventCallback(BIND_EVENT_FUNCTION(Application::onEvent));
    }

    void Application::run()
    {
        while (!m_window->shouldClose())
        {

            // m_eventQueue->process();

            float delta_time = m_timer.getDeltaTime();
            m_timer.update();

            float angle = m_timer.getElapsedTime();

            glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f);

            m_window->refresh(m_timer);
        }

        m_window->m_ui.close();

        glfwTerminate();
    }

    void Application::onEvent(Event &e)
    {

        m_window->m_ui.onEvent(e);
        m_window->m_controls.onEvent(e);
        // m_window->onEvent(e);

        // printf("[Application Event] %s\n", e.GetName());
    }

}
