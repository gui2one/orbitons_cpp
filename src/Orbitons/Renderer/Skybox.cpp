#include "Skybox.h"
#include "Platform/OpenGL/OpenGLSkybox.h"

namespace Orbitons
{
    
    Ref<Skybox> Skybox::create(){

        return MakeRef<OpenGLSkybox>();
    }
} // namespace Orbitons
