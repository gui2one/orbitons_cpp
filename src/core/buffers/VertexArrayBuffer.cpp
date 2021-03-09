#include "VertexArrayBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"
VertexArrayBuffer* VertexArrayBuffer::create(){
    return new OpenGLVertexArrayBuffer();
}
