#include "OpenGLContext.h"

namespace Orbitons
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    :m_windowHandle(windowHandle)
    {
        
    }

    void OpenGLContext::init(){
        
        glfwMakeContextCurrent(m_windowHandle);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        if( !status){
            printf("Problem with glad\n");
            glfwTerminate();
        }
    }

    void OpenGLContext::swapBuffers(){
        glfwSwapBuffers(m_windowHandle);
    }
} // namespace Orbitons
