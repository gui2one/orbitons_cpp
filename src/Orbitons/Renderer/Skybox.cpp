#include "Skybox.h"
#include "Platform/OpenGL/OpenGLSkybox.h"
Orbitons::Ref<Skybox> Skybox::create(){

    return Orbitons::MakeRef<OpenGLSkybox>();
}