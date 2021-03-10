#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "core/Renderer.h"
#include "core.h"

VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size){

    switch(Renderer::getAPI()){
        case RenderAPI::None :
            ORBITONS_ASSERT(false, "Bad RenderAPI");
        case RenderAPI::OpenGL : return  new OpenGLVertexBuffer(vertices,size);
    }

    return nullptr;
}

IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size){
    return new OpenGLIndexBuffer(indices,size);
}