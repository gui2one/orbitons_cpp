#include "Application.h"

Application::Application(){
    m_window = std::make_unique<Window>();

    Renderer::setAPI(RenderAPI::OpenGL);
    Renderer::init();

    m_scene.init();

}