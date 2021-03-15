#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Orbitons{
    Ref<VertexArray> VertexArray::create(){
        return MakeRef<OpenGLVertexArray>();
    }

}