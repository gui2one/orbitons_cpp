#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H
#include "pch.h"
#include "Renderer/GraphicContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Orbitons
{
    
    class OpenGLContext : public GraphicContext{
    public:
        OpenGLContext(GLFWwindow* windowHandle);


        virtual void init() override;
        virtual void swapBuffers() override;
    private:
        GLFWwindow * m_windowHandle;
    };
} // namespace Orbitons

#endif /* OPENGL_CONTEXT_H */