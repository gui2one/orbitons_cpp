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

        m_Version = (char*)glGetString(GL_VERSION);
        m_ShadingLanguageVersion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
        printf("GL version: %s\n", glGetString(GL_VERSION));
        printf("GL shading language version: %s\n", 
        glGetString(GL_SHADING_LANGUAGE_VERSION));
    }

    void OpenGLContext::swapBuffers(){
        glfwSwapBuffers(m_windowHandle);
    }
} // namespace Orbitons
