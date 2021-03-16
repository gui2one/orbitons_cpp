#include "Input.h"

#include "Application.h"
#include <GLFW/glfw3.h>

namespace Orbitons
{
    bool Input::isKeyPressed(const int keycode){
        
        auto*  win = static_cast<GLFWwindow*>(Application::getInstance()->getGLFWWindow());
        auto state = glfwGetKey(win, static_cast<int32_t>(keycode));
        
        
        if( state == GLFW_PRESS){
            // printf("keycode %d PRESSED %d -- %d !!\n", keycode , state, GLFW_PRESS);
            return true;
        }
        return false;
    
    }

    bool Input::isMouseButtonClicked(int button){
        auto*  win = static_cast<GLFWwindow*>(Application::getInstance()->getGLFWWindow());
        auto state = glfwGetMouseButton(win, button);
        switch (state)
        {
        case GLFW_PRESS:
            return true;
            break;
        
        default:
            break;
        }

        return false;
        
    }

    glm::vec2 Input::getMousePos(){
        auto*  win = static_cast<GLFWwindow*>(Application::getInstance()->getGLFWWindow());
        double x, y;
        glfwGetCursorPos(win, &x, &y);

        return glm::vec2((float)x, (float)y);
    }
} // namespace Orbitons
