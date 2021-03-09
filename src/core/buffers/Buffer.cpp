#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size){
    return new OpenGLVertexBuffer(vertices,size);
}

IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size){
    return new OpenGLIndexBuffer(indices,size);
}