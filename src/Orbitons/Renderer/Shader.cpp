#include "Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
std::shared_ptr<Shader> Shader::create(){
        return std::make_shared<OpenGLShader>();
}