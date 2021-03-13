#include "GraphicContext.h"
#include "Platform/OpenGL/OpenGLContext.h"
namespace Orbitons
{
    std::unique_ptr<GraphicContext> GraphicContext::create(void * window_ptr){
        
        return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window_ptr));
    }
} // namespace Orbitons
