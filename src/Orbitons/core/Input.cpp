#include "Input.h"

#include "Application.h"
#include <GLFW/glfw3.h>

namespace Orbitons
{
    bool Input::isKeyPressed(const int keycode){
        
        auto*  win = static_cast<GLFWwindow*>(Application::getInstance()->getGLFWWindow());
        auto state = glfwGetKey(win, static_cast<int32_t>(keycode));
        
        
        if( state == GLFW_PRESS){
            printf("keycode %d PRESSED %d -- %d !!\n", keycode , state, GLFW_PRESS);
            return true;
        }
        return false;
    
    }
} // namespace Orbitons
