#include "pch.h"
#include "Input.h"

#include "Application.h"
#include <GLFW/glfw3.h>

namespace Orbitons
{
    bool Input::isKeyPressed(const int keycode){
        
        auto*  win = static_cast<GLFWwindow*>(Application::getInstance().getGLFWWindow());
        return true;
    
    }
} // namespace Orbitons
