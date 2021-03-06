#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include "Window.h"
#include "core/Scene.h"
#include "core/Timer.h"

class Application{
public:
    Application();
    std::unique_ptr<Window> m_window;
    Orbitons::Scene m_scene;
    Timer m_timer;

private:

};
#endif /* APPLICATION_H */