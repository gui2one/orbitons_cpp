#ifndef OPENGL_BUFFER_H
#define OPENGL_BUFFER_H

#include <pch.h>
#include "core/buffers/Buffer.h"
#include "opengl_debug.h"
#include "glad.h"
class OpenGLVertexBuffer : public VertexBuffer{
public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    virtual ~OpenGLVertexBuffer();

    virtual void bind()  override;
    virtual void unbind()  override;

    inline uint32_t getID() override { return m_id;}
private:

    uint32_t m_id;

};


class OpenGLIndexBuffer : public IndexBuffer{
public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
    virtual ~OpenGLIndexBuffer();

    virtual void bind()  override;
    virtual void unbind()  override;

    inline uint32_t getID() override { return m_id;}
private:

    GLuint m_id;

};
#endif /* OPENGL_BUFFER_H */