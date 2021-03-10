#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

Orbitons::Ref<VertexArray> VertexArray::create(){
    return Orbitons::MakeRef<OpenGLVertexArray>();
}