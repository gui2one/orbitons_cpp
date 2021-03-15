#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Orbitons
{
        
        std::shared_ptr<Shader> Shader::create(){
                return std::make_shared<OpenGLShader>();

        }
} // namespace Orbitons