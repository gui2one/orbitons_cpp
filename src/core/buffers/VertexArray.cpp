#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
VertexArray* VertexArray::create(){
    return new OpenGLVertexArray();
}