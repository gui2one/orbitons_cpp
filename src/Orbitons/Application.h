#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include "Window.h"
#include "core/Scene.h"
#include "core/Timer.h"
#include "Renderer/Renderer.h"
namespace Orbitons{
    class Application{
    public:
        Application();
        std::unique_ptr<Window> m_window;
        // std::unique_ptr<Renderer> m_renderer;
        Orbitons::Scene m_scene;
        Timer m_timer;

    private:

    };
}
#endif /* APPLICATION_H */