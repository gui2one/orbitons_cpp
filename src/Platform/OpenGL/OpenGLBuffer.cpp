#include "OpenGLBuffer.h"
#include <glad/glad.h>
namespace Orbitons
{
    
    //////////////////////////////////////////////////////
    //////   OpenGLVertexBuffer
    //////////////////////////////////////////////////////

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size){
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        // printf("[GL LOG] -- created Vertex Buffer\n");
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer(){

        glDeleteBuffers(1, &m_id);
    }
    void OpenGLVertexBuffer::bind(){
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void OpenGLVertexBuffer::unbind(){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }



    //////////////////////////////////////////////////////
    //////    OpenGLIndexBuffer
    //////////////////////////////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t size){
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer(){

        glDeleteBuffers(1, &m_id);
    }
    void OpenGLIndexBuffer::bind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void OpenGLIndexBuffer::unbind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
} // namespace Orbitons
